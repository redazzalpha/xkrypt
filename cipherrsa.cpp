#include "cipherrsa.h"

const QString AbstractCipherRsa::AlgName = "Asymmectric - Rsa";

// constructors
AbstractCipherRsa::AbstractCipherRsa(){}

// destructor
AbstractCipherRsa::~AbstractCipherRsa() {};

// virtual methods
QString AbstractCipherRsa::getAlgName() const
{
    return AbstractCipherRsa::AlgName;
}
