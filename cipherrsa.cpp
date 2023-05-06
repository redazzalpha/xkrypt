#include "cipherrsa.h"

const std::string AbstractCipherRsa::AlgName = "Asymmectric - Rsa";

// constructors
AbstractCipherRsa::AbstractCipherRsa(){}

// destructor
AbstractCipherRsa::~AbstractCipherRsa() {};

// virtual methods
std::string AbstractCipherRsa::algName() const
{
    return AbstractCipherRsa::AlgName;
}
Alg AbstractCipherRsa::algId() const
{
    return Alg::RSA;
}
