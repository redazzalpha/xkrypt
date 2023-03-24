#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "kActionBase.h"
#include "cipherBase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QList<KActionBase*> m_actions = QList<KActionBase*>();
    CipherBase* m_cipher;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initToolBar();

private slots:
};
#endif // MAINWINDOW_H
