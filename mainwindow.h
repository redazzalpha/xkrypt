#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "kActionBase.h"
#include "cipherBase.h"
#include "kDialog.h"
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
    CipherBase* m_cipher = nullptr;
    KDialog* m_dialog = new KDialog(this);

public:
    // constructors
    MainWindow(QWidget *parent = nullptr);

    // destructor
    ~MainWindow();

private:
    void initToolBar();
    void initDialog();
    void connectItems();

private slots:
    void on_m_encryptBtn_clicked();
    void on_m_decryptBtn_clicked();
    void on_m_encryptSelectFBtn_clicked();
    void on_m_decryptSelectFBtn_clicked();
    void on_m_keyMGenerateBtn_clicked();
    void on_m_keyMImportBtn_clicked();
    void selectCipher(int);
};
#endif // MAINWINDOW_H
