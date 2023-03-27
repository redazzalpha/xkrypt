#include "rsaOeap.h"

using namespace std;

const QString RsaOEAP::ModeName = "ES-OAEP-SHA";

// constructors
RsaOEAP::RsaOEAP() {}

// destructor
RsaOEAP::~RsaOEAP() {};

// methods
QString RsaOEAP::getModeName() const {
    return RsaOEAP::ModeName;
}
void RsaOEAP::decrypt(){std::cout << "cipher Aes decrypt" << std::endl;}
void RsaOEAP::encrypt(){std::cout << "cipher Aes encrypt" << std::endl;}
string RsaOEAP::generateKey(const bool saveOnfile){
    std::cout << "cipher rsa - oeap generate key" << std::endl;
    return "";
}




