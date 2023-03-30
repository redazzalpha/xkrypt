#include "aeseax.h"

using namespace CryptoPP;

const QString AesEAX::ModeName = "EAX";

// constructors
AesEAX::AesEAX() {}

// destructor
AesEAX::~AesEAX() {};

// virtual methods
QString AesEAX::getModeName() const {
    return AesEAX::ModeName;
}

void AesEAX::encrypt(SecByteBlock, SecByteBlock){std::cout << "cipher Aes eax encrypt" << std::endl;}
void AesEAX::decrypt(SecByteBlock, SecByteBlock){std::cout << "cipher Aes eax decrypt" << std::endl;}

