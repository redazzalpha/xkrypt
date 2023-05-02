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
    bool importKeygen(Keygen *keygen, std::ifstream* file) const noexcept(false);
    void keyToFile(const std::string& path, Keygen& keygen, const Encoding encoding) const;
    std::string keyToString(Keygen& keygen, const Encoding encoding) const;
    std::string encodingToString(const Encoding encoding) const;

    std::string writeSuccess(const std::string& path, Keygen& keygen, const Encoding encoding);
};

#endif // SERIAL_H
