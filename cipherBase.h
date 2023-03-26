#ifndef CIPHERBASE_H
#define CIPHERBASE_H

#include <iostream>
#include <QObject>
#include <QString>

/**
 * CipherBase class is abstract and represent base
 * class for cipher algorithms
 */

class CipherBase : public QObject {
      Q_OBJECT

protected:
    std::string m_key = "";

public:
    // constructors
    CipherBase();
    virtual ~CipherBase();

    // methods
    virtual QString getAlgName() const = 0;
    virtual QString getModeName() const = 0;
    virtual void generateKey() = 0;
    virtual void decrypt() = 0;
    virtual void encrypt() = 0;

    bool isKeyLoaded() const;
};

#endif // CIPHERBASE_H
