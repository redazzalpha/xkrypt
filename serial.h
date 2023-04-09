#ifndef SERIAL_H
#define SERIAL_H

#include "keygen.h"
#include "enums.h"
#include <QMessageBox>
#include <QString>
#include <QMainWindow>

class Serial final: public QObject{
public:
    // constructor
    Serial();

    // methods
    bool importKeygen(KeyGen *keygen, std::ifstream* file) const noexcept(false);
    void keyToFile(const std::string& path, KeyGen& keygen, const Encoding encoding) const;
    std::string keyToString(KeyGen& keygen, const Encoding encoding) const;
    std::string encodingToString(const Encoding encoding) const;
};

#endif // SERIAL_H
