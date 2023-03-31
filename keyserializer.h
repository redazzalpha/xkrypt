#ifndef KEYSERIALIZER_H
#define KEYSERIALIZER_H

#include "enums.h"
#include "qmainwindow.h"
#include "secblock.h"

#include <QMessageBox>
#include <QString>

class KeySerializer final: public QObject{

private:
    QMainWindow* m_parent;
    std::string m_fname = "";
    QString m_dir;
//    Encoding m_encoding = Encoding::HEX;
//    Encoding m_encodingF = Encoding::HEX;
    bool m_loop = true;
    bool m_override = false;
    bool m_create = false;
    bool m_changeDirectory = false;

public:
    // constructor
    KeySerializer(QMainWindow* parent);

    // methods
    void saveOnFile(CryptoPP::SecByteBlock key, Encoding encoding);
    std::string keyToString(CryptoPP::SecByteBlock key, Encoding encoding);
    CryptoPP::SecByteBlock importKey(Encoding encoding) noexcept(false);

private:
    void keyToFile(CryptoPP::SecByteBlock key, Encoding encoding);
    bool isFileExist(const std::string &filename);
    QMessageBox::ButtonRole dialogFileExists(const std::string& message);
    bool dialogInsertFilename(const std::string& message);
    bool dialogConfirm(const std::string& message);
    bool isBase64(const std::vector<char> bytes);
    bool isHex(const std::vector<char> bytes);
};

#endif // KEYSERIALIZER_H
