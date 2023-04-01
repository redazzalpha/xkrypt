#include "rsaoeap.h"

using namespace CryptoPP;
using namespace std;

const QString RsaOEAP::ModeName = "ES-OAEP-SHA";

// constructors
RsaOEAP::RsaOEAP() {}

// destructor
RsaOEAP::~RsaOEAP() {};

// methods
QString RsaOEAP::getModeName() const
{
    return RsaOEAP::ModeName;
}
void RsaOEAP::decrypt(SecByteBlock key, SecByteBlock iv)
{
    std::cout << "cipher Rsa oeap decrypt" << std::endl;
}
void RsaOEAP::encrypt(SecByteBlock key, SecByteBlock iv)
{
    std::cout << "cipher Rsa oeap encrypt" << std::endl;
}




