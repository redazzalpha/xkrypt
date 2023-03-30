#ifndef FILEWRITER_H
#define FILEWRITER_H

#include "enums.h"
#include "qmainwindow.h"
#include "secblock.h"

#include <QMessageBox>
#include <QString>

class FileWriter final: public QObject{

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
    FileWriter(QMainWindow* parent);
    // methods
    bool isFileExist(const std::string &filename);
    void saveOnFile(CryptoPP::SecByteBlock key);
    void keyToFile(CryptoPP::SecByteBlock key);

    std::string keyToString(CryptoPP::SecByteBlock key);
    QMessageBox::ButtonRole dialogFileExists(const std::string& message);
    bool dialogInsertFilename(const std::string& message);
    bool dialogConfirm(const std::string& message);
    void dialogSuccessMessage(const std::string& message);
    void dialogErrorMessage(const std::string& message);
    void dialogNoKeyMessage(const std::string& action);

public slots:
    void setKeyEncoding(const int index);

};

#endif // FILEWRITER_H
