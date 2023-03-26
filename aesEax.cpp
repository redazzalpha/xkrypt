#include "aesEax.h"

// constructors
AesEAX::AesEAX(): CipherAes("Aes-EAX") {}

// destructor
AesEAX::~AesEAX() {};

// methods
void AesEAX::generateKey(){std::cout << "cipher Aes generate key" << std::endl;}
void AesEAX::decrypt(){std::cout << "cipher Aes decrypt" << std::endl;}
void AesEAX::encrypt(){std::cout << "cipher Aes encrypt" << std::endl;}
