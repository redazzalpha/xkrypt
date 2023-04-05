#include "aescbc.h"
#include "aes.h"
#include "filters.h"
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

string AesCBC::encrypt(const KeyGen& keygen, const string& plain)
{
    try
    {
        std::string cipher = "";
        const SecByteBlock& key = keygen.getKey();
        const SecByteBlock& iv = keygen.getIv();

        CBC_Mode< AES >::Encryption e;
        e.SetKeyWithIV(key.BytePtr(), key.size(), iv.BytePtr());

        StringSink* ss = new StringSink(cipher);
        StreamTransformationFilter* stf = new StreamTransformationFilter(e, ss);
        StringSource s(plain, true, stf);

        std::cout << "cipher text: " << cipher << std::endl;
        return cipher;
    }
    catch(const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}
string AesCBC::decrypt(const KeyGen& keygen, const string& cipher)
{
    try
    {
        const SecByteBlock& key = keygen.getKey();
        const SecByteBlock& iv = keygen.getIv();

        std::string recovered;

        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key.BytePtr(), key.size(), iv.BytePtr());

        StringSink* sk = new StringSink(recovered);
        StreamTransformationFilter* stf = new StreamTransformationFilter(d,sk);
        StringSource(cipher, true, stf);

        std::cout << "recovered text: " << recovered << std::endl;
        return recovered;
    }
    catch(const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}



