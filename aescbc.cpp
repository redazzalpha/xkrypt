#include "aescbc.h"
#include "aes.h"
#include "fileimporter.h"
#include "filters.h"
#include "hex.h"
#include "base64.h"
#include "modes.h"

using namespace CryptoPP;
using namespace std;

const QString AesCBC::ModeName = "CBC";

// constructors
AesCBC::AesCBC() {}

// destructor
AesCBC::~AesCBC() {};

// virtual methods
QString AesCBC::getModeName() const
{
    return AesCBC::ModeName;
}

string AesCBC::encryptText(const KeyGen& keygen, const string& plain, const Encoding encoding) noexcept(false)
{
    std::string cipher = "";
    const SecByteBlock& key = keygen.getKey();
    const SecByteBlock& iv = keygen.getIv();
    StringSink* ss = new StringSink(cipher);
    CBC_Mode<AES>::Encryption encryptor;
    StreamTransformationFilter* stf = new StreamTransformationFilter(encryptor);
    encryptor.SetKeyWithIV(key, key.size(), iv);

    switch(encoding) {
    case Encoding::BASE64 : stf->Attach(new Base64Encoder(ss)); break;
    case Encoding::HEX : stf->Attach(new HexEncoder(ss)); break;
    case Encoding::NONE : stf->Attach(ss); break;
    default: stf->Attach(new Base64Encoder(ss));;
    }

    StringSource(plain, true, stf);
    return cipher;
}
string AesCBC::decryptText(const KeyGen& keygen, const string& cipher, const Encoding encoding) noexcept(false)
{
    std::string recover;
    const SecByteBlock& key = keygen.getKey();
    const SecByteBlock& iv = keygen.getIv();
    StringSink* ss = new StringSink(recover);
    CBC_Mode<AES>::Decryption decryptor;
    StreamTransformationFilter* stf = new StreamTransformationFilter(decryptor, ss);
    decryptor.SetKeyWithIV(key, key.size(), iv);

    switch(encoding) {
    case Encoding::BASE64 : StringSource(cipher, true, new Base64Decoder(stf)); break;
    case Encoding::HEX : StringSource(cipher, true, new HexDecoder(stf)); break;
    case Encoding::NONE : StringSource(cipher, true, stf); break;
    default: StringSource(cipher, true, new Base64Decoder(stf));
    }

    return recover;
}
bool AesCBC::encryptFile(const KeyGen& keygen, const Encoding encoding) noexcept(false)
{
    bool encrypted = false;
    fstream* f = FileImporter().importFile();
    if(f) {

    }
    return encrypted;
}
bool AesCBC::decryptFile(const KeyGen& keygen, const Encoding encoding) noexcept(false)
{

}


