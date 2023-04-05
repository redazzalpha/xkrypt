#ifndef CIPHERAES_H
#define CIPHERAES_H

#include "cipherbase.h"

/**
 * CipherAes class represents Aes algorithms
 * inherits from CipherBase and
 * encrypts decrypts and generates keys
 */

class CipherAes : public CipherBase {
public:
    static const QString AlgName;

    // constructors
    CipherAes();

    // destructor
    virtual ~CipherAes();

    // methods
    virtual QString getAlgName() const final;
    virtual QString getModeName() const override = 0 ;

    virtual std::string encrypt(const KeyGen& keygen, const std::string& plain) override = 0;
    virtual std::string decrypt(const KeyGen& keygen, const std::string& cipher) override = 0;
};

#endif // CIPHERAES_H
