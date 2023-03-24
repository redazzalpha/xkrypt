#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "kActionBase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initToolBar();

private slots:
    void on_btn_importKey_clicked();
    void on_btn_selectFilesToDecrypt_clicked();
    void on_btn_selectFilesToEncrypt_clicked();
    void on_btn_generateKey_clicked();
    void on_btn_decrypt_clicked();
    void on_btn_encrypt_clicked();

private:
    Ui::MainWindow *ui;
    QList<KActionBase*> m_actions = QList<KActionBase*>();
};
#endif // MAINWINDOW_H
