#ifndef CIPHERBASE_H
#define CIPHERBASE_H

#include "keygen.h"
#include <QObject>
#include <QString>
#include <iostream>

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

    virtual std::string encrypt(const KeyGen& keygen, const std::string& plain) = 0;
    virtual std::string decrypt(const KeyGen& keygen, const std::string& cipher) = 0;
};

#endif // CIPHERBASE_H





