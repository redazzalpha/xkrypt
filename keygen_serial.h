#ifndef KEYGEN_SERIAL_H
#define KEYGEN_SERIAL_H

#include "keygenaes.h"
#include "enums.h"
#include "keygenrsa.h"
#include <QMessageBox>
#include <QString>
#include <QMainWindow>

class Keygen_serial final {
private:
    std::string m_current;

public:
    // constructor
    Keygen_serial();

    // methods
    std::string current() const;
    bool deserialize(std::ifstream* file, KeygenAes* keygen) const noexcept(false);
    bool deserialize(std::ifstream* file, KeygenRsa* keygen) const noexcept(false);
    void serialize(const std::string& path, KeygenAes* keygen) const;
    void serialize(const std::string& path, KeygenRsa* keygen) const;
    std::string serialize(KeygenAes* keygen);
    std::string serialize(KeygenRsa* keygen);
    std::string serializeEncoding(const Encoding encoding) const;

    template<class T>
    bool deserialize(std::ifstream* file, T* keygen, const Encoding encoding) const noexcept(false);
    template<class T>
    void serialize(const std::string& where, T* keygen, Encoding encoding) const;
    template<class T>
    std::string serialize(T* keygen, Encoding encoding) const;
    
    std::string successWriteKey(const std::string& path, AbstractKeygen* keygen);
    std::string truncateInteger(const CryptoPP::Integer& integer, const size_t size = 10) const;
};

#endif // KEYGEN_SERIAL_H
