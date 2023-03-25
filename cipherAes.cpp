#include "cipherAes.h"

// constructors
CipherAes::CipherAes(): CipherBase("Aes") {}

// destructor
CipherAes::~CipherAes() {};

// methods
void CipherAes::generateKey(){std::cout << "cipher Aes generate key" << std::endl;}
void CipherAes::decrypt(){std::cout << "cipher Aes decrypt" << std::endl;}
void CipherAes::encrypt(){std::cout << "cipher Aes encrypt" << std::endl;}

