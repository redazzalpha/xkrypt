#ifndef KEYGENRSA_H
#define KEYGENRSA_H

#include "keygenbase.h"
#include "rsa.h"

class KeygenRsa : public AbstractKeygen {

private:
    CryptoPP::RSA::PrivateKey* m_private = new CryptoPP::RSA::PrivateKey;
    CryptoPP::RSA::PublicKey* m_public = new CryptoPP::RSA::PublicKey;

public:
    // constructors
    KeygenRsa(size_t keysize = static_cast<size_t>(Rsa::KeySize::LENGTH_DEFAULT));
    KeygenRsa(const KeygenRsa& a);

    // operators
    KeygenRsa& operator=(const KeygenRsa& a);

    // destructor
    virtual ~KeygenRsa();

    // methods
    virtual void generateKey() override;
    virtual void generateKey(size_t keysize, Encoding encoding) override;
    virtual bool isReady() const override;
    virtual void flush() override;
    virtual KeygenRsa* keygenCpy() override;

    void setPrivate(CryptoPP::RSA::PrivateKey *newPrivate);
    void setPublic(CryptoPP::RSA::PrivateKey *privateKey);
    void setPublic(CryptoPP::RSA::PublicKey *newPublic);
    CryptoPP::RSA::PrivateKey* getPrivate();
    CryptoPP::RSA::PublicKey* getPublic();

    CryptoPP::InvertibleRSAFunction params();

};

#endif // KEYGENRSA_H
