#include "cipherAes.h"
#include <QFileDialog>
#include <sstream>

using namespace CryptoPP;
using namespace std;

const QString CipherAes::AlgName = "Symmectric - Aes";

// constructors
CipherAes::CipherAes(const int keyLength): m_key(keyLength) {}

// destructor
CipherAes::~CipherAes() {};

// methods
QString CipherAes::getAlgName() const {
    return CipherAes::AlgName;
}

SecByteBlock CipherAes::generateKey() {
    m_prng.GenerateBlock(m_key, m_key.size());
    m_prng.GenerateBlock(m_iv, m_iv.size());
    return m_key;
}

bool CipherAes::isKeyLoaded() const{
    return !m_key.empty();
}
