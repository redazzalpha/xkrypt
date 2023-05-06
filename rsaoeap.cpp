#include "rsaoeap.h"

using namespace CryptoPP;
using namespace std;

const std::string RsaOEAP::ModeName = "ES-OAEP-SHA";

// constructors
RsaOEAP::RsaOEAP() {}

// destructor
RsaOEAP::~RsaOEAP() {};

// virtual methods
std::string RsaOEAP::modeName() const
{
    return RsaOEAP::ModeName;
}
Mode RsaOEAP::modeId() const
{
    return Mode::OEAP;
}
string RsaOEAP::encryptText(const string& plain, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::cout << "cipher Rsa oeap encrypt" << std::endl;
}
string RsaOEAP::decryptText(const string& cipher, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::cout << "cipher Rsa oeap decrypt" << std::endl;
}
void RsaOEAP::encryptFile(const string& path, Keygen* keygen, const Encoding encoding)
{
    std::cout<< "in the rsa oeap slot encrypt" << std::endl;
}
void RsaOEAP::decryptFile(const string& path, Keygen* keygen, const Encoding encoding)
{
    std::cout<< "in the rsa oeap slot decrypt" << std::endl;
}


