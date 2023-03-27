#include "aesEax.h"

using namespace CryptoPP;

const QString AesEAX::ModeName = "EAX";

// constructors
AesEAX::AesEAX(const int keyLength): CipherAes(keyLength){}

// destructor
AesEAX::~AesEAX() {};

// methods
void AesEAX::decrypt(){std::cout << "cipher Aes decrypt" << std::endl;}
void AesEAX::encrypt(){std::cout << "cipher Aes encrypt" << std::endl;}

QString AesEAX::getModeName() const {
    return AesEAX::ModeName;
}
