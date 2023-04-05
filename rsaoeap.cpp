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

string RsaOEAP::encrypt(const KeyGen& keygen, const std::string& plain)
{
    std::cout << "cipher Rsa oeap encrypt" << std::endl;
}
string RsaOEAP::decrypt(const KeyGen& keygen, const string& cipher)
{
    std::cout << "cipher Rsa oeap decrypt" << std::endl;
}




