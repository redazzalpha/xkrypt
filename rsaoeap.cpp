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

string RsaOEAP::encryptText(const string& plain, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{
    std::cout << "cipher Rsa oeap encrypt" << std::endl;
}
string RsaOEAP::decryptText(const string& cipher, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{
    std::cout << "cipher Rsa oeap decrypt" << std::endl;
}
bool RsaOEAP::encryptFile(const string& fname, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{

}
bool RsaOEAP::decryptFile(const string& fname, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{

}




