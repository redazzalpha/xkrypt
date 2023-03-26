#include "cipherAes.h"

const QString CipherAes::AlgName = "Symmectric - Aes";

// constructors
CipherAes::CipherAes() {}

// destructor
CipherAes::~CipherAes() {};

// methods
QString CipherAes::getAlgName() const {
    return CipherAes::AlgName;
}
