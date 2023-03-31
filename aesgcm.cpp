#include "aesgcm.h"

using namespace CryptoPP;

const QString AesGCM::ModeName = "GCM";

// constructors
AesGCM::AesGCM(){}

// destructor
AesGCM::~AesGCM(){};

// virtual methods
QString AesGCM::getModeName() const {
    return AesGCM::AlgName;
}

void AesGCM::encrypt(SecByteBlock key, SecByteBlock iv){std::cout << "cipher Aes gcm encrypt" << std::endl;}
void AesGCM::decrypt(SecByteBlock key, SecByteBlock iv){std::cout << "cipher Aes gcm decrypt" << std::endl;}

