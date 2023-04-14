#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "enums.h"
#include "defines.h"
#include "except.h"
#include <QToolButton>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QGridLayout>
#include <QFileDialog>
#include <QInputDialog>
#include <iostream>
#include <fstream>
#include <regex>
#include <QProgressDialog>
#include <thread>

using namespace std;
using namespace CryptoPP;




class Foo {
public:
    void bar(vector<string>* paths, Encoding encoding, Keygen& keygen) {}

};

// constructors
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
    foreach(AbstractActionBase* action, m_actions) delete action;
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
    QObject::connect(ui->m_encTabFileAlgs, &QComboBox::textActivated, this, &MainWindow::setComboModes);
    QObject::connect(ui->m_decTabFileAlgs, &QComboBox::textActivated, this, &MainWindow::setComboModes);
    QObject::connect(ui->m_encTabTextAlgs, &QComboBox::textActivated, this, &MainWindow::setComboModes);
    QObject::connect(ui->m_decTabTextAlgs, &QComboBox::textActivated, this, &MainWindow::setComboModes);

    // connect checkboxes
    QObject::connect(ui->m_keyMHide, &QCheckBox::clicked, this, &MainWindow::hideKey);

    // connect buttons
    QObject::connect(ui->m_keyMFlush, &QPushButton::clicked, this, &MainWindow::flushKey);

    // connect plain texts
    QObject::connect(ui->m_keyMLoaded, &QPlainTextEdit::textChanged, this, &MainWindow::colorKeyLoaded);
    QObject::connect(ui->m_encTabFileSelected, &QPlainTextEdit::textChanged, this, &MainWindow::colorFilesLoaded);
    QObject::connect(ui->m_decTabFileSelected, &QPlainTextEdit::textChanged, this, &MainWindow::colorFilesLoaded);

    // create and connect actions
    foreach (AbstractActionBase* action, m_actions) {
        ui->m_toolBar->addAction(action);
        QObject::connect(action, &QAction::triggered, action, &AbstractActionBase::onActionClick);
        QObject::connect(action, &AbstractActionBase::quit, this, &QMainWindow::close);
        QObject::connect(action, &AbstractActionBase::setStackPage, ui->m_mainStack, &QStackedWidget::setCurrentIndex);
    }
}
void MainWindow::generateKey(Encoding encoding)
{
    const int keylengthIndex = ui->m_keyMLength->currentIndex();
    const KeyLength keylength = keylengthFrom(keylengthIndex);

    m_keygen->setKeyLength(keylength);
    m_keygen->generateKey();
    setKeyLoadedText(QString::fromStdString(m_serial.keyToString(*m_keygen, encoding)));
}
void MainWindow::progressEnc(vector<string>* paths)
{
    string alg = ui->m_encTabFileAlgs->currentText().toStdString();
    string mode = ui->m_encTabFileModes->currentText().toStdString();
    Encoding encoding = static_cast<Encoding>(ui->m_encTabFileEncodings->currentIndex());
    m_cipherNew(alg, mode);

    m_cipher->encryptFile(paths, m_keygen, encoding);
//    std::thread t(&AbstractCipherBase::encryptFile, m_cipher, paths, m_keygen, encoding);
//    t.join();
}
void MainWindow::progressDec(vector<string>* paths)
{
    string alg = ui->m_decTabFileAlgs->currentText().toStdString();
    string mode = ui->m_decTabFileModes->currentText().toStdString();
    const Encoding encoding = static_cast<Encoding>(ui->m_decTabFileEncodings->currentIndex());
    m_cipherNew(alg, mode);


    m_cipher->decryptFile(paths, m_keygen, encoding);
//    std::thread t(&AbstractCipherBase::decryptFile, m_cipher, paths, m_keygen, encoding);
//    t.join();
}

void MainWindow::saveOnFile(const Encoding encoding)
{
    bool m_override = false;
    bool m_create = false;
    bool m_changeDirectory = false;

    while(true) {
        if(!m_override && !m_create) m_dir = QFileDialog::getExistingDirectory(nullptr, "Select saving directory", "").toStdString();
        if(!m_dir.empty()) {
            bool canWrite = true;
            if(!m_override && !m_create && !m_changeDirectory) canWrite = dialogInsertFilename("Please insert filename");
            if(canWrite) {
                string dir = m_dir +  "/" + m_fname;
                if(!isFileExist(dir) || m_override) {
                    m_dir =  QString::fromStdString(dir).toStdString();
                    m_serial.keyToFile(m_dir, *m_keygen, encoding);
                    saveSuccess(encoding);
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
void MainWindow::saveSuccess(Encoding encoding) {
    string message = "key " + std::to_string(m_keygen->getKey().size()) + " bytes - encoded ";
    message += m_serial.encodingToString(encoding);
    message += "<br />has been successfully written on file<br />" + m_dir;
    dialogSuccessMessage(message);
    ui->m_keyMSaveOnF->setChecked(false);
}
void MainWindow::importSymmectric()
{
    try {
        m_fimporterKey.clear();
        Encoding encoding = static_cast<Encoding>(ui->m_keyMEncodingsI->currentIndex());
        bool imported = m_serial.importKeygen(m_keygen, (ifstream*)m_fimporterKey.importFile());
        if(m_keygen->isReady() && imported) {
            string keyStr = m_serial.keyToString(*m_keygen, encoding);
            setKeyLoadedText(QString::fromStdString(keyStr));

            string message = "key " + std::to_string(m_keygen->getKey().size()) + " bytes - encoded ";
            message += m_serial.encodingToString(encoding);
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
void MainWindow::m_cipherNew(const string& alg, const string& mode)
{
    delete m_cipher;
    m_cipher = nullptr;

    // aes algs
    if(alg == AbstractCipherAes::AlgName) {

        if(mode == AesCBC::ModeName) m_cipher = new AesCBC;
        else if(mode == AesEAX::ModeName) m_cipher = new AesEAX;
        else if(mode == AesGCM::ModeName) m_cipher = new AesGCM;
        else if(mode == AesCCM::ModeName) m_cipher = new AesCCM;
        else if(mode == AesGCM::ModeName) m_cipher = new AesGCM;
        else if(mode == AesGCM::ModeName) m_cipher = new AesGCM;
        else if(mode == AesGCM::ModeName) m_cipher = new AesGCM;
        else if(mode == AesGCM::ModeName) m_cipher = new AesGCM;
        // default. shouldn't go here but used to remove clang warnings
        else m_cipher = new AesCBC;
    }

    // rsa algs
    else if(alg == AbstractCipherRsa::AlgName) {
        if(mode == RsaOEAP::ModeName) m_cipher = new RsaOEAP;
        else if(mode == RsaSSA::ModeName) m_cipher = new RsaSSA;
        // default. shouldn't go here but used to remove clang warnings
        else m_cipher = new RsaOEAP;
    }

    // default. shouldn't go here but used to remove clang warnings
    else m_cipher = new AesCBC;
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

bool MainWindow::isFileExist(const string& filename) const
{
    return std::fstream(filename, ios::in | ios::binary).good();
}
QMessageBox::ButtonRole MainWindow::dialogFileExists(const string& message)
{
    if(m_warning) {
        string text = MESSAGE_FILE_EXISTS_START + message + MESSAGE_FILE_EXISTS_END;
        QMessageBox msg(this);
        QPushButton* changeDirectory =  msg.addButton("Change directory", QMessageBox::AcceptRole);
        QPushButton* override =  msg.addButton("Override file", QMessageBox::ApplyRole);
        QPushButton* create =  msg.addButton("Create file", QMessageBox::ActionRole);
        QPushButton* cancel =  msg.addButton("Cancel", QMessageBox::RejectRole);

        cancel->setVisible(false);
        msg.setWindowTitle("xKrypt - Warning");
        msg.setWindowIcon(QIcon(QPixmap(ICON_WARNING)));
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
    return QMessageBox::ApplyRole;
}
bool MainWindow::dialogInsertFilename(const string& message) {
    string text = MESSAGE_INSERT_FNAME_START + message + MESSAGE_INSERT_FNAME_END;
    QInputDialog input(this);
    bool isFnameInserted = false;
    m_fname = "";

    input.setWindowTitle("xKrypt - insert");
    input.setWindowIcon(QIcon(QPixmap(ICON_FILE)));
    input.setLabelText(QString::fromStdString(text));
    input.setFixedSize(500, 200);
    input.setModal(true);
    if(input.exec()) {
        m_fname = input.textValue().toStdString();
        isFnameInserted = true;
    }

    return isFnameInserted;
}
bool MainWindow::dialogConfirm(const string& message)
{
    bool isConfirmed = true;
    if(m_warning) {
        string text = MESSAGE_CONFIRM_START + message + MESSAGE_CONFIRM_END;
        QMessageBox msg(this);
        QPushButton* ok =  msg.addButton("Ok", QMessageBox::AcceptRole);
        QPushButton* cancel =  msg.addButton("Cancel", QMessageBox::RejectRole);

        msg.setWindowTitle("xKrypt - Warning");
        msg.setWindowIcon(QIcon(QPixmap(ICON_WARNING)));
        msg.setText(QString::fromStdString(text));
        msg.setDefaultButton(cancel);
        msg.setEscapeButton(cancel);
        msg.setModal(true);
        msg.exec();

        if(msg.clickedButton() == ok) isConfirmed = true;
    }

    return isConfirmed;
}
void MainWindow::dialogSuccessMessage(const string& message)
{
    if(m_warning) {
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
void MainWindow::setFilesLoadedStyle(const QString& style) const
{
    QPlainTextEdit* sender = static_cast<QPlainTextEdit*>(QObject::sender());
    sender->setStyleSheet(style);
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
    m_fimporterEnc.clear();
    m_fimporterEnc.importFiles();

    stringstream ss;
    auto paths = m_fimporterEnc.getFilePaths();
    if(paths.size() > 0)
        for(const string& path : paths) ss << path << "\n";
    else ss << NO_FILE_LOADED;
    ui->m_encTabFileSelected->setPlainText(QString::fromStdString(ss.str()));
}
void MainWindow::on_m_decTabFileImport_clicked()
{
    m_fimporterDec.clear();
    m_fimporterDec.importFiles();
    stringstream ss;
    auto paths = m_fimporterDec.getFilePaths();

    if(paths.size() > 0)
        for(const string& path : m_fimporterDec.getFilePaths()) ss << path << "\n";
    else ss << NO_FILE_LOADED;
    ui->m_decTabFileSelected->setPlainText(QString::fromStdString(ss.str()));
}

void MainWindow::on_m_encTabFileEncrypt_clicked()
{
    try {
        vector<string> paths = m_fimporterEnc.getFilePaths();
        size_t size = paths.size();
        if(size < 1) throw FileSelectedException();

        progressEnc(&paths);

        string message = "file(s) successfully encrypted!<br />";
        message += "Using: " + m_cipher->getAlgName() += (" - " + m_cipher->getModeName()) + " mode";
        dialogSuccessMessage(message);
    }
    catch(exception& e) {
        dialogErrorMessage(e.what());
    }
}
void MainWindow::on_m_decTabFileDecrypt_clicked()
{
    try {
        size_t size = 0;
        vector<string> paths = m_fimporterDec.getFilePaths();
        size =  paths.size();
        if(size < 1) throw FileSelectedException();

        progressDec(&paths);

        string message = "file(s) successfully decrypted!<br />";
        message += "Using: " + m_cipher->getAlgName() += (" - " + m_cipher->getModeName()) + " mode";
        dialogSuccessMessage(message);
    }
    catch(exception& e) {
        dialogErrorMessage(e.what());
    }
}
void MainWindow::on_m_encTabFileClear_clicked()
{
    m_fimporterEnc.clear();
    ui->m_encTabFileSelected->setPlainText(NO_FILE_LOADED);
}
void MainWindow::on_m_decTabFileClear_clicked()
{
    m_fimporterDec.clear();
    ui->m_decTabFileSelected->setPlainText(NO_FILE_LOADED);
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
        m_cipherNew(selectedAlg, selectedMode);

        if(!m_cipher) throw BadCipherException();
        string cipherText = m_cipher->encryptText(plainText, m_keygen, selectedEncoding);
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
        m_cipherNew(selectedAlg, selectedMode);

        if(!m_cipher) throw BadCipherException();
        string recoverText = m_cipher->decryptText(cipherText, m_keygen, selectedEncoding);
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
    if(ui->m_keyMSaveOnF->isChecked()) saveOnFile(encoding);
}
void MainWindow::on_m_keyMImport_clicked()
{
    string type = ui->m_keyMType->currentText().toStdString();
    if(type == AbstractCipherAes::AlgName) importSymmectric();
    if(type == AbstractCipherRsa::AlgName)importAsymmectric();
}
void MainWindow::on_m_keyMDisable_toggled(bool checked)
{
    if(checked) m_warning = false;
    else m_warning = true;
}

void MainWindow::setComboModes(const QString& alg)
{
    QComboBox* sender = static_cast<QComboBox*>(QObject::sender());
    QObject* parent = sender->parent();
    string senderName = sender->objectName().toStdString();
    string modeName = senderName.substr(0, senderName.find("Algs")) + "Modes";
    QComboBox* mode = parent->findChild<QComboBox*>(QString::fromStdString(modeName));

    mode->clear();
    if(alg.toStdString() == AbstractCipherAes::AlgName)
        mode->addItems(*m_aesModes);
    if(alg.toStdString() == AbstractCipherRsa::AlgName)
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
void MainWindow::colorKeyLoaded()
{
    QPlainTextEdit* sender = static_cast<QPlainTextEdit*>(QObject::sender());
    bool isEmpty = sender->toPlainText() == QString::fromStdString(NO_KEY_LOADED);
    if(ui->m_keyMHide->isChecked())
        setKeyLoadedStyle(STYLE_BLANK);
    else {
        if(isEmpty) setKeyLoadedStyle(STYLE_RED);
        else setKeyLoadedStyle(STYLE_NORMAL);
    }
}
void MainWindow::colorFilesLoaded()
{
    QPlainTextEdit* sender = static_cast<QPlainTextEdit*>(QObject::sender());
    bool isEmpty = sender->toPlainText() == QString::fromStdString(NO_FILE_LOADED);

    if(isEmpty) setFilesLoadedStyle(STYLE_RED);
    else setFilesLoadedStyle(STYLE_NORMAL);

}
void MainWindow::flushKey()
{
    m_keygen->flush();
    ui->m_keyMHide->setChecked(false);
    setKeyLoadedText(NO_KEY_LOADED);
}






