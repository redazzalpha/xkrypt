#include "mainwindow.h"
#include "./ui_mainwindow.h"
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
    uiInit();
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
    foreach(KActionBase* action, m_actions) delete action;
}

// private methods
void MainWindow::uiInit()
{
    ui->setupUi(this);

    ui->m_encTab->setTabText(0, TAB_NAME_FILE);
    ui->m_encTab->setTabText(1, TAB_NAME_TEXT);
    ui->m_decTab->setTabText(0, TAB_NAME_FILE);
    ui->m_decTab->setTabText(1, TAB_NAME_TEXT);

    ui->m_encTabFileAlgs->addItems(*m_algorithms);
    ui->m_encTabFileModes->addItems(*m_aesModes);
    ui->m_encTabFileEncoding->addItems(*m_encodings);
    ui->m_decTabFileAlgs->addItems(*m_algorithms);
    ui->m_decTabFileModes->addItems(*m_aesModes);
    ui->m_decTabFileEncoding->addItems(*m_encodings);

    ui->m_encTabTextAlgs->addItems(*m_algorithms);
    ui->m_encTabTextModes->addItems(*m_aesModes);
    ui->m_encTabTextEncoding->addItems(*m_encodings);
    ui->m_decTabTextAlgs->addItems(*m_algorithms);
    ui->m_decTabTextModes->addItems(*m_aesModes);
    ui->m_decTabTextEncoding->addItems(*m_encodings);

    ui->m_keyMLength->addItems(*m_aesKeys);
    ui->m_keyMEncodingI->addItems(*m_encodings);
    ui->m_keyMEncodingG->addItems(*m_encodings);

}
void MainWindow::connectItems() const
{
    // connect comboboxes
    QObject::connect(ui->m_encTabFileAlgs, &QComboBox::textActivated, this, &MainWindow::setAlgorithm);
    QObject::connect(ui->m_encTabFileModes, &QComboBox::textActivated, this, &MainWindow::setMode);
    QObject::connect(ui->m_decTabFileAlgs, &QComboBox::textActivated, this, &MainWindow::setAlgorithm);
    QObject::connect(ui->m_decTabFileModes, &QComboBox::textActivated, this, &MainWindow::setMode);
    QObject::connect(ui->m_encTabTextAlgs, &QComboBox::textActivated, this, &MainWindow::setAlgorithm);
    QObject::connect(ui->m_encTabTextModes, &QComboBox::textActivated, this, &MainWindow::setMode);
    QObject::connect(ui->m_decTabTextAlgs, &QComboBox::textActivated, this, &MainWindow::setAlgorithm);
    QObject::connect(ui->m_decTabTextModes, &QComboBox::textActivated, this, &MainWindow::setMode);

    // connect checkboxes
    QObject::connect(ui->m_keyMHide, &QCheckBox::clicked, this, &MainWindow::hideKey);

    // connect buttons
    QObject::connect(ui->m_keyMFlush, &QPushButton::clicked, this, &MainWindow::flushKey);
    // connect plain texts
    QObject::connect(ui->m_keyMLoaded, &QPlainTextEdit::textChanged, this, &MainWindow::colorKey);

    // create and connect actions
    foreach (KActionBase* action, m_actions) {
        ui->m_toolBar->addAction(action);
        QObject::connect(action, &QAction::triggered, action, &KActionBase::onActionClick);
        QObject::connect(action, &KActionBase::quit, this, &QMainWindow::close);
        QObject::connect(action, &KActionBase::setStackPage, ui->m_mainStack, &QStackedWidget::setCurrentIndex);
    }
}
void MainWindow::generateKey(Encoding encoding)
{
    const int keylengthIndex = ui->m_keyMLength->currentIndex();
    const KeyLength keylength = keylengthFrom(keylengthIndex);

    m_keygen->setKeyLength(keylength);
    m_keygen->generateKey();

    setKeyLoadedText(QString::fromStdString(m_ks.keyToString(*m_keygen, encoding)));
}
void MainWindow::saveKeyOnFile(Encoding encoding) {
    if(m_ks.saveOnFile(*m_keygen,  encoding)) {
        string message = "key " + std::to_string(m_keygen->getKey().size()) + " bytes - encoded ";
        message += m_ks.encodingToString(encoding);
        message += "<br />has been successfully written on file<br />" + m_ks.getDir();
        dialogSuccessMessage(message);
        ui->m_keyMSaveOnF->setChecked(false);
    }
}
KeyLength MainWindow::keylengthFrom(const int index)
{
    KeyLength keylength;
    switch(index) {
    case 0 : keylength = KeyLength::LENGTH_DEFAULT; break;
    case 1 : keylength = KeyLength::LENGTH_32; break;
    case 2 : keylength = KeyLength::LENGTH_64; break;
    case 3 : keylength = KeyLength::LENGTH_128; break;
    case 4 : keylength = KeyLength::LENGTH_256; break;
    case 5 : keylength = KeyLength::LENGTH_512; break;
    case 6 : keylength = KeyLength::LENGTH_1024; break;
    case 7 : keylength = KeyLength::LENGTH_2048; break;
    default: keylength = static_cast<KeyLength>(0);
    }
    return keylength;
}

void MainWindow::dialogSuccessMessage(const string& message)
{
    string text = MESSAGE_SUCCESS_START+ message + MESSAGE_SUCCESS_END;
    QMessageBox msg(this);
    QPushButton* ok =  msg.addButton("Ok", QMessageBox::AcceptRole);

    msg.setWindowTitle("xKrypt - Success");
    msg.setWindowIcon(QIcon(QPixmap(ICON_ERROR)));
    msg.setText(QString::fromStdString(text));
    msg.setDefaultButton(ok);
    msg.setEscapeButton(ok);
    msg.setModal(true);
    msg.exec();
}
void MainWindow::dialogErrorMessage(const string& message)
{
    string text = MESSAGE_ERROR_START+ message + MESSAGE_ERROR_END;
    QMessageBox msg(this);
    QPushButton* ok =  msg.addButton("Ok", QMessageBox::AcceptRole);

    msg.setWindowTitle("xKrypt - Error");
    msg.setWindowIcon(QIcon(QPixmap(ICON_ERROR)));
    msg.setText(QString::fromStdString(text));
    msg.setDefaultButton(ok);
    msg.setEscapeButton(ok);
    msg.setModal(true);
    msg.exec();
}
void MainWindow::dialogNoKeyMessage(const string& action)
{
    string text = MESSAGE_NOKEY_START+ action + MESSAGE_NOKEY_END;
    QMessageBox msg(this);
    QPushButton* ok =  msg.addButton("Ok", QMessageBox::AcceptRole);

    msg.setWindowTitle("xKrypt - Error");
    msg.setWindowIcon(QIcon(QPixmap(ICON_ERROR)));
    msg.setText(QString::fromStdString(text));
    msg.setDefaultButton(ok);
    msg.setEscapeButton(ok);
    msg.setModal(true);
    msg.exec();
}

void MainWindow::keyLoadedSelectable(const Qt::TextInteractionFlags flags) const
{
    ui->m_keyMLoaded->setTextInteractionFlags(flags);
    ui->m_encTabFileLoaded->setTextInteractionFlags(flags);
    ui->m_decTabFileLoaded->setTextInteractionFlags(flags);
    ui->m_encTabTextLoaded->setTextInteractionFlags(flags);
    ui->m_decTabTextLoaded->setTextInteractionFlags(flags);
}
void MainWindow::setKeyLoadedStyle(const QString& style) const
{
    ui->m_keyMLoaded->setStyleSheet(style);
    ui->m_encTabFileLoaded->setStyleSheet(style);
    ui->m_decTabFileLoaded->setStyleSheet(style);
    ui->m_encTabTextLoaded->setStyleSheet(style);
    ui->m_decTabTextLoaded->setStyleSheet(style);
}
void MainWindow::setKeyLoadedText(const QString& keyStr) const
{
    ui->m_keyMLoaded->setPlainText(keyStr);
    ui->m_encTabFileLoaded->setPlainText(keyStr);
    ui->m_decTabFileLoaded->setPlainText(keyStr);
    ui->m_encTabTextLoaded->setPlainText(keyStr);
    ui->m_decTabTextLoaded->setPlainText(keyStr);
}
void MainWindow::setKeyLoadedSelectable(const bool selectable) const
{
    if(selectable)keyLoadedSelectable(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    else keyLoadedSelectable(Qt::NoTextInteraction);
}

// slots
void MainWindow::on_m_encTabFileEncrypt_clicked()
{
//    m_keygen->isKeyLoaded()?
//        m_cipher->encrypt():
//        dialogNoKeyMessage("encrypt");
}
void MainWindow::on_m_decTabFileDecrypt_clicked()
{
//    m_keygen->isKeyLoaded()?
//        m_cipher->decrypt():
//        dialogNoKeyMessage("decrypt");
}
void MainWindow::on_m_encTabFileImport_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"file(s) to encrypt", "", "All Files (*)");
}
void MainWindow::on_m_decTabFileImport_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"file(s) to decrypt", "", "All Files (*)");
}

void MainWindow::on_m_encTabTextEncrypt_clicked()
{
    try {
        if(m_keygen->isReady()) {
            string plain = ui->m_encTabTextField->toPlainText().toStdString();
            if(!plain.empty()) {
                Encoding encoding = static_cast<Encoding>(ui->m_encTabTextEncoding->currentIndex());
                string cipher = m_cipher->encrypt(*m_keygen, plain, encoding);
                ui->m_encTabTextField->setPlainText(QString::fromStdString(cipher));
            }
            else dialogErrorMessage("-- error: Cannot encrypt empty!");
        }
        else dialogNoKeyMessage("encypt");
    }
    catch(exception& e) {
        dialogErrorMessage(e.what());
    }
}
void MainWindow::on_m_decTabTextDecrypt_clicked()
{
    try {
        if(m_keygen->isReady()) {
            string cipher = ui->m_decTabTextField->toPlainText().toStdString();
            if(!cipher.empty()) {
                Encoding encoding = static_cast<Encoding>(ui->m_decTabTextEncoding->currentIndex());
                string recover = m_cipher->decrypt(*m_keygen, cipher, encoding);
                ui->m_decTabTextField->setPlainText(QString::fromStdString(recover));
            }
            else dialogErrorMessage("-- error: Cannot decrypt empty!");
        }
        else dialogNoKeyMessage("decrypt");
    }
    catch(exception& e) {
        dialogErrorMessage(e.what());
    }
}
void MainWindow::on_m_encTabTextReset_clicked()
{
    ui->m_encTabTextField->setPlainText("");
}
void MainWindow::on_m_decTabTextReset_clicked()
{
    ui->m_decTabTextField->setPlainText("");
}

void MainWindow::on_m_keyMGenerate_clicked()
{
    Encoding encoding = static_cast<Encoding>(ui->m_keyMEncodingG->currentIndex());
    generateKey(encoding);
    if(ui->m_keyMSaveOnF->isChecked())
        saveKeyOnFile(encoding);
}
void MainWindow::on_m_keyMImport_clicked()
{
    Encoding encoding = static_cast<Encoding>(ui->m_keyMEncodingI->currentIndex());
    try {
        bool imported = m_ks.importKeygen(m_keygen);
        if(m_keygen->isReady() && imported) {
            string keyStr = m_ks.keyToString(*m_keygen, encoding);
            setKeyLoadedText(QString::fromStdString(keyStr));
            colorKey();

            string message = "key " + std::to_string(m_keygen->getKey().size()) + " bytes - encoded ";
            message += m_ks.encodingToString(encoding);
            message += "<br />has been successfully imported";

            dialogSuccessMessage(message);
        }
    }
    catch(exception& e) {
        dialogErrorMessage(e.what());
    }
}

void MainWindow::setAlgorithm(const QString& alg)
{
    delete m_cipher;
    ui->m_encTabFileModes->clear();
    ui->m_keyMLength->clear();

    if(alg == CipherAes::AlgName){
//        ui->m_keyMLength->currentText().toInt();
        m_cipher = new AesGCM;
        ui->m_encTabFileModes->addItems(*m_aesModes);
        ui->m_keyMLength->addItems(*m_aesKeys);
        ui->m_keyMLength->setVisible(true);
    }
    if(alg == CipherRsa::AlgName) {
        m_cipher = new RsaOEAP;
        ui->m_encTabFileModes->addItems(*m_rsaModes);
        ui->m_keyMLength->setVisible(false);
    }
}
void MainWindow::setMode(const QString& mode)
{
    delete m_cipher;
//    ui->m_keyMLength->currentText().toInt();
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
void MainWindow::hideKey(const bool isChecked)
{
    bool isEmpty = ui->m_keyMLoaded->toPlainText() == QString::fromStdString(NO_KEY_LOADED);
    if(isChecked && !isEmpty) {
        setKeyLoadedStyle(STYLE_BLANK);
        setKeyLoadedSelectable(false);
    }
    else {
        if(isEmpty) setKeyLoadedStyle(STYLE_RED);
        else setKeyLoadedStyle(STYLE_NORMAL);
        setKeyLoadedSelectable(true);
    }
}
void MainWindow::colorKey()
{
    bool isEmpty = ui->m_keyMLoaded->toPlainText() == QString::fromStdString(NO_KEY_LOADED);
    if(ui->m_keyMHide->isChecked())
        setKeyLoadedStyle(STYLE_BLANK);
    else {
        if(isEmpty) setKeyLoadedStyle(STYLE_RED);
        else setKeyLoadedStyle(STYLE_NORMAL);
    }
}
void MainWindow::flushKey()
{
    m_keygen->flush();
    ui->m_keyMHide->setChecked(false);
    setKeyLoadedText(NO_KEY_LOADED);
}





