#ifndef CIPHERBASE_H
#define CIPHERBASE_H

#include "secblock.h"
#include <iostream>
#include <QObject>
#include <QString>

/**
 * CipherBase class is abstract and represent base
 * class for cipher algorithms
 */

class CipherBase : public QObject {
    Q_OBJECT

public:
    // constructors
    CipherBase();

    // destructor
    virtual ~CipherBase();

    // methods
    virtual QString getAlgName() const = 0;
    virtual QString getModeName() const = 0;
    virtual void encrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv) = 0;
    virtual void decrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv) = 0;
};

#endif // CIPHERBASE_H
