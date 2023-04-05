#ifndef KSERIAL_H
#define KSERIAL_H

#include "keygen.h"
#include "enums.h"
#include <QMessageBox>
#include <QString>
#include <QMainWindow>

class KSerial final: public QObject{

private:
    QMainWindow* m_parent;
    std::string m_fname = "";
    QString m_dir;
    Encoding m_encoding;
    bool m_loop = true;
    bool m_override = false;
    bool m_create = false;
    bool m_changeDirectory = false;

public:
    // constructor
    KSerial(QMainWindow* parent);

    // methods
    std::string getDir();
    Encoding getEncoding();
    std::string encodingToString(const Encoding encoding);
    bool saveOnFile(KeyGen& keygen, const Encoding encoding);
    bool importKeygen(KeyGen *keygen) noexcept(false);
    std::string keyToString(KeyGen& keygen, const Encoding encoding);

private:
    void keyToFile(KeyGen& keygen, const Encoding encoding);
    bool isFileExist(const std::string& filename);
    QMessageBox::ButtonRole dialogFileExists(const std::string& message);
    bool dialogInsertFilename(const std::string& message);
    bool dialogConfirm(const std::string& message);
    bool isBase64(std::vector<char>& bytes);
    bool isHex(std::vector<char>& bytes);
};

#endif // KSERIAL_H
