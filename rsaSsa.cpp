#include "rsaSsa.h"


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
void RsaSSA::decrypt(){std::cout << "cipher r decrypt" << std::endl;}
void RsaSSA::encrypt(){std::cout << "cipher Aes encrypt" << std::endl;}

SecByteBlock RsaSSA::generateKey() {
    SecByteBlock m_key;
    return m_key;
}



