#include "aeseax.h"

using namespace CryptoPP;
using namespace std;

const QString AesEAX::ModeName = "EAX";

// constructors
AesEAX::AesEAX() {}

// destructor
AesEAX::~AesEAX() {};

// virtual methods
QString AesEAX::getModeName() const {
    return AesEAX::ModeName;
}

string AesEAX::encrypt(const KeyGen& keygen, const string& plain, const Encoding encoding) noexcept(false)
{
    std::cout << "cipher Aes eax encrypt" << std::endl;
}
string AesEAX::decrypt(const KeyGen& keygen, const string& cipher, const Encoding encoding) noexcept(false)
{
    std::cout << "cipher Aes eax decrypt" << std::endl;
}

