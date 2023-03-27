#include "cipherAes.h"
#include "base64.h"
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

string CipherAes::generateKey(const bool saveOnfile) {
    m_prng.GenerateBlock(m_key, m_key.size());
    m_prng.GenerateBlock(m_iv, m_iv.size());

    if(saveOnfile) {
        QString dir = QFileDialog::getExistingDirectory(nullptr, "Open directory", "");
        if(!dir.isEmpty()) {
            string fname = dir.toStdString() + "/aes.key";
            FileSink* fs = new FileSink(fname.c_str());
            Base64Encoder encoderBase64(fs);

            encoderBase64.Put(m_key, m_key.size());
            encoderBase64.MessageEnd();
        }
    }

    stringstream ss;
    FileSink* fs = new FileSink(ss);
    Base64Encoder encoderBase64(fs);

    encoderBase64.Put(m_key, m_key.size());
    encoderBase64.MessageEnd();

    return ss.str();
}

bool CipherAes::isKeyLoaded() const{
    return !m_key.empty();
}
