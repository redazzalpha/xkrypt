#include "cipherRsa.h"

const QString CipherRsa::AlgName = "Asymmectric - Rsa";

// constructors
CipherRsa::CipherRsa(){}

// destructor
CipherRsa::~CipherRsa() {};

// methods
QString CipherRsa::getAlgName() const {
    return CipherRsa::AlgName;
}
