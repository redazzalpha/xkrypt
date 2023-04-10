#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "aesgcm.h"
#include "aescbc.h"
#include "aeseax.h"
#include "serial.h"
#include "keygen.h"
#include "rsassa.h"
#include "rsaoeap.h"
#include "enums.h"
#include "actionkeyMgr.h"
#include "actionencrypt.h"
#include "actiondecrypt.h"
#include "actionquit.h"
#include "aesccm.h"
#include "fileimporter.h"
#include <QMainWindow>
#include <QList>
#include <QString>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    Serial m_serial;
    FileImporter m_fimporterEnc;
    FileImporter m_fimporterDec;
    FileImporter m_fimporterKey;
    std::string m_fname;
    std::string m_dir;
    KeyGen* m_keygen = new KeyGen;
    AbstractCipherBase* m_cipher = new AesGCM;

    QList<AbstractActionBase*> m_actions = QList<AbstractActionBase*> {
        new ActionKeyMgr(),
        new ActionEncrypt(),
        new ActionDecrypt(),
        new ActionQuit(),
    };
    QList<QString>* m_algorithms = new QList<QString> {
        QString::fromStdString(AbstractCipherAes::AlgName),
        QString::fromStdString(AbstractCipherRsa::AlgName),
    };
    QList<QString>* m_aesModes = new QList<QString>{
        QString::fromStdString(AesCBC::ModeName),
        QString::fromStdString(AesEAX::ModeName),
        QString::fromStdString(AesGCM::ModeName),
        QString::fromStdString(AesCCM::ModeName),
    };
    QList<QString>* m_rsaModes = new QList<QString>{
        QString::fromStdString(RsaOEAP::ModeName),
        QString::fromStdString(RsaSSA::ModeName),
    };
    QList<QString>* m_aesKeys = new QList<QString>{
        QString::number(static_cast<int>(KeyLength::LENGTH_DEFAULT)),
        QString::number(static_cast<int>(KeyLength::LENGTH_32)),
//        AES SIZES NOT DEFINED YET CANNOT USE THEM!
//        QString::number(static_cast<int>(KeyLength::LENGTH_64)),
//        QString::number(static_cast<int>(KeyLength::LENGTH_128)),
//        QString::number(static_cast<int>(KeyLength::LENGTH_256)),
//        QString::number(static_cast<int>(KeyLength::LENGTH_512)),
//        QString::number(static_cast<int>(KeyLength::LENGTH_1024)),
//        QString::number(static_cast<int>(KeyLength::LENGTH_2048)),
    };
    QList<QString>* m_keyEncodings = new QList<QString>{
        "Base64",
        "Hex",
        "None",
    };
    QList<QString>* m_enc_dec_encodings = new QList<QString>{
        "Base64",
        "Hex",
    };

public:
    // constructors
    MainWindow(QWidget *parent = nullptr);

    // destructor
    ~MainWindow();

private:

    // methods
    void uiInit();
    void connectItems() const;
    void generateKey(Encoding encodingIndex);
    void saveSuccess(Encoding encoding);
    void processEncrypt(QObject* sender);
    void processDecrypt(QObject *sender);
    void importAsymmectric();
    void importSymmectric();
    void m_cipherFrom(const std::string& alg, const std::string& mode);
    KeyLength keylengthFrom(const int index);

    void saveOnFile(const Encoding encoding);
    bool isFileExist(const std::string& filename) const;
    QMessageBox::ButtonRole dialogFileExists(const std::string& message);
    bool dialogInsertFilename(const std::string& message);
    bool dialogConfirm(const std::string& message);
    void dialogSuccessMessage(const std::string& message);
    void dialogErrorMessage(const std::string& message);
    void dialogNoKeyMessage(const std::string& action);

    void keyLoadedSelectable(const Qt::TextInteractionFlags flags) const;
    void setKeyLoadedStyle(const QString &style) const;
    void setFilesLoadedStyle(const QString &style) const;
    void setKeyLoadedText(const QString &keyStr) const;
    void setKeyLoadedSelectable(const bool selectable) const;

private slots:
    void on_m_encTabFileImport_clicked();
    void on_m_decTabFileImport_clicked();
    void on_m_encTabFileEncrypt_clicked();
    void on_m_decTabFileDecrypt_clicked();
    void on_m_encTabFileClear_clicked();


    void on_m_encTabTextEncrypt_clicked();
    void on_m_decTabTextDecrypt_clicked();
    void on_m_encTabTextReset_clicked();
    void on_m_decTabTextReset_clicked();

    void on_m_keyMGenerate_clicked();
    void on_m_keyMImport_clicked();

    void setComboModes(const QString& alg);
    void hideKey(const bool isChecked);
    void colorKeyLoaded();
    void colorFilesLoaded();
    void flushKey();
    void on_m_decTabFileClear_clicked();
};
#endif // MAINWINDOW_H
