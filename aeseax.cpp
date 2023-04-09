#include "aeseax.h"
#include "eax.h"

#include <base64.h>
#include <hex.h>

using namespace CryptoPP;
using namespace std;

const QString AesEAX::ModeName = "EAX";

// constructors
AesEAX::AesEAX() {}

// destructor
AesEAX::~AesEAX() {};

// virtual methods
QString AesEAX::getModeName() const {
    return AesEAX::ModeName;
}

string AesEAX::encryptText(const string& plain, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{
    std::string cipher = "";
    const SecByteBlock& key = keygen.getKey();
    const SecByteBlock& iv = keygen.getIv();
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
string AesEAX::decryptText(const string& cipher, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{
    std::string recover;
    const SecByteBlock& key = keygen.getKey();
    const SecByteBlock& iv = keygen.getIv();
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
bool AesEAX::encryptFile(const string& fname, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{

}
bool AesEAX::decryptFile(const string& fname, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{

}

