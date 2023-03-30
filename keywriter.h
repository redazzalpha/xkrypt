#ifndef KEYWRITER_H
#define KEYWRITER_H

#include "enums.h"
#include "qmainwindow.h"
#include "secblock.h"

#include <QMessageBox>
#include <QString>

class KeyWriter final: public QObject{

private:
    QMainWindow* m_parent;
    std::string m_fname = "";
    QString m_dir;
    Encoding m_encoding = Encoding::HEX;
    bool m_loop = true;
    bool m_override = false;
    bool m_create = false;
    bool m_changeDirectory = false;

public:
    // constructor
    KeyWriter(QMainWindow* parent);

    // methods
    void saveOnFile(CryptoPP::SecByteBlock key);
    std::string keyToString(CryptoPP::SecByteBlock key);

private:
    void keyToFile(CryptoPP::SecByteBlock key);
    bool isFileExist(const std::string &filename);
    QMessageBox::ButtonRole dialogFileExists(const std::string& message);
    bool dialogInsertFilename(const std::string& message);
    bool dialogConfirm(const std::string& message);

public slots:
    void setKeyEncoding(const int index);

};

#endif // KEYWRITER_H
