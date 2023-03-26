#include "aesCbc.h"

// constructors
AesCBC::AesCBC(): CipherAes("Aes-CBC") {}

// destructor
AesCBC::~AesCBC() {};

// methods
void AesCBC::generateKey(){std::cout << "cipher Aes generate key" << std::endl;}
void AesCBC::decrypt(){std::cout << "cipher Aes decrypt" << std::endl;}
void AesCBC::encrypt(){std::cout << "cipher Aes encrypt" << std::endl;}
