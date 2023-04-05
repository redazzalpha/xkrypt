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
void RsaOEAP::decrypt(const KeyGen& keygen)
{
    std::cout << "cipher Rsa oeap decrypt" << std::endl;
}
void RsaOEAP::encrypt(const KeyGen& keygen)
{
    std::cout << "cipher Rsa oeap encrypt" << std::endl;
}




