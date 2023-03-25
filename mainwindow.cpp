#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "kActionBase.h"
#include "kActionKeyMgr.h"
#include "kActionEncrypt.h"
#include "kActionDecrypt.h"
#include "cipherAes.h"
#include "cipherRsa.h"
#include <QToolButton>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QFileDialog>
#include <iostream>


// constructors
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initToolBar();
    initDialog();
    connectItems();
}

// destructor
MainWindow::~MainWindow()
{
    delete ui;
    delete m_cipher;
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
        ui->m_toolBar->addAction(action);
        QObject::connect(action, &QAction::triggered, action, &KActionBase::onActionClick);
        QObject::connect(action, &KActionBase::setStackPage, ui->m_mainStack, &QStackedWidget::setCurrentIndex);
    }

    setIconSize(QSize(40, 40));
}
void MainWindow::initDialog() {
    m_dialog->setModal(true);

}
void MainWindow::connectItems() {
    QObject::connect(ui->m_keyMAlg, &QComboBox::activated, this, &MainWindow::selectCipher);

}

// slots
void MainWindow::on_m_encryptBtn_clicked()
{
    if(m_cipher && m_cipher->isKeyLoaded()) m_cipher->encrypt();
    else {
        m_dialog->exec();
    }
}
void MainWindow::on_m_decryptBtn_clicked()
{
    m_cipher->decrypt();
}
void MainWindow::on_m_encryptSelectFBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"file(s) to encrypt", "", "All Files (*)");
}
void MainWindow::on_m_decryptSelectFBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"file(s) to decrypt", "", "All Files (*)");
}
void MainWindow::on_m_keyMGenerateBtn_clicked()
{
    m_cipher->generateKey();
}
void MainWindow::on_m_keyMImportBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Import key", "", "All Files (*)");
}
void MainWindow::selectCipher(int index) {
    if(m_cipher) delete m_cipher;
    switch(index) {
    case 0: m_cipher = new CipherAes; break;
    case 1: m_cipher = new CipherRsa; break;
    default: m_cipher = nullptr; break;
    }
}




