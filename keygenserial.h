#ifndef KEYGENSERIAL_H
#define KEYGENSERIAL_H

#include "keygen.h"
#include "enums.h"
#include <QMessageBox>
#include <QString>
#include <QMainWindow>

class KeygenSerial final: public QObject{
public:
    // constructor
    KeygenSerial();

    // methods
    bool deserialize(std::ifstream* file, Keygen *keygen) const noexcept(false);
    void serialize(const std::string& path, Keygen& keygen, const Encoding encoding) const;
    std::string serialize(Keygen& keygen, const Encoding encoding) const;
    std::string serializeEncoding(const Encoding encoding) const;

    std::string successMesssage(const std::string& path, Keygen& keygen, const Encoding encoding);
};

#endif // KEYGENSERIAL_H
