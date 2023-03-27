#include "aesGcm.h"

using namespace CryptoPP;

const QString AesGCM::ModeName = "GCM";

// constructors
AesGCM::AesGCM(const int keyLength): CipherAes(keyLength){}

// destructor
AesGCM::~AesGCM(){};

// methods
void AesGCM::decrypt(){std::cout << "cipher Aes decrypt" << std::endl;}
void AesGCM::encrypt(){std::cout << "cipher Aes encrypt" << std::endl;}

QString AesGCM::getModeName() const {
    return AesGCM::AlgName;
}
