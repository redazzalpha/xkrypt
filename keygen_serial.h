#ifndef KEYGEN_SERIAL_H
#define KEYGEN_SERIAL_H

#include "keygenaes.h"
#include "enums.h"
#include "keygenrsa.h"
#include <QMessageBox>
#include <QString>
#include <QMainWindow>

class Keygen_serial final {
public:
    // constructor
    Keygen_serial();

    // methods
    bool deserialize(std::ifstream* file, KeygenAes* keygen) const noexcept(false);
    bool deserialize(std::ifstream* file, KeygenRsa* keygen) const noexcept(false);
    bool deserialize(std::ifstream* file, KeygenAes* keygen, const Encoding encoding) const noexcept(false);
    bool deserialize(std::ifstream* file, KeygenRsa* keygen, const Encoding encoding) const noexcept(false);

    void serialize(const std::string& where, KeygenAes* keygen) const;
    void serialize(const std::string& where, KeygenRsa* keygen) const;
    void serialize(const std::string& where, KeygenAes* keygen, Encoding encoding) const;
    void serialize(const std::string& where, KeygenRsa* keygen, Encoding encoding) const;
    std::string serialize(KeygenAes* keygen) const;
    std::string serialize(KeygenRsa* keygen) const;
    std::string serialize(KeygenAes* keygen, Encoding encoding) const;
    std::string serialize(KeygenRsa* keygen, Encoding encoding) const;

    std::string serializeEncoding(const Encoding encoding) const;
    
    std::string successWriteKey(const std::string& path, KeygenAes* keygen);
    std::string successWriteKey(const std::string& path, KeygenRsa* keygen);
};

#endif // KEYGEN_SERIAL_H
