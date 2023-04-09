#ifndef CIPHERBASE_H
#define CIPHERBASE_H

#include "fileimporter.h"
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

protected:
    FileImporter* m_fi;

public:
    // constructors
    AbstractCipherBase();

    // destructor
    virtual ~AbstractCipherBase();

    // methods
    virtual QString getAlgName() const = 0;
    virtual QString getModeName() const = 0;

    virtual std::string encryptText(const KeyGen& keygen, const std::string& plain, const Encoding encoding) const noexcept(false) = 0;
    virtual std::string decryptText(const KeyGen& keygen, const std::string& cipher, const Encoding encoding) const noexcept(false) = 0;
    virtual bool encryptFile(const KeyGen& keygen, const Encoding encoding) const noexcept(false) = 0;
    virtual bool decryptFile(const KeyGen& keygen, const Encoding encoding) const noexcept(false) = 0;
};

#endif // CIPHERBASE_H





