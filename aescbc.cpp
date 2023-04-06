#include "aescbc.h"
#include "aes.h"
#include "filters.h"
#include "hex.h"
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

string AesCBC::encrypt(const KeyGen& keygen, const string& plain) noexcept(false)
{
    std::string cipher = "";
    const SecByteBlock& key = keygen.getKey();
    const SecByteBlock& iv = keygen.getIv();
    StringSink* ss = new StringSink(cipher);
    CBC_Mode<AES>::Encryption e;
    StreamTransformationFilter* stf = new StreamTransformationFilter(e, new HexEncoder(ss));

    e.SetKeyWithIV(key, key.size(), iv);
    StringSource(plain, true, stf);
    return cipher;
}
string AesCBC::decrypt(const KeyGen& keygen, const string& cipher) noexcept(false)
{
    std::string recover;
    const SecByteBlock& key = keygen.getKey();
    const SecByteBlock& iv = keygen.getIv();
    StringSink* sk = new StringSink(recover);
    CBC_Mode<AES>::Decryption d;
    StreamTransformationFilter* stf = new StreamTransformationFilter(d, sk);

    d.SetKeyWithIV(key, key.size(), iv);
    StringSource(cipher, true, new HexDecoder(stf));
    return recover;
}



