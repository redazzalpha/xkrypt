#ifndef CIPHERAES_H
#define CIPHERAES_H

#include "cipherBase.h"
#include "osrng.h"
#include "hex.h"
#include "files.h"

/**
 * CipherAes class represents Aes algorithms
 * inherits from CipherBase and
 * encrypts decrypts and generates keys
 */

class CipherAes : public CipherBase {
protected:
    CryptoPP::AutoSeededRandomPool m_prng;
    CryptoPP::SecByteBlock m_key;
    CryptoPP::SecByteBlock m_iv = CryptoPP::SecByteBlock(CryptoPP::AES::BLOCKSIZE);
    CryptoPP::HexEncoder m_encoder = CryptoPP::HexEncoder(new CryptoPP::FileSink(std::cout));
    int m_keyLength = 0;

public:
    static const QString AlgName;

    // constructors
    CipherAes(const int keyLength);

    // destructor
    virtual ~CipherAes();

    // methods
    virtual CryptoPP::SecByteBlock generateKey() final;
    virtual QString getAlgName() const final;
    virtual QString getModeName() const override = 0 ;
    virtual void decrypt() override = 0;
    virtual void encrypt() override = 0;
    virtual bool isKeyLoaded() const final;
    virtual void flushKey() override;


};

#endif // CIPHERAES_H
