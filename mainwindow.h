#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "kActionBase.h"
#include "aesGcm.h"
#include "aesCbc.h"
#include "aesEax.h"
#include "rsaSsa.h"
#include "kActionKeyMgr.h"
#include "kActionEncrypt.h"
#include "kActionDecrypt.h"
#include "kActionQuit.h"
//#include "kMessage.h"
#include "rsaOeap.h"
#include <QMainWindow>
#include <QList>
#include <QString>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    bool m_genLoop = true;
    bool m_genOverride = false;
    QString m_dir;

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
        QString::number(CryptoPP::AES::DEFAULT_KEYLENGTH),
        QString::number(CryptoPP::AES::MAX_KEYLENGTH),
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
    void connectItems();
    bool isFileExist(std::string filename);

    void dialogFileExists();
    void dialogRenameFile();
    void dialogWarning(const std::string& message);
    void dialogError(const std::string& message);
    void dialogNoKeyError(const std::string& action);


private slots:
    void on_m_encryptBtn_clicked();
    void on_m_decryptBtn_clicked();
    void on_m_encryptSelectFBtn_clicked();
    void on_m_decryptSelectFBtn_clicked();
    void on_m_keyMGenerateBtn_clicked();
    void on_m_keyMImportBtn_clicked();
    void setAlgorithm(const QString& alg);
    void setMode(const QString& mode);
    void setKey(const int keyLength);
};
#endif // MAINWINDOW_H
