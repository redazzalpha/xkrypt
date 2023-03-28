#include "rsaOeap.h"

using namespace CryptoPP;
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

CryptoPP::SecByteBlock RsaOEAP::generateKey() {
    CryptoPP::SecByteBlock m_key;
    return m_key;

}



