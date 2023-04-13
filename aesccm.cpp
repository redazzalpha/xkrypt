#include "aesccm.h"
#include "base64.h"
#include "files.h"
#include "hex.h"
#include "ccm.h"

using namespace CryptoPP;
using namespace std;

const std::string AesCCM::ModeName = "GCM";

// constructors
AesCCM::AesCCM(){}

// destructor
AesCCM::~AesCCM(){};

// virtual methods
std::string AesCCM::getModeName() const
{
    return AesCCM::AlgName;
}

string AesCCM::encryptText(const string& plain, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{
    std::string cipher = "";
    const SecByteBlock& key = keygen.getKey();
    const SecByteBlock& iv = keygen.getIv();
    StringSink* ss = new StringSink(cipher);
    CCM<AES>::Encryption encryptor;
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
string AesCCM::decryptText(const string& cipher, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{
    std::string recover;
    const SecByteBlock& key = keygen.getKey();
    const SecByteBlock& iv = keygen.getIv();
    StringSink* ss = new StringSink(recover);
    CCM<AES>::Decryption decryptor;
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
void AesCCM::encryptFile(const vector<string> paths, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{
    const SecByteBlock& key = keygen.getKey();
    const SecByteBlock& iv = keygen.getIv();
    CCM<AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(key, key.size(), iv);

    for(string path : paths) {
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
void AesCCM::decryptFile(const vector<string> paths, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{
    const SecByteBlock& key = keygen.getKey();
    const SecByteBlock& iv = keygen.getIv();
    CCM<AES>::Decryption decryptor;
    decryptor.SetKeyWithIV(key, key.size(), iv);

    for(string path : paths) {
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

