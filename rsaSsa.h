#ifndef RSASSA_H
#define RSASSA_H

#include "cipherRsa.h"

class RsaSSA : public CipherRsa {
public:
    static const QString ModeName;

    // constructors
    RsaSSA();

    // destructor
    virtual ~RsaSSA();

    // methods
    virtual void decrypt() override;
    virtual void encrypt() override;
    virtual std::string generateKey(const bool saveOnfile) override;
    virtual QString getModeName() const override;
};

#endif // RSASSA_H
