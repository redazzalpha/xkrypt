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

string RsaSSA::encrypt(const KeyGen& keygen, const string& plain)
{
    std::cout << "cipher Rsa ssa encrypt" << std::endl;
}
string RsaSSA::decrypt(const KeyGen& keygen, const string& cipher)
{
    std::cout << "cipher Rsa ssa decrypt" << std::endl;
}



