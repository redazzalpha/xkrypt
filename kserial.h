#ifndef KSERIAL_H
#define KSERIAL_H

#include "fileimporter.h"
#include "keygen.h"
#include "enums.h"
#include <QMessageBox>
#include <QString>
#include <QMainWindow>

class KSerial final: public QObject{

private:
    QMainWindow* m_parent;
    std::string m_fname;
    QString m_dir;
    bool m_loop = true;
    bool m_override = false;
    bool m_create = false;
    bool m_changeDirectory = false;
    FileImporter m_fi;

public:
    // constructor
    KSerial(QMainWindow* parent);

    // methods
    std::string getDir() const;
    std::string encodingToString(const Encoding encoding) const;
    bool saveOnFile(KeyGen& keygen, const Encoding encoding);
    bool importKeygen(KeyGen *keygen) noexcept(false);
    std::string keyToString(KeyGen& keygen, const Encoding encoding);

private:
    void keyToFile(KeyGen& keygen, const Encoding encoding) const;
    bool isFileExist(const std::string& filename) const;
    QMessageBox::ButtonRole dialogFileExists(const std::string& message);
    bool dialogInsertFilename(const std::string& message);
    bool dialogConfirm(const std::string& message);
};

#endif // KSERIAL_H
