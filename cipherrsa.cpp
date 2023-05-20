#include "cipherrsa.h"

const std::string AbstractCipherRsa::AlgName = "Asymmetric - Rsa";

// constructors
AbstractCipherRsa::AbstractCipherRsa(){}

// destructor
AbstractCipherRsa::~AbstractCipherRsa() {};

// virtual methods
std::string AbstractCipherRsa::algName() const
{
    return AbstractCipherRsa::AlgName;
}
Algorithms AbstractCipherRsa::algId() const
{
    return Algorithms::RSA;
}
