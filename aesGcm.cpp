#include "aesGcm.h"

// constructors
AesGCM::AesGCM(): CipherAes("Aes-GCM"){}

// destructor
AesGCM::~AesGCM() {};

// methods
void AesGCM::generateKey(){std::cout << "cipher Aes generate key" << std::endl;}
void AesGCM::decrypt(){std::cout << "cipher Aes decrypt" << std::endl;}
void AesGCM::encrypt(){std::cout << "cipher Aes encrypt" << std::endl;}
