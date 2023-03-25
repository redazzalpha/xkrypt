#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "kActionBase.h"
#include "cipherBase.h"
#include "cipherAes.h"
#include "kMessage.h"
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QList<KActionBase*> m_actions = QList<KActionBase*>();
    CipherBase* m_cipher = new CipherAes;
    KMessage* m_message = new KMessage(this);

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
    void selectCipher(int alg);
};
#endif // MAINWINDOW_H
