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

string RsaOEAP::encryptText(const string& plain, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::cout << "cipher Rsa oeap encrypt" << std::endl;
}
string RsaOEAP::decryptText(const string& cipher, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::cout << "cipher Rsa oeap decrypt" << std::endl;
}
void RsaOEAP::encryptFile(vector<string>* paths, Keygen* keygen, const Encoding encoding) noexcept(false)
{

}
void  RsaOEAP::decryptFile(vector<string>* paths, Keygen* keygen, const Encoding encoding) noexcept(false)
{

}



