#include "aeseax.h"
#include "defines.h"
#include "eax.h"
#include "except.h"
#include "files.h"

#include <QFile>
#include <base64.h>
#include <hex.h>

using namespace CryptoPP;
using namespace std;

const std::string AesEAX::ModeName = "EAX";

// constructors
AesEAX::AesEAX() {}

// destructor
AesEAX::~AesEAX() {};

// virtual methods
std::string AesEAX::modeName() const {
    return AesEAX::ModeName;
}
Mode AesEAX::modeId() const {
    return Mode::EAX;
}
string AesEAX::encryptText(const string& plain, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::string cipher = "";
    const SecByteBlock& key = keygen->getKey();
    const SecByteBlock& iv = keygen->getIv();
    StringSink* ss = new StringSink(cipher);
    CryptoPP::EAX<CryptoPP::AES>::Encryption encryptor;
    AuthenticatedEncryptionFilter* textFilter = new AuthenticatedEncryptionFilter(encryptor);
    encryptor.SetKeyWithIV(key, key.size(), iv);

    switch(encoding) {
    case Encoding::BASE64 : textFilter->Attach(new Base64Encoder(ss)); break;
    case Encoding::HEX : textFilter->Attach(new HexEncoder(ss)); break;
    case Encoding::NONE : textFilter->Attach(ss); break;
    default : throw EncodingException();
    }

    StringSource(plain, true, textFilter);
    return cipher;
}
string AesEAX::decryptText(const string& cipher, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::string recover;
    const SecByteBlock& key = keygen->getKey();
    const SecByteBlock& iv = keygen->getIv();
    StringSink* ss = new StringSink(recover);
    CryptoPP::EAX<CryptoPP::AES>::Decryption decryptor;
    AuthenticatedDecryptionFilter* textFilter = new AuthenticatedDecryptionFilter(decryptor, ss);
    decryptor.SetKeyWithIV(key, key.size(), iv);

    switch(encoding) {
    case Encoding::BASE64 : StringSource(cipher, true, new Base64Decoder(textFilter)); break;
    case Encoding::HEX : StringSource(cipher, true, new HexDecoder(textFilter)); break;
    case Encoding::NONE : StringSource(cipher, true, textFilter); break;
    default : throw EncodingException();
    }

    return recover;
}
void AesEAX::encryptFile(const string& path, Keygen* keygen, const Encoding encoding)
{
    string filename, output;
    const SecByteBlock& key = keygen->getKey();
    const SecByteBlock& iv = keygen->getIv();
    CryptoPP::EAX<CryptoPP::AES>::Encryption encryptor;
    DirFname dirfname = extractFname(path);

    if(m_encfname) {
        encryptor.SetKeyWithIV(key, key.size(), iv);
        AuthenticatedEncryptionFilter* filenameFilter = new AuthenticatedEncryptionFilter(encryptor, new HexEncoder(new StringSink(filename)));
        StringSource(dirfname.m_fname, true, filenameFilter);
    }
    else filename += dirfname.m_fname + FILE_TEMP_SUFFIX;

    FileSink* fs = new FileSink((output = dirfname.m_dir + DELIMITOR + filename).c_str());
    AuthenticatedEncryptionFilter* fileFilter = new AuthenticatedEncryptionFilter(encryptor);
    encryptor.SetKeyWithIV(key, key.size(), iv);

    injectRefs(fs, encoding);
    switch(encoding) {
    case Encoding::BASE64 : fileFilter->Attach(new Base64Encoder(fs)); break;
    case Encoding::HEX : fileFilter->Attach(new HexEncoder(fs)); break;
    case Encoding::NONE : fileFilter->Attach(fs); break;
    default : throw EncodingException();
    }

    FileSource source(path.c_str(), true, new Redirector(*fileFilter));

    remove(path.c_str());
    if(!m_encfname) {
        QString out = QString::fromStdString(output);
        QFile(out).rename(QString::fromStdString(output.substr(0, output.size()-strlen(FILE_TEMP_SUFFIX))));
    }
}
void AesEAX::decryptFile(const string& path, Keygen* keygen, const Encoding encoding)
{
    string filename, output;
    const SecByteBlock& key = keygen->getKey();
    const SecByteBlock& iv = keygen->getIv();
    CryptoPP::EAX<CryptoPP::AES>::Decryption decryptor;
    DirFname dirfname = extractFname(path);

    if(m_decfname) {
        decryptor.SetKeyWithIV(key, key.size(), iv);
        AuthenticatedEncryptionFilter* filenameFilter  = new AuthenticatedEncryptionFilter(decryptor, new StringSink(filename));
        StringSource(dirfname.m_fname, true, new HexDecoder(filenameFilter));
    }
    else filename += dirfname.m_fname + FILE_TEMP_SUFFIX;

    FileSink* fs = new FileSink((output = dirfname.m_dir + DELIMITOR + filename).c_str());
    AuthenticatedDecryptionFilter* fileFilter = new AuthenticatedDecryptionFilter(decryptor, fs);
    FileSource source(path.c_str(), false);
    decryptor.SetKeyWithIV(key, key.size(), iv);

    afterRefs(&source);
    switch(encoding) {
    case Encoding::BASE64 : source.Attach(new Base64Decoder(fileFilter)); break;
    case Encoding::HEX : source.Attach(new HexDecoder(fileFilter)); break;
    case Encoding::NONE : source.Attach(fileFilter); break;
    default : throw EncodingException();
    }

    source.PumpAll();
    remove(path.c_str());
    if(!m_decfname) {
        QString out = QString::fromStdString(output);
        QFile(out).rename(QString::fromStdString(output.substr(0, output.size()-strlen(FILE_TEMP_SUFFIX))));
    }
}

