#ifndef CIPHERBASE_H
#define CIPHERBASE_H

#include "keygen.h"
#include "structures.h"
#include <QObject>
#include <files.h>
#include <iostream>

/**
 * CipherBase class is abstract and represent base
 * class for cipher algorithms
 */

class AbstractCipherBase {

protected:
    bool m_encfname = true;
    bool m_decfname = true;


public:
    // constructors
    AbstractCipherBase();

    // destructor
    virtual ~AbstractCipherBase();

    // methods
    virtual std::string algName() const = 0;
    virtual std::string modeName() const = 0;
    virtual Alg algId() const = 0;
    virtual Mode modeId() const = 0;
    virtual std::string encryptText(const std::string& plain, Keygen* keygen, const Encoding encoding) = 0;
    virtual std::string decryptText(const std::string& cipher, Keygen* keygen, const Encoding encoding) = 0;
    virtual void encryptFile(const std::string& path, Keygen* keygen, const Encoding encoding) = 0;
    virtual void decryptFile(const std::string& path, Keygen* keygen, const Encoding encoding) = 0;

    void setEncfname(bool newEncfname);
    void setDecfname(bool newDecfname);
    bool encfname() const;
    bool decfname() const;

    DirFname extractFname(const std::string &path) const;
    std::string pumpRefs(const std::string &path);
    void injectRefs(CryptoPP::FileSink *fs, const Encoding encoding);
    void afterRefs(CryptoPP::FileSource *fs);
    std::string checkRefs(const std::string& path);

};

#endif // CIPHERBASE_H





