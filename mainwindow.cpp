#include "mainwindow.h"
#include "./ui_mainwindow.h"
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
    ui->m_keyMAlg->addItems(*m_algorithms);
    ui->m_keyMMode->addItems(*m_aesModes);

    connectItems();
    setIconSize(QSize(35, 35));
}

// destructor
MainWindow::~MainWindow()
{
    delete ui;
    delete m_cipher;
    delete m_aesModes;
    delete m_rsaModes;
    delete m_algorithms;
    foreach(KActionBase* action, m_actions)
        delete action;
}

// methods
void MainWindow::connectItems() {
    // connect comboboxes
    QObject::connect(ui->m_keyMAlg, &QComboBox::textActivated, this, &MainWindow::setAlgorithm);
    QObject::connect(ui->m_keyMMode, &QComboBox::textActivated, this, &MainWindow::setMode);

    // connect actions
    foreach (KActionBase* action, m_actions) {
        ui->m_toolBar->addAction(action);
        QObject::connect(action, &QAction::triggered, action, &KActionBase::onActionClick);
        QObject::connect(action, &KActionBase::quit, this, &QMainWindow::close);
        QObject::connect(action, &KActionBase::setStackPage, ui->m_mainStack, &QStackedWidget::setCurrentIndex);
    }
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

void MainWindow::setAlgorithm(const QString& alg) {

    delete m_cipher;
    ui->m_keyMMode->clear();

    if(alg == CipherAes::AlgName){
        m_cipher = new AesGCM;
        ui->m_keyMMode->addItems(*m_aesModes);
    }
    if(alg == CipherRsa::AlgName) {
        m_cipher = new RsaOEAP;
        ui->m_keyMMode->addItems(*m_rsaModes);
    }
}
void MainWindow::setMode(const QString& mode) {
    delete m_cipher;

    // aes modes
    if(mode == AesGCM::ModeName) m_cipher = new AesGCM;
    if(mode == AesGCM::ModeName) m_cipher = new AesGCM;
    if(mode == AesEAX::ModeName) m_cipher = new AesEAX;
    if(mode == AesGCM::ModeName) m_cipher = new AesGCM;
    if(mode == AesCBC::ModeName) m_cipher = new AesCBC;
    if(mode == AesGCM::ModeName) m_cipher = new AesGCM;
    if(mode == AesGCM::ModeName) m_cipher = new AesGCM;
    if(mode == AesGCM::ModeName) m_cipher = new AesGCM;

    // rsa modes
    if(mode == RsaOEAP::ModeName) m_cipher = new RsaOEAP;
    if(mode == RsaSSA::ModeName) m_cipher = new RsaSSA;


}




