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

    // methods
    virtual void generateKey() override;
    virtual void generateKey(size_t keysize, Encoding encoding) override;
    virtual bool isReady() const override;
    virtual void flush() override;

    void setKey(CryptoPP::SecByteBlock key);
    void setIv(CryptoPP::SecByteBlock iv);
    const CryptoPP::SecByteBlock& getKey() const;
    const CryptoPP::SecByteBlock& getIv() const;

};

#endif // KEYGENAES_H
