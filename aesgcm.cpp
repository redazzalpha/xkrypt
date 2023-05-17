#include "aesgcm.h"
#include "base64.h"
#include "files.h"
#include "hex.h"
#include "gcm.h"
#include "defines.h"
#include "except.h"

#include <QFile>
#include <keygenaes.h>

using namespace CryptoPP;
using namespace std;

const std::string AesGCM::ModeName = "GCM";

// constructors
AesGCM::AesGCM(){}

// destructor
AesGCM::~AesGCM(){};

// virtual methods
std::string AesGCM::modeName() const
{
    return AesGCM::ModeName;
}
Mode AesGCM::modeId() const
{
    return Mode::GCM;
}
string AesGCM::encryptText(const string& plain, AbstractKeygen* keygen, const Encoding encoding) noexcept(false)
{
    KeygenAes* keygen_aes = (KeygenAes*)keygen;
    std::string cipher = "";
    const SecByteBlock& key = keygen_aes->getKey();
    const SecByteBlock& iv = keygen_aes->getIv();
    StringSink* ss = new StringSink(cipher);
    CryptoPP::GCM<CryptoPP::AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(key, key.size(), iv);
    AuthenticatedEncryptionFilter* textFilter = new AuthenticatedEncryptionFilter(encryptor);

    switch(encoding) {
    case Encoding::BASE64 : textFilter->Attach(new Base64Encoder(ss)); break;
    case Encoding::HEX : textFilter->Attach(new HexEncoder(ss)); break;
    case Encoding::NONE : textFilter->Attach(ss); break;
    default : throw EncodingException();
    }

    StringSource(plain, true, textFilter);
    return cipher;
}
string AesGCM::decryptText(const string& cipher, AbstractKeygen* keygen, const Encoding encoding) noexcept(false)
{
    KeygenAes* keygen_aes = (KeygenAes*)keygen;
    std::string recover;
    const SecByteBlock& key = keygen_aes->getKey();
    const SecByteBlock& iv = keygen_aes->getIv();
    StringSink* ss = new StringSink(recover);
    CryptoPP::GCM<CryptoPP::AES>::Decryption decryptor;
    decryptor.SetKeyWithIV(key, key.size(), iv);
    AuthenticatedDecryptionFilter* textFilter = new AuthenticatedDecryptionFilter(decryptor, ss);

    switch(encoding) {
    case Encoding::BASE64 : StringSource(cipher, true, new Base64Decoder(textFilter)); break;
    case Encoding::HEX : StringSource(cipher, true, new HexDecoder(textFilter)); break;
    case Encoding::NONE : StringSource(cipher, true, textFilter); break;
    default : throw EncodingException();
    }

    return recover;
}
void AesGCM::encryptFile(const string& path, AbstractKeygen* keygen, const Encoding encoding)
{
    KeygenAes* keygen_aes = (KeygenAes*)keygen;
    string filename, output;
    const SecByteBlock& key = keygen_aes->getKey();
    const SecByteBlock& iv = keygen_aes->getIv();
    CryptoPP::GCM<CryptoPP::AES>::Encryption encryptor;
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
void AesGCM::decryptFile(const string& path, AbstractKeygen* keygen, const Encoding encoding)
{
    KeygenAes* keygen_aes = (KeygenAes*)keygen;
    string filename, output;
    const SecByteBlock& key = keygen_aes->getKey();
    const SecByteBlock& iv = keygen_aes->getIv();
    CryptoPP::GCM<CryptoPP::AES>::Decryption decryptor;
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
