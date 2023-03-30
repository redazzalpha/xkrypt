#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include "enums.h"
#include "defines.h"
#include <QToolButton>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QFileDialog>
#include <QInputDialog>
#include <iostream>
#include <fstream>

using namespace std;
using namespace CryptoPP;

// constructors
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,   m_ks(this)
{
    ui->setupUi(this);
    init();
    connectItems();
    setFixedSize(800, 600);
    setIconSize(QSize(35, 35));
}
// destructor
MainWindow::~MainWindow()
{
    delete ui;
    delete m_keygen;
    delete m_cipher;
    delete m_aesModes;
    delete m_rsaModes;
    delete m_algorithms;
    delete m_encodings;
    foreach(KActionBase* action, m_actions)
        delete action;
}

// private methods
void MainWindow::init() {
    ui->m_encAlgs->addItems(*m_algorithms);
    ui->m_encModes->addItems(*m_aesModes);
    ui->m_decAlgs->addItems(*m_algorithms);
    ui->m_decModes->addItems(*m_aesModes);
    ui->m_keyMLength->addItems(*m_aesKeys);
    ui->m_keyMEncodingI->addItems(*m_encodings);
    ui->m_keyMEncodingG->addItems(*m_encodings);
}
void MainWindow::connectItems() {
    // connect comboboxes
    QObject::connect(ui->m_encAlgs, &QComboBox::textActivated, this, &MainWindow::setAlgorithm);
    QObject::connect(ui->m_encModes, &QComboBox::textActivated, this, &MainWindow::setMode);
    QObject::connect(ui->m_decAlgs, &QComboBox::textActivated, this, &MainWindow::setAlgorithm);
    QObject::connect(ui->m_decModes, &QComboBox::textActivated, this, &MainWindow::setMode);
    QObject::connect(ui->m_keyMLength, &QComboBox::activated, this, &MainWindow::setKeyLength);

    // connect checkboxes
    QObject::connect(ui->m_keyMshowKey, &QCheckBox::clicked, this, &MainWindow::showKey);

    // connect buttons
    QObject::connect(ui->m_keyMFlush, &QPushButton::clicked, this, &MainWindow::flushKey);

    // connect plain texts
    QObject::connect(ui->m_keyMLoaded, &QPlainTextEdit::textChanged, this, &MainWindow::colorKey);

    // connect actions
    foreach (KActionBase* action, m_actions) {
        ui->m_toolBar->addAction(action);
        QObject::connect(action, &QAction::triggered, action, &KActionBase::onActionClick);
        QObject::connect(action, &KActionBase::quit, this, &QMainWindow::close);
        QObject::connect(action, &KActionBase::setStackPage, ui->m_mainStack, &QStackedWidget::setCurrentIndex);
    }
}

void MainWindow::dialogSuccessMessage(const string& message) {
    string text =
        "<td><img src=:/assets/success.png width=50 height=50/></td><td valign=middle>" +
        message +
        "</td>";
    QMessageBox msg(this);
    QPushButton* ok =  msg.addButton("Ok", QMessageBox::AcceptRole);

    msg.setWindowTitle("xKrypt - Success");
    msg.setWindowIcon(QIcon(QPixmap(":/assets/error.ico")));
    msg.setText(QString::fromStdString(text));
    msg.setDefaultButton(ok);
    msg.setEscapeButton(ok);
    msg.setModal(true);
    msg.exec();
}
void MainWindow::dialogErrorMessage(const string& message) {
    string text =
        "<td><img src=:/assets/error.png width=50 height=50/></td><td valign=middle>" +
        message +
        "</td>";
    QMessageBox msg(this);
    QPushButton* ok =  msg.addButton("Ok", QMessageBox::AcceptRole);

    msg.setWindowTitle("xKrypt - Error");
    msg.setWindowIcon(QIcon(QPixmap(":/assets/error.ico")));
    msg.setText(QString::fromStdString(text));
    msg.setDefaultButton(ok);
    msg.setEscapeButton(ok);
    msg.setModal(true);
    msg.exec();
}
void MainWindow::dialogNoKeyMessage(const string& action) {
    string text =
        "<td><img src=:/assets/error.png width=50 height=50/></td>"
        "<td valign=middle>Cannot " +
        action +
        " - No key loaded!<br />Please generate or import key and retry</td>";
    QMessageBox msg(this);
    QPushButton* ok =  msg.addButton("Ok", QMessageBox::AcceptRole);

    msg.setWindowTitle("xKrypt - Error");
    msg.setWindowIcon(QIcon(QPixmap(":/assets/error.ico")));
    msg.setText(QString::fromStdString(text));
    msg.setDefaultButton(ok);
    msg.setEscapeButton(ok);
    msg.setModal(true);
    msg.exec();
}

// slots
void MainWindow::on_m_encEncrypt_clicked()
{
//    m_keygen->isKeyLoaded()?
//        m_cipher->encrypt():
//        dialogNoKeyMessage("encrypt");
}
void MainWindow::on_m_decDecrypt_clicked()
{
//    m_keygen->isKeyLoaded()?
//        m_cipher->decrypt():
//        dialogNoKeyMessage("decrypt");
}
void MainWindow::on_m_encImport_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"file(s) to encrypt", "", "All Files (*)");
}
void MainWindow::on_m_decImport_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"file(s) to decrypt", "", "All Files (*)");
}
void MainWindow::on_m_keyMGenerate_clicked()
{
    SecByteBlock key = m_keygen->generateKey();
    Encoding encoding = static_cast<Encoding>(ui->m_keyMEncodingG->currentIndex());

    if(ui->m_keyMSaveOnF->isChecked()) m_ks.saveOnFile(key,  encoding);

    ui->m_keyMLoaded->setPlainText(QString::fromStdString(m_ks.keyToString(key, encoding)));

    ui->m_keyMSaveOnF->setChecked(false);
    dialogSuccessMessage("key " + std::to_string(m_keygen->getKeyLength()) + " bits has been successfully generated");
}
void MainWindow::on_m_keyMImport_clicked()
{
    Encoding encoding = static_cast<Encoding>(ui->m_keyMEncodingI->currentIndex());

    m_keygen->setKey(m_ks.importKey());
    if(m_keygen->isKeyLoaded())
        m_ks.keyToString(m_keygen->getKey(), encoding);

}

void MainWindow::setAlgorithm(const QString& alg) {

    delete m_cipher;
    ui->m_encModes->clear();
    ui->m_keyMLength->clear();

    if(alg == CipherAes::AlgName){
        ui->m_keyMLength->currentText().toInt();
        m_cipher = new AesGCM;
        ui->m_encModes->addItems(*m_aesModes);
        ui->m_keyMLength->addItems(*m_aesKeys);
        ui->m_keyMLength->setVisible(true);
    }
    if(alg == CipherRsa::AlgName) {
        m_cipher = new RsaOEAP;
        ui->m_encModes->addItems(*m_rsaModes);
        ui->m_keyMLength->setVisible(false);
    }
}
void MainWindow::setMode(const QString& mode) {
    delete m_cipher;
    ui->m_keyMLength->currentText().toInt();

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
void MainWindow::setKeyLength(const int index) {
    switch(index) {
    case 0 : m_keygen->setKeyLength(KeyLength::LENGTH_DEFAULT); break;
    case 1 : m_keygen->setKeyLength(KeyLength::LENGTH_32); break;
    case 2 : m_keygen->setKeyLength(KeyLength::LENGTH_64); break;
    case 3 : m_keygen->setKeyLength(KeyLength::LENGTH_128); break;
    case 4 : m_keygen->setKeyLength(KeyLength::LENGTH_256); break;
    case 5 : m_keygen->setKeyLength(KeyLength::LENGTH_512); break;
    case 6 : m_keygen->setKeyLength(KeyLength::LENGTH_1024); break;
    case 7 : m_keygen->setKeyLength(KeyLength::LENGTH_2048); break;
    default: m_keygen->setKeyLength(KeyLength::LENGTH_DEFAULT);
    }
}
void MainWindow::showKey(const bool isChecked) {
    bool isEmpty = ui->m_keyMLoaded->toPlainText() == QString::fromStdString(NO_KEY_LOADED);
    if(isChecked) {
        if(isEmpty) ui->m_keyMLoaded->setStyleSheet("background-color:rgba(0,0,0,0);color:red;");
        else ui->m_keyMLoaded->setStyleSheet("background-color:rgba(0,0,0,0);");
    }
    else ui->m_keyMLoaded->setStyleSheet("background-color:rgba(0,0,0,0); color:rgba(0,0,0,0)");
}
void MainWindow::colorKey() {
    bool isEmpty = ui->m_keyMLoaded->toPlainText() == QString::fromStdString(NO_KEY_LOADED);
    if(ui->m_keyMshowKey->isChecked()) {
        if(isEmpty) ui->m_keyMLoaded->setStyleSheet("background-color:rgba(0,0,0,0);color:red;");
        else ui->m_keyMLoaded->setStyleSheet("background-color:rgba(0,0,0,0);");
    }
    else ui->m_keyMLoaded->setStyleSheet("background-color:rgba(0,0,0,0); color:rgba(0,0,0,0)");
}
void MainWindow::flushKey() {
    m_keygen->flushKey();
    ui->m_keyMLoaded->setPlainText(NO_KEY_LOADED);
    ui->m_keyMshowKey->setChecked(true);
    colorKey();
}
