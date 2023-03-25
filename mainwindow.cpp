#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "kActionBase.h"
#include "kActionKeyMgr.h"
#include "kActionEncrypt.h"
#include "kActionDecrypt.h"
#include "kActionQuit.h"
#include "cipherRsa.h"
#include "defines.h"
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
    m_actions.append(new KActionQuit());

    foreach (KActionBase* action, m_actions) {
        ui->m_toolBar->addAction(action);
        QObject::connect(action, &QAction::triggered, action, &KActionBase::onActionClick);
        QObject::connect(action, &KActionBase::quit, this, &QMainWindow::close);
        QObject::connect(action, &KActionBase::setStackPage, ui->m_mainStack, &QStackedWidget::setCurrentIndex);
    }

    setIconSize(QSize(35, 35));
}
void MainWindow::connectItems() {
    QObject::connect(ui->m_keyMAlg, &QComboBox::activated, this, &MainWindow::selectCipher);

}

// slots
void MainWindow::on_m_encryptBtn_clicked()
{
    m_cipher->isKeyLoaded() ?
        m_cipher->encrypt() :
        m_message->show(NO_KEY_MSG("encrypt"), ":/assets/error.png");
}
void MainWindow::on_m_decryptBtn_clicked()
{
    m_cipher->isKeyLoaded() ?
        m_cipher->decrypt() :
        m_message->show(NO_KEY_MSG("decrypt"), ":/assets/error.png");
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
void MainWindow::selectCipher(int alg) {
    if(m_cipher) delete m_cipher;
    switch(alg) {
    case Algorithm::aes: m_cipher = new CipherAes; break;
    case Algorithm::rsa: m_cipher = new CipherRsa; break;
    default: m_cipher = nullptr; break;
    }
}




