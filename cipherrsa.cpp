#include "cipherrsa.h"

const QString CipherRsa::AlgName = "Asymmectric - Rsa";

// constructors
CipherRsa::CipherRsa(){}

// destructor
CipherRsa::~CipherRsa() {};

// virtual methods
QString CipherRsa::getAlgName() const
{
    return CipherRsa::AlgName;
}
