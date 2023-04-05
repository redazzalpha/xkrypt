#include "aescbc.h"
#include "aes.h"
#include "filters.h"
#include "modes.h"

using namespace CryptoPP;

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

void AesCBC::encrypt(const KeyGen& keygen)
{
    try
    {

        std::string cipher = "", plain = "";

        const SecByteBlock& key = keygen.getKey();
        const SecByteBlock& iv = keygen.getIv();

        CBC_Mode< AES >::Encryption e;
        e.SetKeyWithIV(key.BytePtr(), key.size(), iv.BytePtr());

        StringSink* sk = new StringSink(cipher);
        StreamTransformationFilter* stf = new StreamTransformationFilter(e, sk);
        StringSource s(plain, true, stf);

        std::cout << "cipher text: " << cipher << std::endl;
    }
    catch(const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}
void AesCBC::decrypt(const KeyGen& keygen)
{
    try
    {
        const SecByteBlock& key = keygen.getKey();
        const SecByteBlock& iv = keygen.getIv();

        std::string cipher = "", plain = "", recovered;

        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key.BytePtr(), key.size(), iv.BytePtr());

        StringSink* sk = new StringSink(recovered);
        StreamTransformationFilter* stf = new StreamTransformationFilter(d,sk);
        StringSource(plain, true, stf);

        std::cout << "recovered text: " << recovered << std::endl;
    }
    catch(const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}



