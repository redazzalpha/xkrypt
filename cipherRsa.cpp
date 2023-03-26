#include "cipherRsa.h"

// constructors
CipherRsa::CipherRsa(const std::string& algName): CipherBase(algName) {}

// destructor
CipherRsa::~CipherRsa() {};

// methods
void CipherRsa::generateKey(){std::cout << "cipher Rsa generate key" << std::endl;}
void CipherRsa::decrypt(){std::cout << "cipher Rsa decrypt" << std::endl;}
void CipherRsa::encrypt(){std::cout << "cipher Rsa encrypt" << std::endl;}

