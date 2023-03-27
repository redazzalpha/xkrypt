#include "aesEax.h"

const QString AesEAX::ModeName = "EAX";

// constructors
AesEAX::AesEAX(){}

// destructor
AesEAX::~AesEAX() {};

// methods
void AesEAX::generateKey(){std::cout << "cipher Aes - eax generate key" << std::endl;}
void AesEAX::decrypt(){std::cout << "cipher Aes decrypt" << std::endl;}
void AesEAX::encrypt(){std::cout << "cipher Aes encrypt" << std::endl;}

QString AesEAX::getModeName() const {
    return AesEAX::ModeName;
}
