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

class AbstractCipherBase : public QObject {
    Q_OBJECT

public:
    // constructors
    AbstractCipherBase();

    // destructor
    virtual ~AbstractCipherBase();

    // methods
    virtual QString getAlgName() const = 0;
    virtual QString getModeName() const = 0;

    virtual std::string encryptText(const std::string& plain, const KeyGen& keygen, const Encoding encoding) const noexcept(false) = 0;
    virtual std::string decryptText(const std::string& cipher, const KeyGen& keygen, const Encoding encoding) const noexcept(false) = 0;
    virtual bool encryptFile(const std::string& fname, const KeyGen& keygen, const Encoding encoding) const noexcept(false) = 0;
    virtual bool decryptFile(const std::string& fname, const KeyGen& keygen, const Encoding encoding) const noexcept(false) = 0;
};

#endif // CIPHERBASE_H





