#include "aesgcm.h"
#include "base64.h"
#include "hex.h"
#include "gcm.h"

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

string AesGCM::encryptText(const string& plain, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{
    std::string cipher = "";
    const SecByteBlock& key = keygen.getKey();
    const SecByteBlock& iv = keygen.getIv();
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
    return cipher;
}
string AesGCM::decryptText(const string& cipher, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{
    std::string recover;
    const SecByteBlock& key = keygen.getKey();
    const SecByteBlock& iv = keygen.getIv();
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

    return recover;
}
void AesGCM::encryptFile(const string& path, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{

}
void AesGCM::decryptFile(const string& path, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{

}

