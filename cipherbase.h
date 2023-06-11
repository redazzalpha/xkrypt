#ifndef CIPHERBASE_H
#define CIPHERBASE_H

#include "enums.h"
#include "structures.h"
#include <QObject>
#include <files.h>
#include <iostream>
#include <keygenbase.h>

/**
 * CipherBase class is abstract and represent base
 * class for cipher algorithms
 */

class AbstractCipher {

protected:
    bool m_encfname = true;
    bool m_decfname = true;
    bool m_isContentEnc = false;
    std::vector<CryptoPP::byte> m_xrefs;

public:
    // constructors
    AbstractCipher();

    // destructor
    virtual ~AbstractCipher();

    // methods
    virtual std::string algName() const = 0;
    virtual std::string modeName() const = 0;
    virtual Algorithms algId() const = 0;
    virtual Mode modeId() const = 0;
    virtual std::string encryptText(const std::string& plain, AbstractKeygen* keygen, const Encoding encoding) = 0;
    virtual std::string decryptText(const std::string& cipher, AbstractKeygen* keygen, const Encoding encoding) = 0;
    virtual void encryptFile(const std::string& path, AbstractKeygen* keygen, const Encoding encoding, const std::string& newDir = "") = 0;
    virtual void decryptFile(const std::string& path, AbstractKeygen* keygen, const Encoding encoding, const std::string& newDir = "") = 0;

    void setEncfname(bool newEncfname);
    void setDecfname(bool newDecfname);
    bool encfname() const;
    bool decfname() const;

    DirFname extractFname(const std::string &path) const;
    std::vector<CryptoPP::byte>& vector_xrefs(AbstractKeygen *keygen);

    void injectRefs(CryptoPP::Sink* sink, AbstractKeygen *keygen);
    void injectRefs(std::string& sink, AbstractKeygen *keygen);

    std::string pumpRefs(CryptoPP::Source* source);
    std::string pumpRefs(const std::string& cipherText);

    std::string checkRefs(CryptoPP::Source *source);
    std::string checkRefs(const std::string& path);

    std::string stringRefs(AbstractKeygen* keygen);
    int afterRefs(CryptoPP::Source *source);
    bool isContentEnc() const;
    void setIsContentEnc(bool newCipherRefs);
};

#endif // CIPHERBASE_H





