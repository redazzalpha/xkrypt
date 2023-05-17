#ifndef KEYGENSERIAL_H
#define KEYGENSERIAL_H

#include "keygenaes.h"
#include "enums.h"
#include "keygenrsa.h"
#include <QMessageBox>
#include <QString>
#include <QMainWindow>

class KeygenSerial final: public QObject{
public:
    // constructor
    KeygenSerial();

    // methods
    bool deserialize(std::ifstream* file, KeygenAes* keygen) const noexcept(false);
    bool deserialize(std::ifstream* file, KeygenRsa* keygen) const noexcept(false);
    void serialize(const std::string& where, KeygenAes* keygen) const;
    void serialize(const std::string& where, KeygenRsa* keygen) const;
    std::string serialize(KeygenAes* keygen) const;
    std::string serialize(KeygenRsa* keygen) const;
    std::string serializeEncoding(const Encoding encoding) const;
    
    std::string successWriteKey(const std::string& path, KeygenAes* keygen);
    std::string successWriteKey(const std::string& path, KeygenRsa* keygen);
};

#endif // KEYGENSERIAL_H
