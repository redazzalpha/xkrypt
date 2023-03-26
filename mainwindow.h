#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "kActionBase.h"
#include "cipherBase.h"
#include "aesGcm.h"
#include "aesCbc.h"
#include "aesEax.h"
#include "rsaSsa.h"
#include "rsaOeap.h"
#include "kMessage.h"
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
    QList<KActionBase*> m_actions = QList<KActionBase*>();
    KMessage* m_message = new KMessage(this);
    std::string m_selectedAlg = "";
    std::string m_selectedMode = "";
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
        RsaSSA::ModeName,
        RsaOEAP::ModeName
    };

public:
    // constructors
    MainWindow(QWidget *parent = nullptr);

    // destructor
    ~MainWindow();

private:
    void initToolBar();
    void initMessage();
    void connectItems();

private slots:
    void on_m_encryptBtn_clicked();
    void on_m_decryptBtn_clicked();
    void on_m_encryptSelectFBtn_clicked();
    void on_m_decryptSelectFBtn_clicked();
    void on_m_keyMGenerateBtn_clicked();
    void on_m_keyMImportBtn_clicked();
    void setModeList(const int selectedAlg);
    void setAlgorithm(const QString& alg);
    void setMode(const QString& mode);
};
#endif // MAINWINDOW_H
