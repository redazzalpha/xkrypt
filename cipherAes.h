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

public:
    static const QString AlgName;

    // constructors
    CipherAes(const int keyLength);

    // destructor
    virtual ~CipherAes();

    // methods
    virtual QString getAlgName() const final;
    virtual QString getModeName() const = 0;
    virtual void decrypt() = 0;
    virtual void encrypt() = 0;
    virtual CryptoPP::SecByteBlock generateKey() final;
    virtual bool isKeyLoaded() const final;
};

#endif // CIPHERAES_H
