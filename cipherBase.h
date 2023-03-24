#ifndef CIPHERBASE_H
#define CIPHERBASE_H

#include <iostream>

/**
 * CipherBase class is abstract and represent base
 * class for cipher algorithms
 */

class CipherBase {

protected:
    std::string m_key = nullptr;
    std::string m_label;

public:
    // constructors
    CipherBase(std::string label);
    virtual ~CipherBase();

    // methods
    virtual void generateKey() = 0;
    virtual void decrypt() = 0;
    virtual void encrypt() = 0;
};

#endif // CIPHERBASE_H
