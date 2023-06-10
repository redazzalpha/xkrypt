#ifndef KEYGENAES_H
#define KEYGENAES_H

#include "keygenbase.h"
#include "secblock.h"

class KeygenAes : public  AbstractKeygen {
private:
    CryptoPP::SecByteBlock m_key {0};
    CryptoPP::SecByteBlock m_iv {0};

public:
    // constructors
    KeygenAes(size_t keysize = static_cast<size_t>(Aes::KeySize::LENGTH_DEFAULT));
    KeygenAes(const KeygenAes& a);

    // operators
    KeygenAes& operator=(const KeygenAes &a);

    // methods
    virtual void generateKey() override;
    virtual void generateKey(size_t keysize, Encoding encoding) override;
    virtual bool isReady() const override;
    virtual void flush() override;
    virtual KeygenAes* keygenCpy() override;

    void setKey(CryptoPP::SecByteBlock key);
    void setIv(CryptoPP::SecByteBlock iv);
    void setPkState(bool newPkState);
    CryptoPP::SecByteBlock& key();
    CryptoPP::SecByteBlock& Iv();

    KeygenAes* pkDerive(const std::string& password, const bool isGenSalt = true);
    KeygenAes* pkDerive(const bool isGenSalt = true);

};

#endif // KEYGENAES_H
