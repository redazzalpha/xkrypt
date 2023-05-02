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
    bool m_run = true;
    bool m_encFname = true;
    bool m_decFname = true;
    const std::string m_encSuffix = ".xef";
    const std::string m_decSuffix = ".xdf";
    const std::string m_tempSuffix = ".xtf";

public:
    // constructors
    AbstractCipherBase();

    // destructor
    virtual ~AbstractCipherBase();

    // methods
    virtual std::string getAlgName() const = 0;
    virtual std::string getModeName() const = 0;
    
    void encFname(bool value);
    void decFname(bool value);
    std::string successEncMsg(const int succeed = 1);
    std::string successDecMsg(const int succeed = 1);

protected :
    bool& run();
    void removeFile(const std::string& filePath) const;
    DirFname extractFname(const std::string& path, const std::string& delim) const;

public slots:
    virtual std::string encryptText(const std::string& plain, Keygen* keygen, const Encoding encoding) = 0;
    virtual std::string decryptText(const std::string& cipher, Keygen* keygen, const Encoding encoding) = 0;
    virtual void encryptFile(std::vector<std::string>  paths, Keygen* keygen, const Encoding encoding) = 0;
    virtual void decryptFile(std::vector<std::string>  paths, Keygen* keygen, const Encoding encoding) = 0;
    void kill();
signals:
    void finished();
    void proceed(const int progress = 0);
    void error(const std::string& error);
    void success(const std::string& success);
    void cipherText(const std::string& cipherText);
    void recoverText(const std::string& recoverText);
};

#endif // CIPHERBASE_H





