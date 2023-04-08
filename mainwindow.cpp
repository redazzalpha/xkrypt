#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "enums.h"
#include "defines.h"
#include "fileimporter.h"
#include "kexcept.h"
#include <QToolButton>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QFileDialog>
#include <QInputDialog>
#include <iostream>
#include <fstream>
#include <regex>


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
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setIconSize(QSize(WINDOW_ICON_WIDTH, WINDOW_ICON_HEIGHT));
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
        delete m_keyEncodings;
        foreach(KActionBase* action, m_actions) delete action;
    }

// private methods
void MainWindow::uiInit()
{
    ui->setupUi(this);

    // tab widgets
    ui->m_encTab->setTabText(0, TAB_NAME_FILE);
    ui->m_encTab->setTabText(1, TAB_NAME_TEXT);
    ui->m_decTab->setTabText(0, TAB_NAME_FILE);
    ui->m_decTab->setTabText(1, TAB_NAME_TEXT);

    // comboxes
    ui->m_keyMLength->addItems(*m_aesKeys);
    ui->m_keyMEncodingsI->addItems(*m_keyEncodings);
    ui->m_keyMEncodingsG->addItems(*m_keyEncodings);
    ui->m_keyMType->addItems(*m_algorithms);

    ui->m_encTabFileAlgs->addItems(*m_algorithms);
    ui->m_encTabFileModes->addItems(*m_aesModes);
    ui->m_encTabFileEncodings->addItems(*m_keyEncodings);
    ui->m_decTabFileAlgs->addItems(*m_algorithms);
    ui->m_decTabFileModes->addItems(*m_aesModes);
    ui->m_decTabFileEncodings->addItems(*m_keyEncodings);

    ui->m_encTabTextAlgs->addItems(*m_algorithms);
    ui->m_encTabTextModes->addItems(*m_aesModes);
    ui->m_encTabTextEncodings->addItems(*m_enc_dec_encodings);
    ui->m_decTabTextAlgs->addItems(*m_algorithms);
    ui->m_decTabTextModes->addItems(*m_aesModes);
    ui->m_decTabTextEncodings->addItems(*m_enc_dec_encodings);
}
void MainWindow::connectItems() const
{
    // connect combos
    QObject::connect(ui->m_encTabFileAlgs, &QComboBox::textActivated, this, &MainWindow::setAlgorithm);
    QObject::connect(ui->m_decTabFileAlgs, &QComboBox::textActivated, this, &MainWindow::setAlgorithm);
    QObject::connect(ui->m_encTabTextAlgs, &QComboBox::textActivated, this, &MainWindow::setAlgorithm);
    QObject::connect(ui->m_decTabTextAlgs, &QComboBox::textActivated, this, &MainWindow::setAlgorithm);

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
void MainWindow::importSymmectric()
{
    try {
        Encoding encoding = static_cast<Encoding>(ui->m_keyMEncodingsI->currentIndex());
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
void MainWindow::importAsymmectric()
{
}
void MainWindow::m_cipherFrom(const string& alg, const string& mode)
{
    delete m_cipher;
    m_cipher = nullptr;

    // aes algs
    if(QString::fromStdString(alg) == CipherAes::AlgName) {

        if(QString::fromStdString(mode) == AesCBC::ModeName) m_cipher = new AesCBC;
        if(QString::fromStdString(mode) == AesEAX::ModeName) m_cipher = new AesEAX;
        if(QString::fromStdString(mode) == AesGCM::ModeName) m_cipher = new AesGCM;
        if(QString::fromStdString(mode) == AesCCM::ModeName) m_cipher = new AesCCM;
        if(QString::fromStdString(mode) == AesGCM::ModeName) m_cipher = new AesGCM;
        if(QString::fromStdString(mode) == AesGCM::ModeName) m_cipher = new AesGCM;
        if(QString::fromStdString(mode) == AesGCM::ModeName) m_cipher = new AesGCM;
        if(QString::fromStdString(mode) == AesGCM::ModeName) m_cipher = new AesGCM;
    }

    // rsa algs
    if(QString::fromStdString(alg) == CipherRsa::AlgName) {
        if(QString::fromStdString(mode) == RsaOEAP::ModeName) m_cipher = new RsaOEAP;
        if(QString::fromStdString(mode) == RsaSSA::ModeName) m_cipher = new RsaSSA;
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
void MainWindow::on_m_encTabFileImport_clicked()
{
    string alg = ui->m_encTabFileAlgs->currentText().toStdString();
    string mode = ui->m_encTabFileModes->currentText().toStdString();
    Encoding encoding = static_cast<Encoding>(ui->m_encTabFileEncodings->currentIndex());
    m_cipherFrom(alg, mode);
    m_cipher->encryptFile(*m_keygen, encoding);
}
void MainWindow::on_m_decTabFileImport_clicked()
{
}
void MainWindow::on_m_encTabFileEncrypt_clicked()
{
}
void MainWindow::on_m_decTabFileDecrypt_clicked()
{
}

void MainWindow::on_m_encTabTextEncrypt_clicked()
{    
    try {
        if(!m_keygen->isReady()) throw UnreadyKeyException();
        string plainText = ui->m_encTabTextField->toPlainText().toStdString();

        if(plainText.empty()) throw EmptyTextException();
        string selectedAlg = ui->m_encTabTextAlgs->currentText().toStdString();
        string selectedMode = ui->m_encTabTextModes->currentText().toStdString();
        Encoding selectedEncoding = static_cast<Encoding>(ui->m_encTabTextEncodings->currentIndex());
        m_cipherFrom(selectedAlg, selectedMode);

        if(!m_cipher) throw BadCipherException();
        string cipherText = m_cipher->encryptText(*m_keygen, plainText, selectedEncoding);
        ui->m_encTabTextField->setPlainText(QString::fromStdString(cipherText));
    }
    catch(exception& e) {
        dialogErrorMessage(e.what());
    }

}
void MainWindow::on_m_decTabTextDecrypt_clicked()
{
    try {
        if(!m_keygen->isReady()) throw UnreadyKeyException();
        string cipherText = ui->m_decTabTextField->toPlainText().toStdString();

        if(cipherText.empty()) throw EmptyTextException();
        string selectedAlg = ui->m_decTabTextAlgs->currentText().toStdString();
        string selectedMode = ui->m_decTabTextModes->currentText().toStdString();
        Encoding selectedEncoding = static_cast<Encoding>(ui->m_decTabTextEncodings->currentIndex());
        m_cipherFrom(selectedAlg, selectedMode);

        if(!m_cipher) throw BadCipherException();
        string recoverText = m_cipher->decryptText(*m_keygen, cipherText, selectedEncoding);
        ui->m_decTabTextField->setPlainText(QString::fromStdString(recoverText));
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
    Encoding encoding = static_cast<Encoding>(ui->m_keyMEncodingsG->currentIndex());
    generateKey(encoding);
    if(ui->m_keyMSaveOnF->isChecked())
        saveKeyOnFile(encoding);
}
void MainWindow::on_m_keyMImport_clicked()
{
    QString type = ui->m_keyMType->currentText();
    if(type == CipherAes::AlgName) importSymmectric();
    if(type == CipherRsa::AlgName)importAsymmectric();
}

void MainWindow::setAlgorithm(const QString& alg)
{
    QComboBox* sender = static_cast<QComboBox*>(QObject::sender());
    QObject* parent = sender->parent();
    string senderName = sender->objectName().toStdString();
    string modeName = senderName.substr(0, senderName.find("Algs")) + "Modes";
    QComboBox* mode = parent->findChild<QComboBox*>(QString::fromStdString(modeName));

    mode->clear();
    if(alg == CipherAes::AlgName)
        mode->addItems(*m_aesModes);
    if(alg == CipherRsa::AlgName)
        mode->addItems(*m_rsaModes);
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







