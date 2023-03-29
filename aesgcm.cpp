#include "aesgcm.h"

using namespace CryptoPP;

const QString AesGCM::ModeName = "GCM";

// constructors
AesGCM::AesGCM(){}

// destructor
AesGCM::~AesGCM(){};

// methods
void AesGCM::decrypt(SecByteBlock key, SecByteBlock iv){std::cout << "cipher Aes gcm decrypt" << std::endl;}
void AesGCM::encrypt(SecByteBlock key, SecByteBlock iv){std::cout << "cipher Aes gcm encrypt" << std::endl;}

QString AesGCM::getModeName() const {
    return AesGCM::AlgName;
}
