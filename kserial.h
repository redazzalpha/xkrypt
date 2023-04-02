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
    bool m_loop = true;
    bool m_override = false;
    bool m_create = false;
    bool m_changeDirectory = false;

public:
    // constructor
    KSerial(QMainWindow* parent);

    // methods
    void saveOnFile(KeyGen& keygen, const Encoding encoding);
    std::string keyToString(KeyGen& keygen, const Encoding encoding);
    bool importKeygen(KeyGen *keygen, const Encoding encoding) noexcept(false);

private:
    void keyToFile(KeyGen& keygen, const Encoding encoding);
    bool isFileExist(const std::string& filename);
    QMessageBox::ButtonRole dialogFileExists(const std::string& message);
    bool dialogInsertFilename(const std::string& message);
    bool dialogConfirm(const std::string& message);
    bool isBase64(const std::vector<char> bytes);
    bool isHex(const std::vector<char> bytes);
};

#endif // KSERIAL_H
