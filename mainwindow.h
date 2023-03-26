#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "kActionBase.h"
#include "cipherBase.h"
#include "aesGcm.h"
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
    CipherBase* m_cipher = new AesGCM;
    KMessage* m_message = new KMessage(this);
    QList<QString>* m_algorithms = new QList<QString>{"Symmectric - Aes", "Asymmetric - Rsa"};
    QList<QString>* m_aesModes = new QList<QString>{"GCM", "CCM", "EAX", "ECB", "CBC", "CBF", "OFB","CTR"};
    QList<QString>* m_rsaModes = new QList<QString>{"ES-OAEP-SHA", "SSA"};
    std::string m_selectedAlg = "";
    std::string m_selectedMode = "";

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
    void setAlgorithm(QString alg);
    void setMode(QString mode);
    void setModeList(int selectedAlg);
};
#endif // MAINWINDOW_H
