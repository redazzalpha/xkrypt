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
QString AesCBC::getModeName() const {
    return AesCBC::ModeName;
}

void AesCBC::decrypt(SecByteBlock key, SecByteBlock iv){
    try
    {
        std::string cipher = "", plain = "", recovered;

        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        StringSource s(cipher, true,
            new StreamTransformationFilter(d,
                new StringSink(recovered)
            ) // StreamTransformationFilter
        ); // StringSource

        std::cout << "recovered text: " << recovered << std::endl;
    }
    catch(const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}
void AesCBC::encrypt(SecByteBlock key, SecByteBlock iv){
    try
    {
        std::string cipher = "", plain = "";

        CBC_Mode< AES >::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        StringSink* sk = new StringSink(cipher);
        StreamTransformationFilter* stf = new StreamTransformationFilter(e, sk);

        StringSource s(plain, true, stf);
    }
    catch(const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

}



