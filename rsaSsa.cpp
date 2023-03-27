#include "rsaSsa.h"

const QString RsaSSA::ModeName = "SSA";

// constructors
RsaSSA::RsaSSA() {}

// destructor
RsaSSA::~RsaSSA() {};

// methods
void RsaSSA::generateKey(){std::cout << "cipher rsa ssa generate key" << std::endl;}
void RsaSSA::decrypt(){std::cout << "cipher r decrypt" << std::endl;}
void RsaSSA::encrypt(){std::cout << "cipher Aes encrypt" << std::endl;}

QString RsaSSA::getModeName() const {
    return RsaSSA::ModeName;
}


