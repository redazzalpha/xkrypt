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
#include "processbar.h"
#include <QList>
#include <QString>
#include <QMessageBox>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QThread m_threadProcess;
    QThread m_threadCipher;
    ProcessBar m_process = ProcessBar(this);
    AbstractCipherBase* m_cipher = new AesCBC;
    Serial m_serial;
    FileImporter m_fimporterEnc;
    FileImporter m_fimporterDec;
    FileImporter m_fimporterKey;
    std::string m_fname;
    std::string m_path;
    Keygen* m_keygen = new Keygen;

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

    bool m_warning = true;
public:
    // constructors
    MainWindow(QWidget *parent = nullptr);

    // destructor
    ~MainWindow();

    AbstractCipherBase *cipher() const;

private:
    // methods
    void uiInit();
    void connectItems();
    void connectCipher();
    void connectProcess();
    void generateKey(Encoding encodingIndex);
    void shortcuts();
    void toolTips();
    void importAsymmectric();
    void importSymmectric();
    KeyLength keylengthFrom(const int index);

    void processEncText();
    void processDecText();
    void processEncFile(std::vector<std::string>& paths);
    void processDecFile(std::vector<std::string>& paths);
    void m_cipherNew(const std::string& alg, const std::string& mode);
    
    bool isFileExist(const std::string& filename) const;
    QMessageBox::ButtonRole dialogFileExists(const std::string& message);
    bool dialogInsertFilename(const std::string& message);
    bool dialogConfirm(const std::string& message);
    void dialogNoKeyMessage(const std::string& action);
    std::string dialogSave();

    void keyLoadedSelectable(const Qt::TextInteractionFlags flags) const;
    void setKeyLoadedStyle(const QString &style) const;
    void setFilesLoadedStyle(const QString &style) const;
    void setKeyLoadedText(const QString &keyStr) const;
    void setKeyLoadedSelectable(const bool selectable) const;

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_m_encTabFileImport_clicked();
    void on_m_decTabFileImport_clicked();
    void on_m_encTabFileEncrypt_clicked();
    void on_m_decTabFileDecrypt_clicked();
    void on_m_encTabFileClear_clicked();
    void on_m_decTabFileClear_clicked();

    void on_m_encTabTextEncrypt_clicked();
    void on_m_decTabTextDecrypt_clicked();
    void on_m_encTabTextReset_clicked();
    void on_m_decTabTextReset_clicked();

    void on_m_keyMGenerate_clicked();
    void on_m_keyMImport_clicked();
    void on_m_keyMDisable_toggled(bool checked);

    void setComboModes(const QString& alg);
    void hideKey(const bool isChecked);
    void colorKeyLoaded();
    void colorFilesLoaded();
    void flushKey();

    void recoverText(const std::string &recoverText);
    void cipherText(const std::string &cipherText);
    void cipherError(const std::string &error);
    void cipherKill();
    void processing(const int progress);
    void processKill();
    void dialogSuccess(const std::string& message);
    void dialogError(const std::string& message);

signals:
    void startEncFile(std::vector<std::string> paths, Keygen* keygen, const Encoding encoding);
    void startDecFile(std::vector<std::string> paths, Keygen* keygen, const Encoding encoding);
    void startEncText(const std::string& plain, Keygen* keygen, const Encoding encoding);
    void startDecText(const std::string& cipher, Keygen* keygen, const Encoding encoding);
    void startProcess(const int progress = 0);
};

#endif // MAINWINDOW_H
