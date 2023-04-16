#include "aeseax.h"
#include "eax.h"
#include "files.h"

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
std::string AesEAX::getModeName() const {
    return AesEAX::ModeName;
}

string AesEAX::encryptText(const string& plain, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::string cipher = "";
    try {
        const SecByteBlock& key = keygen->getKey();
        const SecByteBlock& iv = keygen->getIv();
        StringSink* ss = new StringSink(cipher);
        EAX<AES>::Encryption encryptor;
        AuthenticatedEncryptionFilter* aef = new AuthenticatedEncryptionFilter(encryptor);
        encryptor.SetKeyWithIV(key, key.size(), iv);

        switch(encoding) {
        case Encoding::BASE64 : aef->Attach(new Base64Encoder(ss)); break;
        case Encoding::HEX : aef->Attach(new HexEncoder(ss)); break;
        case Encoding::NONE : aef->Attach(ss); break;
        default: aef->Attach(new Base64Encoder(ss));;
        }
        StringSource(plain, true, aef);
        return cipher;
    }
    catch(exception& e) {
        std::cout << e.what() << std::endl;
        emit error(e.what());
    }
    return cipher;
}
string AesEAX::decryptText(const string& cipher, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::string recover;
    try {
        const SecByteBlock& key = keygen->getKey();
        const SecByteBlock& iv = keygen->getIv();
        StringSink* ss = new StringSink(recover);
        EAX<AES>::Decryption decryptor;
        AuthenticatedDecryptionFilter* aef = new AuthenticatedDecryptionFilter(decryptor, ss);
        decryptor.SetKeyWithIV(key, key.size(), iv);

        switch(encoding) {
        case Encoding::BASE64 : StringSource(cipher, true, new Base64Decoder(aef)); break;
        case Encoding::HEX : StringSource(cipher, true, new HexDecoder(aef)); break;
        case Encoding::NONE : StringSource(cipher, true, aef); break;
        default: StringSource(cipher, true, new Base64Decoder(aef));
        }
        return recover;
    }
    catch(exception& e) {
        std::cout << e.what() << std::endl;
        emit error(e.what());
    }
    return recover;
}
void AesEAX::encryptFile(vector<string>* paths, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    try {
        const SecByteBlock& key = keygen->getKey();
        const SecByteBlock& iv = keygen->getIv();
        EAX<AES>::Encryption encryptor;
        encryptor.SetKeyWithIV(key, key.size(), iv);

        for(const string& path : *paths) {
            DirFname dirfname = extractFname(path, m_delim);
            FileSink* fs = new FileSink((dirfname.m_dir + dirfname.m_delim + encryptText(dirfname.m_fname, keygen, Encoding::HEX)).c_str());
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
    }
    catch(exception& e) {
        std::cout << e.what() << std::endl;
        emit error(e.what());
    }
}
void AesEAX::decryptFile(vector<string>* paths, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    try {
        const SecByteBlock& key = keygen->getKey();
        const SecByteBlock& iv = keygen->getIv();
        EAX<AES>::Decryption decryptor;
        decryptor.SetKeyWithIV(key, key.size(), iv);

        for(const string& path : *paths) {
            DirFname dirfname = extractFname(path, m_delim);
            FileSink* fs = new FileSink((dirfname.m_dir + dirfname.m_delim + decryptText(dirfname.m_fname, keygen, Encoding::HEX)).c_str());
            AuthenticatedDecryptionFilter* aef = new AuthenticatedDecryptionFilter(decryptor, fs);

            switch(encoding) {
            case Encoding::BASE64 : FileSource(path.c_str(), true, new Base64Decoder(aef)); break;
            case Encoding::HEX : FileSource(path.c_str(), true, new HexDecoder(aef)); break;
            case Encoding::NONE : FileSource(path.c_str(), true, aef); break;
            default: FileSource(path.c_str(), true, new Base64Decoder(aef));
            }
            removeFile(path);
        }
    }
    catch(exception& e) {
        std::cout << e.what() << std::endl;
        emit error(e.what());
    }
}

