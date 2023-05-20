#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "aesgcm.h"
#include "aescbc.h"
#include "aeseax.h"
#include "keygen_serial.h"
#include "keygenaes.h"
#include "rsaoaep.h"
#include "enums.h"
#include "actionkeyMgr.h"
#include "actionencrypt.h"
#include "actiondecrypt.h"
#include "actionquit.h"
#include "aesccm.h"
#include "fileimporter.h"
#include "aesecb.h"
#include "aescfb.h"
#include "aesofb.h"
#include "cipher.h"
#include <QList>
#include <QString>
#include <QMessageBox>
#include <QThread>
#include <processbar.h>
#include <aesctr.h>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    Cipher m_cipher;
    QThread m_threadCipher;
    ProcessBar m_processBar;
    AbstractKeygen* m_keygen = new KeygenAes;
    Keygen_serial m_kserial;
    AbstractAction* m_currentAction;
    FileImporter m_fimporterEnc;
    FileImporter m_fimporterDec;
    FileImporter m_fimporterKey;
    std::string m_path;
    std::string m_dir;
    std::string m_fname;
    std::vector<std::string> m_algorithms = {
        AbstractCipherAes::AlgName,
        AbstractCipherRsa::AlgName,
    };
    std::multimap<std::string, std::string> m_modes = {
        {AbstractCipherAes::AlgName, AesCBC::ModeName},
        {AbstractCipherAes::AlgName, AesCCM::ModeName},
        {AbstractCipherAes::AlgName, AesCFB::ModeName},
        {AbstractCipherAes::AlgName, AesCTR::ModeName},
        {AbstractCipherAes::AlgName, AesEAX::ModeName},
        {AbstractCipherAes::AlgName, AesECB::ModeName},
        {AbstractCipherAes::AlgName, AesGCM::ModeName},
        {AbstractCipherAes::AlgName, AesOFB::ModeName},

        {AbstractCipherRsa::AlgName, RsaOAEP::ModeName},
    };
    std::multimap<std::string, std::string> m_keysizes = {
        {AbstractCipherAes::AlgName, std::to_string(static_cast<int>(Aes::KeySize::LENGTH_16))},
        {AbstractCipherAes::AlgName, std::to_string(static_cast<int>(Aes::KeySize::LENGTH_32))},

        {AbstractCipherRsa::AlgName, std::to_string(static_cast<int>(Rsa::KeySize::LENGTH_1024))},
        {AbstractCipherRsa::AlgName, std::to_string(static_cast<int>(Rsa::KeySize::LENGTH_2048))},
        {AbstractCipherRsa::AlgName, std::to_string(static_cast<int>(Rsa::KeySize::LENGTH_3072))},
        {AbstractCipherRsa::AlgName, std::to_string(static_cast<int>(Rsa::KeySize::LENGTH_4096))},
        {AbstractCipherRsa::AlgName, std::to_string(static_cast<int>(Rsa::KeySize::LENGTH_6144))},
    };
    std::multimap<std::string, std::string> m_encodings = {
        {AbstractCipherAes::AlgName, "Base64"},
        {AbstractCipherAes::AlgName, "Hex"},
        {AbstractCipherAes::AlgName, "None"},

        {AbstractCipherRsa::AlgName, "BER"},
        {AbstractCipherRsa::AlgName, "DER"},
        {AbstractCipherRsa::AlgName, "PEM"},
    };

    QList<AbstractAction*> m_actions = QList<AbstractAction*> {
        new ActionKeyMgr(),
        new ActionEncrypt(),
        new ActionDecrypt(),
        new ActionQuit(),
    };
    QList<QString>* m_algTypes = new QList<QString>;
    QList<QString>* m_aesModes = new QList<QString>;
    QList<QString>* m_rsaModes = new QList<QString>;
    QList<QString>* m_aesKeysizes = new QList<QString>;
    QList<QString>* m_rsaKeysizes = new QList<QString>;
    QList<QString>* m_aesEncodings = new QList<QString>;
    QList<QString>* m_rsaEncodings = new QList<QString>;
    QList<QString>* m_aesText_encodings = new QList<QString>;

    bool m_warning = true;
public:
    // constructors
    MainWindow(QWidget *parent = nullptr);

    // destructor
    ~MainWindow();

private:
    // methods
    void uiInit();
    void initAlgorithms();
    void initModes();
    void initKeysizes();
    void initEncodings();
    void connectItems();
    void connectCipher();
    void shortcuts();
    void toolTips();
    size_t keysizeFrom(const std::string &size);
    Encoding encodingFrom(QComboBox *combo);
    Encoding encodingFrom2(QComboBox *combo);

    bool isFileExist(const std::string& path) const;
    QMessageBox::ButtonRole dialogFileExists(const std::string& message);
    bool dialogInsertFilename(const std::string& message);
    bool dialogConfirm(const std::string& message, const std::string& description = "");
    void dialogNoKeyMessage(const std::string& action, const std::string& description = "");
    void dialogSuccess(const std::string& message, const std::string &description = "");
    void dialogError(const std::string& message, const std::string& description = "");
    std::string dialogSave(QWidget* parent = nullptr, const std::string& caption = "Select saving directory", const std::string& openDir = "");

    void setFilesLoadedStyle(const QString &style) const;
    void setKeyLoadedStyle(const QString &style) const;
    void setKeyLoadedText(const QString &keyStr) const;
    void setKeyLoadedSelectable(const bool selectable) const;
    void keyLoadedSelectable(const Qt::TextInteractionFlags flags) const;

    bool isRunningThread();
    std::string refsToString();
    void closeEvent(QCloseEvent* event) override;
    void importFile(FileImporter& fimporter, const std::string &caption);

    template <class T>
    void generateKey();
    template<class T>
    void saveKey();
    template <class T>
    void importKey(const std::string& caption);

private slots:
    void on_m_encTabTextEncrypt_clicked();
    void on_m_decTabTextDecrypt_clicked();
    void on_m_encTabTextReset_clicked();
    void on_m_decTabTextReset_clicked();

    void on_m_encTabFileImport_clicked();
    void on_m_decTabFileImport_clicked();

    void on_m_encTabFileEncrypt_clicked();
    void on_m_decTabFileDecrypt_clicked();
    void on_m_encTabFileClear_clicked();
    void on_m_decTabFileClear_clicked();

    void on_m_keyMGenerate_clicked();
    void on_m_keyMImport_clicked();
    void on_m_keyMDisable_toggled(bool checked);
    
    void setTypeKey(const QString & type);
    void setTypeCipher(const QString& alg);
    void hideKey(const bool isChecked);
    void flushKey();
    void colorKeyLoaded();
    void colorFilesLoaded();
    void autoEncfname1();

    void recoverText(const std::string &recoverText);
    void cipherText(const std::string &cipherText);
    void recoverFile(const std::string& success);
    void cipherFile(const std::string& success);
    void cipherError(const std::string &error);
    void cipherKill();

    void actionSelected();
    void dectectFields(
        const std::string& alg,
        const std::string& mode,
        const Encoding encoding,
        const bool decfname
    );

signals:
    void startEncText(const std::string& plain, AbstractKeygen* keygen, const Encoding encoding);
    void startDecText(const std::string& cipher, AbstractKeygen* keygen, const Encoding encoding);
    void startEncFile(std::vector<std::string> paths, AbstractKeygen* keygen, const Encoding encoding);
    void startDecFile(std::vector<std::string> paths, AbstractKeygen* keygen);
    void startProcess(const int progress = 0);
};

#endif // MAINWINDOW_H
