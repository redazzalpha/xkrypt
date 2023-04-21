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

string RsaSSA::encryptText(const string& plain, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::cout << "cipher Rsa ssa encrypt" << std::endl;
}
string RsaSSA::decryptText(const string& cipher, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::cout << "cipher Rsa ssa decrypt" << std::endl;
}

// slots
void RsaSSA::encryptFile(std::vector<std::string> paths, Keygen* keygen, const Encoding encoding)
{
    std::cout<< "in the rsa ssa slot encrypt" << std::endl;
}
void RsaSSA::decryptFile(std::vector<std::string> paths, Keygen* keygen, const Encoding encoding)
{
    std::cout<< "in the rsa ssa slot derypt" << std::endl;
}
