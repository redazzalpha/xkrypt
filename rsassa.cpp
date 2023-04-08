#include "rsassa.h"


using namespace CryptoPP;
using namespace std;

const QString RsaSSA::ModeName = "SSA";

// constructors
RsaSSA::RsaSSA() {}

// destructor
RsaSSA::~RsaSSA() {};

// virtual methods
QString RsaSSA::getModeName() const
{
    return RsaSSA::ModeName;
}

string RsaSSA::encryptText(const KeyGen& keygen, const string& plain, const Encoding encoding)
{
    std::cout << "cipher Rsa ssa encrypt" << std::endl;
}
string RsaSSA::decryptText(const KeyGen& keygen, const string& cipher, const Encoding encoding)
{
    std::cout << "cipher Rsa ssa decrypt" << std::endl;
}
void RsaSSA::encryptFile(const KeyGen& keygen, const std::string& plain, const Encoding encoding) noexcept(false)
{

}
void RsaSSA::decryptFile(const KeyGen& keygen, const std::string& cipher, const Encoding encoding) noexcept(false)
{

}



