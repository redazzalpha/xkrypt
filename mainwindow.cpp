#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QToolButton>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <iostream>
#include "kActionBase.h"
#include "kActionKeyMgr.h"
#include "kActionEncrypt.h"
#include "kActionDecrypt.h"
#include <QFileDialog>

// constructors
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initToolBar();
}

// destructor
MainWindow::~MainWindow()
{
    delete ui;
    foreach(KActionBase* action, m_actions)
        delete action;
}

// methods
void MainWindow::initToolBar()
{
    m_actions.append(new KActionKeyMgr());
    m_actions.append(new KActionEncrypt());
    m_actions.append(new KActionDecrypt());

    foreach (KActionBase* action, m_actions) {
        ui->toolBar->addAction(action);
        QObject::connect(action, &QAction::triggered, action, &KActionBase::onActionClick);
        QObject::connect(action, &KActionBase::setStackPage, ui->mainStack, &QStackedWidget::setCurrentIndex);
    }

    setIconSize(QSize(40, 40));
}

// slots
void MainWindow::on_btn_importKey_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Import key", "", "All Files (*)");
}
void MainWindow::on_btn_selectFilesToDecrypt_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"file(s) to decrypt", "", "All Files (*)");
}
void MainWindow::on_btn_selectFilesToEncrypt_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"file(s) to decrypt", "", "All Files (*)");

}
void MainWindow::on_btn_generateKey_clicked()
{

}
void MainWindow::on_btn_decrypt_clicked()
{

}
void MainWindow::on_btn_encrypt_clicked()
{

}

