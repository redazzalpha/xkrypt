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

string RsaOEAP::encryptText(const KeyGen& keygen, const std::string& plain, const Encoding encoding) noexcept(false)
{
    std::cout << "cipher Rsa oeap encrypt" << std::endl;
}
string RsaOEAP::decryptText(const KeyGen& keygen, const string& cipher, const Encoding encoding) noexcept(false)
{
    std::cout << "cipher Rsa oeap decrypt" << std::endl;
}
bool RsaOEAP::encryptFile(const KeyGen& keygen, const Encoding encoding) noexcept(false)
{

}
bool RsaOEAP::decryptFile(const KeyGen& keygen, const Encoding encoding) noexcept(false)
{

}




