#include "aeseax.h"
#include "defines.h"
#include "eax.h"
#include "except.h"
#include "files.h"

#include <QFile>
#include <base64.h>
#include <hex.h>
#include <keygenaes.h>

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
string AesEAX::encryptText(const string& plain, AbstractKeygen* keygen, const Encoding encoding) noexcept(false)
{
    KeygenAes* kg_aes = (KeygenAes*)keygen;
    std::string cipher = "";
    const SecByteBlock& key = kg_aes->key();
    const SecByteBlock& iv = kg_aes->Iv();
    StringSink* ssink = new StringSink(cipher);
    CryptoPP::EAX<CryptoPP::AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(key, key.size(), iv);
    AuthenticatedEncryptionFilter* textFilter = new AuthenticatedEncryptionFilter(encryptor);

    string refsCipher;
    injectRefs(refsCipher, keygen);

    switch(encoding) {
    case Encoding::BASE64 : textFilter->Attach(new Base64Encoder); break;
    case Encoding::HEX : textFilter->Attach(new HexEncoder); break;
    case Encoding::NONE : break;
    default : throw EncodingException();
    }

    textFilter->Attach(ssink);
    StringSource(plain, true, textFilter);
    refsCipher += cipher;

    if(m_isContentEnc) return refsCipher;
    return cipher;
}
string AesEAX::decryptText(const string& cipher, AbstractKeygen* keygen, const Encoding encoding) noexcept(false)
{
    KeygenAes* kg_aes = (KeygenAes*)keygen;
    std::string recover;
    const SecByteBlock& key = kg_aes->key();
    const SecByteBlock& iv = kg_aes->Iv();
    StringSink* ssink = new StringSink(recover);
    CryptoPP::EAX<CryptoPP::AES>::Decryption decryptor;
    decryptor.SetKeyWithIV(key, key.size(), iv);
    AuthenticatedDecryptionFilter* textFilter = new AuthenticatedDecryptionFilter(decryptor, ssink);
    StringSource source(cipher, false);

    afterRefs(&source);

    switch(encoding) {
    case Encoding::BASE64 : source.Attach(new Base64Decoder); break;
    case Encoding::HEX : source.Attach(new HexDecoder); break;
    case Encoding::NONE : break;
    default : throw EncodingException();
    }

    source.Attach(textFilter);
    source.PumpAll();

    return recover;
}
void AesEAX::encryptFile(const string& path, AbstractKeygen* keygen, const Encoding encoding)
{
    KeygenAes* kg_aes = (KeygenAes*)keygen;
    string filename, output;
    const SecByteBlock& key = kg_aes->key();
    const SecByteBlock& iv = kg_aes->Iv();
    CryptoPP::EAX<CryptoPP::AES>::Encryption encryptor;
    DirFname dirfname = extractFname(path);

    if(m_encfname) {
        encryptor.SetKeyWithIV(key, key.size(), iv);
        AuthenticatedEncryptionFilter* filenameFilter = new AuthenticatedEncryptionFilter(encryptor, new HexEncoder(new StringSink(filename)));
        StringSource(dirfname.m_fname, true, filenameFilter);
    }
    else filename += dirfname.m_fname + FILE_TEMP_SUFFIX;

    FileSink* fs = new FileSink((output = dirfname.m_dir + DELIMITOR + filename).c_str());
    encryptor.SetKeyWithIV(key, key.size(), iv);
    AuthenticatedEncryptionFilter* fileFilter = new AuthenticatedEncryptionFilter(encryptor);

    injectRefs(fs, keygen);
    switch(encoding) {
    case Encoding::BASE64 : fileFilter->Attach(new Base64Encoder); break;
    case Encoding::HEX : fileFilter->Attach(new HexEncoder); break;
    case Encoding::NONE :  break;
    default : throw EncodingException();
    }

    fileFilter->Attach(new Redirector(*fs));
    FileSource(path.c_str(), true, fileFilter);

    remove(path.c_str());
    if(!m_encfname) {
        QString out = QString::fromStdString(output);
        QFile(out).rename(QString::fromStdString(output.substr(0, output.size()-strlen(FILE_TEMP_SUFFIX))));
    }
}
void AesEAX::decryptFile(const string& path, AbstractKeygen* keygen, const Encoding encoding)
{
    KeygenAes* kg_aes = (KeygenAes*)keygen;
    string filename, output;
    const SecByteBlock& key = kg_aes->key();
    const SecByteBlock& iv = kg_aes->Iv();
    CryptoPP::EAX<CryptoPP::AES>::Decryption decryptor;
    DirFname dirfname = extractFname(path);

    if(m_decfname) {
        decryptor.SetKeyWithIV(key, key.size(), iv);
        AuthenticatedEncryptionFilter* filenameFilter  = new AuthenticatedEncryptionFilter(decryptor, new StringSink(filename));
        StringSource(dirfname.m_fname, true, new HexDecoder(filenameFilter));
        filename = filename.substr(0, filename.size()-DEFAULT_PADDING_AEF);
    }
    else filename += dirfname.m_fname + FILE_TEMP_SUFFIX;

    FileSink* fs = new FileSink((output = dirfname.m_dir + DELIMITOR + filename).c_str());
    decryptor.SetKeyWithIV(key, key.size(), iv);
    AuthenticatedDecryptionFilter* fileFilter = new AuthenticatedDecryptionFilter(decryptor, fs);
    FileSource source(path.c_str(), false);

    afterRefs(&source);
    switch(encoding) {
    case Encoding::BASE64 : source.Attach(new Base64Decoder); break;
    case Encoding::HEX : source.Attach(new HexDecoder); break;
    case Encoding::NONE : break;
    default : throw EncodingException();
    }

    source.Attach(fileFilter);
    source.PumpAll();

    remove(path.c_str());
    if(!m_decfname) {
        QString out = QString::fromStdString(output);
        QFile(out).rename(QString::fromStdString(output.substr(0, output.size()-strlen(FILE_TEMP_SUFFIX))));
    }
}

