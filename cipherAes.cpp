#include "cipherAes.h"
#include <QFileDialog>
#include <sstream>

using namespace CryptoPP;
using namespace std;

const QString CipherAes::AlgName = "Symmectric - Aes";

// constructors
CipherAes::CipherAes(const int keyLength): m_keyLength(keyLength) {
}

// destructor
CipherAes::~CipherAes() {};

// methods
SecByteBlock CipherAes::generateKey() {
    m_key.CleanNew(m_keyLength);
    m_prng.GenerateBlock(m_key, m_key.size());
    m_prng.GenerateBlock(m_iv, m_iv.size());
    return m_key;
}
QString CipherAes::getAlgName() const {
    return CipherAes::AlgName;
}
bool CipherAes::isKeyLoaded() const{
    return !m_key.empty();
}

void CipherAes::flushKey() {
    m_key.CleanNew(0);
}
