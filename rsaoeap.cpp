#include "rsaoeap.h"

using namespace CryptoPP;
using namespace std;

const std::string RsaOEAP::ModeName = "ES-OAEP-SHA";

// constructors
RsaOEAP::RsaOEAP() {}

// destructor
RsaOEAP::~RsaOEAP() {};

// methods
std::string RsaOEAP::getModeName() const
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
void RsaOEAP::encryptFile(const vector<string>& paths, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{

}
void  RsaOEAP::decryptFile(const vector<string>& paths, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{

}




