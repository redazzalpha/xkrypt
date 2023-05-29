#ifndef CIPHER_H
#define CIPHER_H

#include "aescbc.h"
#include "cipherbase.h"

class Cipher : public QObject {
    Q_OBJECT

private:
    AbstractCipher* m_cipher = new AesCBC;
    bool m_run = true;

public:
    // constructors
    Cipher();

    // destructors
    ~Cipher();

    // methods
    void setEncfname(bool newEncfname);
    void setDecfname(bool newDecfname);
    bool encfname();
    bool decfname();

    std::string algName() const;
    std::string modeName() const;
    Algorithms algId() const;
    Mode modeId() const;
    std::string successMsg(const int succeed = 1, const bool mode = true);
    void cipherNew(const std::string& alg, const std::string& mode);
    void cipherDetect(const std::string &refs);
    void kill();
    std::string encodeText(const std::string& text, const Encoding encoding);
    std::string stringRefs(AbstractKeygen* keygen);

public slots:
    std::string encryptText(const std::string& plain, AbstractKeygen* keygen, const Encoding encoding);
    std::string decryptText(const std::string& cipher, AbstractKeygen* keygen, const Encoding encoding);
    void encryptFile(std::vector<std::string> paths, AbstractKeygen* keygen, const Encoding encoding);
    void decryptFile(std::vector<std::string> paths, AbstractKeygen* keygen);

signals:
    void finished();
    void proceed(const int progress = 1);
    void error(const std::string& error, const std::string& description = "");
    void success(const std::string& success);
    void cipherText(const std::string& cipherText);
    void recoverText(const std::string& recoverText);
    void cipherFile(const std::string& success);
    void recoverFile(const std::string& success);
    void processing(const std::string& filename);
    void autoDetect(const std::string& alg, const std::string& mode, const Encoding encoding, const bool decfname);
};

#endif // CIPHER_H
