#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "aesgcm.h"
#include "aescbc.h"
#include "aeseax.h"
#include "kserial.h"
#include "keygen.h"
#include "rsassa.h"
#include "rsaoeap.h"
#include "enums.h"
#include "kactionkeyMgr.h"
#include "kactionencrypt.h"
#include "kactiondecrypt.h"
#include "kactionquit.h"
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
    KSerial m_ks;

    KeyGen* m_keygen = new KeyGen;
    CipherBase* m_cipher = new AesGCM;
    QList<QString>* m_algorithms = new QList<QString> {
        CipherAes::AlgName,
        CipherRsa::AlgName
    };
    QList<QString>* m_aesModes = new QList<QString>{
        AesGCM::ModeName,
        AesCBC::ModeName,
        AesEAX::ModeName
    };
    QList<QString>* m_rsaModes = new QList<QString>{
        RsaOEAP::ModeName,
        RsaSSA::ModeName,
    };
    QList<QString>* m_aesKeys = new QList<QString>{
        QString::number(static_cast<int>(KeyLength::LENGTH_DEFAULT)),
        QString::number(static_cast<int>(KeyLength::LENGTH_32)),
        QString::number(static_cast<int>(KeyLength::LENGTH_64)),
        QString::number(static_cast<int>(KeyLength::LENGTH_128)),
        QString::number(static_cast<int>(KeyLength::LENGTH_256)),
        QString::number(static_cast<int>(KeyLength::LENGTH_512)),
        QString::number(static_cast<int>(KeyLength::LENGTH_1024)),
        QString::number(static_cast<int>(KeyLength::LENGTH_2048)),
    };
    QList<QString>* m_encodings = new QList<QString>{
        "Base64",
        "Hex",
        "None",
    };
    QList<KActionBase*> m_actions = QList<KActionBase*> {
        new KActionKeyMgr(),
        new KActionEncrypt(),
        new KActionDecrypt(),
        new KActionQuit(),
    };

public:
    // constructors
    MainWindow(QWidget *parent = nullptr);

    // destructor
    ~MainWindow();

private:
    // methods
    void uiInit();
    void connectItems();
    void generateKey(const Encoding encoding);

    void dialogSuccessMessage(const std::string& message);
    void dialogErrorMessage(const std::string& message);
    void dialogNoKeyMessage(const std::string& action);

    void keyLoadedSelectable(const Qt::TextInteractionFlags flags);
    void setKeyLoadedStyle(const QString &style);
    void setKeyLoadedText(const QString &keyStr);
    void setKeyLoadedSelectable(const bool selectable);

private slots:
    void on_m_encTabFileEncrypt_clicked();
    void on_m_decTabFileDecrypt_clicked();
    void on_m_encTabFileImport_clicked();
    void on_m_decTabFileImport_clicked();

    void on_m_encTabTextEncrypt_clicked();
    void on_m_decTabTextDecrypt_clicked();
    void on_m_encTabTextReset_clicked();
    void on_m_decTabTextReset_clicked();

    void on_m_keyMGenerate_clicked();
    void on_m_keyMImport_clicked();

    void setAlgorithm(const QString& alg);
    void setMode(const QString& mode);
    void setKeyLength(const int index);
    void hideKey(const bool isChecked);
    void colorKey();
    void flushKey();
};
#endif // MAINWINDOW_H
