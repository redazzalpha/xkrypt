#include "rsassa.h"


using namespace CryptoPP;
using namespace std;

const QString RsaSSA::ModeName = "SSA";

// constructors
RsaSSA::RsaSSA() {}

// destructor
RsaSSA::~RsaSSA() {};

// methods
QString RsaSSA::getModeName() const {
    return RsaSSA::ModeName;
}
void RsaSSA::encrypt(SecByteBlock key, SecByteBlock iv){std::cout << "cipher Aes encrypt" << std::endl;}
void RsaSSA::decrypt(SecByteBlock key, SecByteBlock iv){std::cout << "cipher r decrypt" << std::endl;}



