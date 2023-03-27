#include "aesCbc.h"
#include "modes.h"

using namespace CryptoPP;

const QString AesCBC::ModeName = "CBC";

// constructors
AesCBC::AesCBC(const int keyLength): CipherAes(keyLength) {}

// destructor
AesCBC::~AesCBC() {};

// methods
void AesCBC::encrypt(){
    try
    {
        std::string cipher = "", plain = "";

        CBC_Mode< AES >::Encryption e;
        e.SetKeyWithIV(m_key, m_key.size(), m_iv);

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
void AesCBC::decrypt(){
    try
    {
        std::string cipher = "", plain = "", recovered;

        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(m_key, m_key.size(), m_iv);

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

QString AesCBC::getModeName() const {
    return AesCBC::ModeName;
}


