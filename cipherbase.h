#ifndef CIPHERBASE_H
#define CIPHERBASE_H

#include "keygen.h"
#include "structures.h"
#include <QObject>
#include <iostream>

/**
 * CipherBase class is abstract and represent base
 * class for cipher algorithms
 */

class AbstractCipherBase : public QObject {
    Q_OBJECT

protected:
    const std::string m_delim = "/";

public:
    // constructors
    AbstractCipherBase();

    // destructor
    virtual ~AbstractCipherBase();

    // methods
    virtual std::string getAlgName() const = 0;
    virtual std::string getModeName() const = 0;
    
    virtual std::string encryptText(const std::string& plain, Keygen* keygen, const Encoding encoding) noexcept(false) = 0;
    virtual std::string decryptText(const std::string& cipher, Keygen* keygen, const Encoding encoding) noexcept(false) = 0;
    virtual void decryptFile(std::vector<std::string>* paths, Keygen* keygen, const Encoding encoding) noexcept(false) = 0;
    virtual void encryptFile(std::vector<std::string>* paths, Keygen* keygen, const Encoding encoding) noexcept(false) = 0;

protected :
    void removeFile(const std::string& filePath) const;
    DirFname extractFname(const std::string& path, const std::string& delim) const;

signals:
    void error(const std::string& err);
};

#endif // CIPHERBASE_H





