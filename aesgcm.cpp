#include "aesgcm.h"
#include "base64.h"
#include "files.h"
#include "hex.h"
#include "gcm.h"
#include "defines.h"

using namespace CryptoPP;
using namespace std;

const std::string AesGCM::ModeName = "GCM";

// constructors
AesGCM::AesGCM(){}

// destructor
AesGCM::~AesGCM(){};

// virtual methods
std::string AesGCM::getModeName() const
{
    return AesGCM::AlgName;
}

// slots
string AesGCM::encryptText(const string& plain, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::string cipher = "";
    try {
        const SecByteBlock& key = keygen->getKey();
        const SecByteBlock& iv = keygen->getIv();
        StringSink* ss = new StringSink(cipher);
        GCM<AES>::Encryption encryptor;
        AuthenticatedEncryptionFilter* aef = new AuthenticatedEncryptionFilter(encryptor);
        encryptor.SetKeyWithIV(key, key.size(), iv);

        switch(encoding) {
        case Encoding::BASE64 : aef->Attach(new Base64Encoder(ss)); break;
        case Encoding::HEX : aef->Attach(new HexEncoder(ss)); break;
        case Encoding::NONE : aef->Attach(ss); break;
        default: aef->Attach(new Base64Encoder(ss));;
        }
        StringSource(plain, true, aef);
        emit cipherText(cipher);
        emit finished();
        return cipher;
    }
    catch(exception& e) {
        emit error(e.what());
    }
    return cipher;
}
string AesGCM::decryptText(const string& cipher, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::string recover;
    try {
        const SecByteBlock& key = keygen->getKey();
        const SecByteBlock& iv = keygen->getIv();
        StringSink* ss = new StringSink(recover);
        GCM<AES>::Decryption decryptor;
        AuthenticatedDecryptionFilter* aef = new AuthenticatedDecryptionFilter(decryptor, ss);
        decryptor.SetKeyWithIV(key, key.size(), iv);

        switch(encoding) {
        case Encoding::BASE64 : StringSource(cipher, true, new Base64Decoder(aef)); break;
        case Encoding::HEX : StringSource(cipher, true, new HexDecoder(aef)); break;
        case Encoding::NONE : StringSource(cipher, true, aef); break;
        default: StringSource(cipher, true, new Base64Decoder(aef));
        }
        emit recoverText(recover);
        emit finished();
        return recover;
    }
    catch(exception& e) {
        emit error(e.what());
    }
    return recover;
}
void AesGCM::encryptFile(vector<string> paths, Keygen* keygen, const Encoding encoding)
{
    try {
        const SecByteBlock& key = keygen->getKey();
        const SecByteBlock& iv = keygen->getIv();
        GCM<AES>::Encryption encryptor;
        encryptor.SetKeyWithIV(key, key.size(), iv);

        for(const string& path : paths) {
            DirFname dirfname = extractFname(path);
            FileSink* fs = new FileSink((dirfname.m_dir + DELIMITOR + encryptText(dirfname.m_fname, keygen, Encoding::HEX)).c_str());
            AuthenticatedEncryptionFilter* aef = new AuthenticatedEncryptionFilter(encryptor);

            switch(encoding) {
            case Encoding::BASE64 : aef->Attach(new Base64Encoder(fs)); break;
            case Encoding::HEX : aef->Attach(new HexEncoder(fs)); break;
            case Encoding::NONE : aef->Attach(fs); break;
            default: aef->Attach(new Base64Encoder(fs));;
            }
            FileSource(path.c_str(), true, aef);
            removeFile(path);
        }
        emit finished();
    }
    catch(exception& e) {
        emit error(e.what());
    }
}
void AesGCM::decryptFile(vector<string> paths, Keygen* keygen, const Encoding encoding)
{
    try {
        const SecByteBlock& key = keygen->getKey();
        const SecByteBlock& iv = keygen->getIv();
        GCM<AES>::Decryption decryptor;
        decryptor.SetKeyWithIV(key, key.size(), iv);

        for(const string& path : paths) {
            DirFname dirfname = extractFname(path);
            FileSink* fs = new FileSink((dirfname.m_dir + DELIMITOR + decryptText(dirfname.m_fname, keygen, Encoding::HEX)).c_str());
            AuthenticatedDecryptionFilter* aef = new AuthenticatedDecryptionFilter(decryptor, fs);

            switch(encoding) {
            case Encoding::BASE64 : FileSource(path.c_str(), true, new Base64Decoder(aef)); break;
            case Encoding::HEX : FileSource(path.c_str(), true, new HexDecoder(aef)); break;
            case Encoding::NONE : FileSource(path.c_str(), true, aef); break;
            default: FileSource(path.c_str(), true, new Base64Decoder(aef));
            }
            removeFile(path);
        }

        emit finished();
    }
    catch(exception& e) {
        emit error(e.what());
    }
}
