#include "aesGcm.h"

const QString AesGCM::ModeName = "GCM";

// constructors
AesGCM::AesGCM(){}

// destructor
AesGCM::~AesGCM(){};

// methods
void AesGCM::generateKey(){std::cout << "cipher Aes _ gcm generate key" << std::endl;}
void AesGCM::decrypt(){std::cout << "cipher Aes decrypt" << std::endl;}
void AesGCM::encrypt(){std::cout << "cipher Aes encrypt" << std::endl;}

QString AesGCM::getModeName() const {
    return AesGCM::AlgName;
}
