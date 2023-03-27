#include "rsaOeap.h"

const QString RsaOEAP::ModeName = "ES-OAEP-SHA";

// constructors
RsaOEAP::RsaOEAP() {}

// destructor
RsaOEAP::~RsaOEAP() {};

// methods
void RsaOEAP::generateKey(){std::cout << "cipher rsa - oeap generate key" << std::endl;}
void RsaOEAP::decrypt(){std::cout << "cipher Aes decrypt" << std::endl;}
void RsaOEAP::encrypt(){std::cout << "cipher Aes encrypt" << std::endl;}

QString RsaOEAP::getModeName() const {
    return RsaOEAP::ModeName;
}


