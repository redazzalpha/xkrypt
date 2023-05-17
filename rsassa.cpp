#include "rsassa.h"


using namespace CryptoPP;
using namespace std;

const std::string RsaSSA::ModeName = "SSA";

// constructors
RsaSSA::RsaSSA() {}

// destructor
RsaSSA::~RsaSSA() {};

// virtual methods
std::string RsaSSA::modeName() const
{
    return RsaSSA::ModeName;
}
Mode RsaSSA::modeId() const
{
    return Mode::SSA;
}
string RsaSSA::encryptText(const string& plain, AbstractKeygen* keygen, const Encoding encoding) noexcept(false)
{
    std::cout << "cipher Rsa ssa encrypt" << std::endl;
}
string RsaSSA::decryptText(const string& cipher, AbstractKeygen* keygen, const Encoding encoding) noexcept(false)
{
    std::cout << "cipher Rsa ssa decrypt" << std::endl;
}
void RsaSSA::encryptFile(const string& path, AbstractKeygen* keygen, const Encoding encoding)
{
    std::cout<< "in the rsa ssa slot encrypt" << std::endl;
}
void RsaSSA::decryptFile(const string& path, AbstractKeygen* keygen, const Encoding encoding)
{
    std::cout<< "in the rsa ssa slot derypt" << std::endl;
}
