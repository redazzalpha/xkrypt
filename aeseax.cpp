#include "aeseax.h"

using namespace CryptoPP;

const QString AesEAX::ModeName = "EAX";

// constructors
AesEAX::AesEAX() {}

// destructor
AesEAX::~AesEAX() {};

// methods
QString AesEAX::getModeName() const {
    return AesEAX::ModeName;
}
void AesEAX::encrypt(SecByteBlock key, SecByteBlock iv){std::cout << "cipher Aes eax encrypt" << std::endl;}
void AesEAX::decrypt(SecByteBlock key, SecByteBlock iv){std::cout << "cipher Aes eax decrypt" << std::endl;}

