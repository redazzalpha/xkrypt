#ifndef CIPHERBASE_H
#define CIPHERBASE_H

#include <iostream>
#include <QObject>

/**
 * CipherBase class is abstract and represent base
 * class for cipher algorithms
 */

class CipherBase : public QObject {
      Q_OBJECT
protected:
    std::string m_key = "";
    std::string m_algName;

public:
    // constructors
    CipherBase(std::string algName);
    virtual ~CipherBase();

    // methods
    virtual void generateKey() = 0;
    virtual void decrypt() = 0;
    virtual void encrypt() = 0;
};

#endif // CIPHERBASE_H
