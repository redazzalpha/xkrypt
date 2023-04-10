#include "rsassa.h"


using namespace CryptoPP;
using namespace std;

const std::string RsaSSA::ModeName = "SSA";

// constructors
RsaSSA::RsaSSA() {}

// destructor
RsaSSA::~RsaSSA() {};

// virtual methods
std::string RsaSSA::getModeName() const
{
    return RsaSSA::ModeName;
}

string RsaSSA::encryptText(const string& plain, const KeyGen& keygen, const Encoding encoding) const
{
    std::cout << "cipher Rsa ssa encrypt" << std::endl;
}
string RsaSSA::decryptText(const string& cipher, const KeyGen& keygen, const Encoding encoding) const
{
    std::cout << "cipher Rsa ssa decrypt" << std::endl;
}
void  RsaSSA::encryptFile(const string& path, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{

}
void RsaSSA::decryptFile(const string& path, const KeyGen& keygen, const Encoding encoding) const noexcept(false)
{

}



