#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include "enums.h"
#include "defines.h"
#include "base64.h"
#include "hex.h"
#include "files.h"
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
{
    ui->setupUi(this);
    init();
    connectItems();
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

// methods
void MainWindow::init() {
    ui->m_keyMAlgs->addItems(*m_algorithms);
    ui->m_keyMModes->addItems(*m_aesModes);
    ui->m_keyMKeyLength->addItems(*m_aesKeys);
    ui->m_keyMKeyEncoding->addItems(*m_encodings);
}
void MainWindow::connectItems() {
    // connect comboboxes
    QObject::connect(ui->m_keyMAlgs, &QComboBox::textActivated, this, &MainWindow::setAlgorithm);
    QObject::connect(ui->m_keyMModes, &QComboBox::textActivated, this, &MainWindow::setMode);
    QObject::connect(ui->m_keyMKeyLength, &QComboBox::activated, this, &MainWindow::setKeyLength);
    QObject::connect(ui->m_keyMKeyEncoding, &QComboBox::activated, this, &MainWindow::setKeyEncoding);

    // connect checkboxes
    QObject::connect(ui->m_keyMshowKey, &QCheckBox::clicked, this, &MainWindow::showKey);

    // connect buttons
    QObject::connect(ui->m_keyMFlushBtn, &QPushButton::clicked, this, &MainWindow::flushKey);

    // connect plain texts
    QObject::connect(ui->m_keyMKeyLoaded, &QPlainTextEdit::textChanged, this, &MainWindow::colorKey);

    // connect actions
    foreach (KActionBase* action, m_actions) {
        ui->m_toolBar->addAction(action);
        QObject::connect(action, &QAction::triggered, action, &KActionBase::onActionClick);
        QObject::connect(action, &KActionBase::quit, this, &QMainWindow::close);
        QObject::connect(action, &KActionBase::setStackPage, ui->m_mainStack, &QStackedWidget::setCurrentIndex);
    }
}
bool MainWindow::isFileExist(string filename) {
    return std::fstream(filename).good();
}
void MainWindow::saveOnFile(SecByteBlock key) {
    m_override = false;
    m_create = false;
    m_changeDirectory = false;
    m_dir = "";
    m_fname = "";

    while(true) {
        if(!m_override && !m_create) m_dir = QFileDialog::getExistingDirectory(nullptr, "Select saving directory", "");
        if(!m_dir.isEmpty()) {
            bool canWrite = true;
            if(!m_override && !m_create && !m_changeDirectory) canWrite = dialogInsertFilename("Please insert filename");
            if(canWrite) {
                string dir = m_dir.toStdString() +  "/" + m_fname;
                if(!isFileExist(dir) || m_override) {
                    m_dir =  QString::fromStdString(dir);
                    writeKey(key);
                    break;
                }
                else {
                    QMessageBox::ButtonRole role = dialogFileExists("File already exists! What you want to do?");
                    if(role == QMessageBox::AcceptRole)  { m_changeDirectory = true; continue; }
                    if(role == QMessageBox::ApplyRole) { m_override = true; continue; }
                    if(role == QMessageBox::ActionRole) { m_create = true; continue; }
                    if(role == QMessageBox::RejectRole) break;
                }
            }
            else break;
        }
        else break;
    }
}

QMessageBox::ButtonRole MainWindow::dialogFileExists(const string& message) {
    string text = "<td><img src=:/assets/warning.png width=50 height=50/></td><td valign=middle>" + message + "</td>";
    QMessageBox msg(this);
    QPushButton* changeDirectory =  msg.addButton("Change directory", QMessageBox::AcceptRole);
    QPushButton* override =  msg.addButton("Override file", QMessageBox::ApplyRole);
    QPushButton* create =  msg.addButton("Create file", QMessageBox::ActionRole);
    QPushButton* cancel =  msg.addButton("Cancel", QMessageBox::RejectRole);

    cancel->setVisible(false);
    msg.setWindowTitle("xKrypt - Warning");
    msg.setWindowIcon(QIcon(QPixmap(":/assets/warning.ico")));
    msg.setText(QString::fromStdString(text));
    msg.setDefaultButton(changeDirectory);
    msg.setEscapeButton(cancel);
    msg.setModal(true);
    msg.exec();

    if(msg.clickedButton() == changeDirectory)
        return QMessageBox::AcceptRole;
    else if(msg.clickedButton() == override)
        return dialogConfirm("Are you sure you want to override file?<br />This operation cannot be undone!")? QMessageBox::ApplyRole : QMessageBox::RejectRole;
    else if(msg.clickedButton() == create)
        return dialogInsertFilename("Please insert filename")? QMessageBox::ActionRole: QMessageBox::RejectRole;
    else if(msg.clickedButton() == cancel)
        return QMessageBox::RejectRole;
    return QMessageBox::RejectRole;
}
bool MainWindow::dialogInsertFilename(const string& message) {
    string text = "<td><img src=:/assets/file.png width=50 height=50/></td><td valign=middle>" + message + "</td>";
    QInputDialog input(this);
    bool isFnameInserted = false;
    m_fname = "";

    input.setWindowTitle("xKrypt - insert");
    input.setWindowIcon(QIcon(QPixmap(":/assets/file.ico")));
    input.setLabelText(QString::fromStdString(text));
    input.setFixedSize(500, 200);
    input.setModal(true);
    if(input.exec()) {
        m_fname = input.textValue().toStdString();
        isFnameInserted = true;
    }

    return isFnameInserted;
}
bool MainWindow::dialogConfirm(const string& message) {
    string text = "<td><img src=:/assets/warning.png width=50 height=50/></td><td valign=middle>" + message +  "</td>";
    QMessageBox msg(this);
    QPushButton* ok =  msg.addButton("Ok", QMessageBox::AcceptRole);
    QPushButton* cancel =  msg.addButton("Cancel", QMessageBox::RejectRole);
    bool isConfirmed = false;

    msg.setWindowTitle("xKrypt - Warning");
    msg.setWindowIcon(QIcon(QPixmap(":/assets/warning.ico")));
    msg.setText(QString::fromStdString(text));
    msg.setDefaultButton(cancel);
    msg.setEscapeButton(cancel);
    msg.setModal(true);
    msg.exec();

    if(msg.clickedButton() == ok) isConfirmed = true;

    return isConfirmed;
}
void MainWindow::dialogSuccessMessage(const string& message) {
    string text = "<td><img src=:/assets/success.png width=50 height=50/></td><td valign=middle>" + message + "</td>";
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
    string text = "<td><img src=:/assets/error.png width=50 height=50/></td><td valign=middle>" + message + "</td>";
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
    string text = "<td><img src=:/assets/error.png width=50 height=50/></td><td valign=middle>Cannot " + action + " - No key loaded!<br />Please generate or import key and retry</td>";
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

void MainWindow::writeKey(SecByteBlock key) {
    FileSink* fs = new FileSink(m_dir.toStdString().c_str());
    BufferedTransformation* encoder;

    switch(m_encoding) {
    case Encoding::HEX : encoder = new HexEncoder(fs); break;
    case Encoding::BASE64 : encoder = new Base64Encoder(fs); break;
    case Encoding::BINARY : encoder = new Base64Encoder(fs); break;
    default : encoder = new HexEncoder(fs);
    }

    encoder->Put(key, key.size());
    encoder->MessageEnd();

    delete encoder;
    encoder = nullptr;
}
string MainWindow::keyTo(SecByteBlock key) {
    stringstream ss;
    FileSink* fs = new FileSink(ss);
    BufferedTransformation* encoder;

    switch(m_encoding) {
    case Encoding::HEX : encoder = new HexEncoder(fs); break;
    case Encoding::BASE64 : encoder = new Base64Encoder(fs); break;
    case Encoding::BINARY : encoder = new Base64Encoder(fs); break;
    default : encoder = new HexEncoder(fs);
    }

    encoder->Put(key, key.size());
    encoder->MessageEnd();

    delete encoder;
    encoder = nullptr;

    return ss.str();
}

// slots
void MainWindow::on_m_encryptBtn_clicked()
{
//    m_keygen->isKeyLoaded()?
//        m_cipher->encrypt():
//        dialogNoKeyMessage("encrypt");
}
void MainWindow::on_m_decryptBtn_clicked()
{
//    m_keygen->isKeyLoaded()?
//        m_cipher->decrypt():
//        dialogNoKeyMessage("decrypt");
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
    SecByteBlock key = m_keygen->generateKey();

    if(ui->m_keyMSaveOnF->isChecked()) saveOnFile(key);

    ui->m_keyMKeyLoaded->setPlainText(QString::fromStdString(keyTo(key)));

    ui->m_keyMSaveOnF->setChecked(false);
    dialogSuccessMessage("key " + std::to_string(m_keygen->getKeyLength()) + " bits has been successfully generated");
}
void MainWindow::on_m_keyMImportBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Import key", "", "All Files (*)");
}

void MainWindow::setAlgorithm(const QString& alg) {

    delete m_cipher;
    ui->m_keyMModes->clear();
    ui->m_keyMKeyLength->clear();

    if(alg == CipherAes::AlgName){
        ui->m_keyMKeyLength->currentText().toInt();
        m_cipher = new AesGCM;
        ui->m_keyMModes->addItems(*m_aesModes);
        ui->m_keyMKeyLength->addItems(*m_aesKeys);
        ui->m_keyMKeyLength->setVisible(true);
    }
    if(alg == CipherRsa::AlgName) {
        m_cipher = new RsaOEAP;
        ui->m_keyMModes->addItems(*m_rsaModes);
        ui->m_keyMKeyLength->setVisible(false);
    }
}
void MainWindow::setMode(const QString& mode) {
    delete m_cipher;
    ui->m_keyMKeyLength->currentText().toInt();

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
void MainWindow::setKeyEncoding(const int index) {
    switch(index) {
    case Encoding::HEX : m_encoding = Encoding::HEX; break;
    case Encoding::BASE64 : m_encoding = Encoding::BASE64; break;
    case Encoding::BINARY : m_encoding = Encoding::BINARY; break;
    default: m_encoding = Encoding::HEX;
    }
}
void MainWindow::showKey(bool isChecked) {
    bool isEmpty = ui->m_keyMKeyLoaded->toPlainText() == QString::fromStdString(NO_KEY_LOADED);
    if(isChecked) {
        if(isEmpty) ui->m_keyMKeyLoaded->setStyleSheet("background-color:rgba(0,0,0,0);color:red;");
        else ui->m_keyMKeyLoaded->setStyleSheet("background-color:rgba(0,0,0,0);");
    }
    else ui->m_keyMKeyLoaded->setStyleSheet("background-color:rgba(0,0,0,0); color:rgba(0,0,0,0)");
}
void MainWindow::colorKey() {
    bool isEmpty = ui->m_keyMKeyLoaded->toPlainText() == QString::fromStdString(NO_KEY_LOADED);
    if(ui->m_keyMshowKey->isChecked()) {
        if(isEmpty) ui->m_keyMKeyLoaded->setStyleSheet("background-color:rgba(0,0,0,0);color:red;");
        else ui->m_keyMKeyLoaded->setStyleSheet("background-color:rgba(0,0,0,0);");
    }
    else ui->m_keyMKeyLoaded->setStyleSheet("background-color:rgba(0,0,0,0); color:rgba(0,0,0,0)");
}
void MainWindow::flushKey() {
    m_keygen->flushKey();
    ui->m_keyMKeyLoaded->setPlainText(NO_KEY_LOADED);
    ui->m_keyMshowKey->setChecked(true);
    colorKey();
}
