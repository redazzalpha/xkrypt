#include "mainwindow.h"
#include "kChoice.h"
#include "kMessage.h"
#include "kInput.h"
#include "./ui_mainwindow.h"
#include "base64.h"
#include <QToolButton>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QFileDialog>
#include <iostream>

using namespace std;
using namespace CryptoPP;

// constructors
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->m_keyMAlgs->addItems(*m_algorithms);
    ui->m_keyMModes->addItems(*m_aesModes);
    ui->m_keyMKeys->addItems(*m_aesKeys);

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
    QObject::connect(ui->m_keyMAlgs, &QComboBox::textActivated, this, &MainWindow::setAlgorithm);
    QObject::connect(ui->m_keyMModes, &QComboBox::textActivated, this, &MainWindow::setMode);
    QObject::connect(ui->m_keyMKeys, &QComboBox::activated, this, &MainWindow::setKey);

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
        KMessage(this).show("Cannot ecnrypt - No key has not been loaded! \n Please load key or generate one and retry.", ":/assets/error.png");
        //m_message->show( "Cannot ecnrypt - No key has not been loaded! \n Please load key or generate one and retry.", ":/assets/error.png");
}
void MainWindow::on_m_decryptBtn_clicked()
{
    m_cipher->isKeyLoaded() ?
        m_cipher->decrypt() :
        KMessage(this).show("Cannot decrypt - No key has not been loaded! \n Please load key or generate one and retry.", ":/assets/error.png");
        //m_message->show( "Cannot decrypt - No key has not been loaded! \n Please load key or generate one and retry.", ":/assets/error.png");
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
    SecByteBlock key = m_cipher->generateKey();

    if(ui->m_keyMCheckBox->isChecked()) {
        QString dir = QFileDialog::getExistingDirectory(nullptr, "Select saving directory", "");
        if(!dir.isEmpty()) {
            string fname = dir.toStdString() + "/aes.key";

            if(!isFileExist(fname)) {
                FileSink* fs = new FileSink(fname.c_str());
                Base64Encoder encoderBase64(fs);
                encoderBase64.Put(key, key.size());
                encoderBase64.MessageEnd();
            }
            else {
                KChoice* choice = new KChoice(this);
                choice->setMessage("File already exists!\nWhat do you want to do?");
                choice->setBtnAcceptText("Rename file");
                choice->setBtnRejectText("Change directory");
                choice->addButton("Override file");
                choice->setIcon(":/assets/warning.png");

                choice->exec();



            }
        }
    }

    stringstream ss;
    FileSink* fs = new FileSink(ss);
    Base64Encoder encoderBase64(fs);

    encoderBase64.Put(key, key.size());
    encoderBase64.MessageEnd();

    ui->m_keyMKeyLoaded->setPlainText(QString::fromStdString(ss.str()));
    if(ui->m_keyMCheckBox->isChecked()) ui->m_keyMCheckBox->setChecked(false);
}
void MainWindow::on_m_keyMImportBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Import key", "", "All Files (*)");
}

void MainWindow::setAlgorithm(const QString& alg) {

    delete m_cipher;
    ui->m_keyMModes->clear();
    ui->m_keyMKeys->clear();

    if(alg == CipherAes::AlgName){
        int keyLength = ui->m_keyMKeys->currentText().toInt();
        m_cipher = new AesGCM(keyLength);
        ui->m_keyMModes->addItems(*m_aesModes);
        ui->m_keyMKeys->addItems(*m_aesKeys);
        ui->m_keyMKeys->setVisible(true);
    }
    if(alg == CipherRsa::AlgName) {
        m_cipher = new RsaOEAP;
        ui->m_keyMModes->addItems(*m_rsaModes);
        ui->m_keyMKeys->setVisible(false);
    }
}
void MainWindow::setMode(const QString& mode) {
    delete m_cipher;
    int keyLength = ui->m_keyMKeys->currentText().toInt();


    // aes modes
    if(mode == AesGCM::ModeName) m_cipher = new AesGCM(keyLength);
    if(mode == AesGCM::ModeName) m_cipher = new AesGCM(keyLength);
    if(mode == AesEAX::ModeName) m_cipher = new AesEAX(keyLength);
    if(mode == AesGCM::ModeName) m_cipher = new AesGCM(keyLength);
    if(mode == AesCBC::ModeName) m_cipher = new AesCBC(keyLength);
    if(mode == AesGCM::ModeName) m_cipher = new AesGCM(keyLength);
    if(mode == AesGCM::ModeName) m_cipher = new AesGCM(keyLength);
    if(mode == AesGCM::ModeName) m_cipher = new AesGCM(keyLength);

    // rsa modes
    if(mode == RsaOEAP::ModeName) m_cipher = new RsaOEAP;
    if(mode == RsaSSA::ModeName) m_cipher = new RsaSSA;
}
void MainWindow::setKey(const int keyLength) {
    switch(keyLength) {
    case CryptoPP::AES::DEFAULT_KEYLENGTH :
        break;
    case CryptoPP::AES::MAX_KEYLENGTH :
        break;
    default: break;
    }

}

bool MainWindow::isFileExist(std::string filename) {
    return std::fstream(filename).good();
}



