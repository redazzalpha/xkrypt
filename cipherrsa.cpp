#include "cipherrsa.h"

const std::string AbstractCipherRsa::AlgName = "Asymmectric - Rsa";

// constructors
AbstractCipherRsa::AbstractCipherRsa(){}

// destructor
AbstractCipherRsa::~AbstractCipherRsa() {};

// virtual methods
std::string AbstractCipherRsa::getAlgName() const
{
    return AbstractCipherRsa::AlgName;
}
