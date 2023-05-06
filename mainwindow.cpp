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

using namespace std;
using namespace CryptoPP;

// constructors
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_processBar(this)
{
    uiInit();
    connectItems();
    shortcuts();
    toolTips();
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setIconSize(QSize(WINDOW_ICON_WIDTH, WINDOW_ICON_HEIGHT));
    m_currentAction = m_actions[0];
}

// destructor
MainWindow::~MainWindow()
{
    delete ui;
    delete m_keygen;
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
void MainWindow::connectItems()
{
    connectCipher();

    // connect combos
    QObject::connect(ui->m_encTabFileAlgs, &QComboBox::textActivated, this, &MainWindow::setComboModes);
    QObject::connect(ui->m_decTabFileAlgs, &QComboBox::textActivated, this, &MainWindow::setComboModes);
    QObject::connect(ui->m_encTabTextAlgs, &QComboBox::textActivated, this, &MainWindow::setComboModes);
    QObject::connect(ui->m_decTabTextAlgs, &QComboBox::textActivated, this, &MainWindow::setComboModes);

    // connect checkboxes
    QObject::connect(ui->m_keyMHide, &QCheckBox::clicked, this, &MainWindow::hideKey);
    QObject::connect(ui->m_encTabTextSaveOnF, &QCheckBox::stateChanged, this, &MainWindow::toogleEncFname);

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
        QObject::connect(action, &QAction::triggered, this, &MainWindow::actionSelected);

    }
}
void MainWindow::connectCipher()
{
    m_cipher.moveToThread(&m_threadCipher);
    QObject::connect(this, &MainWindow::startEncFile, &m_cipher, &Cipher::encryptFile);
    QObject::connect(this, &MainWindow::startDecFile, &m_cipher, &Cipher::decryptFile);
    QObject::connect(this, &MainWindow::startEncText, &m_cipher, &Cipher::encryptText);
    QObject::connect(this, &MainWindow::startDecText, &m_cipher, &Cipher::decryptText);

    QObject::connect(&m_cipher, &Cipher::recoverText, this, &MainWindow::recoverText);
    QObject::connect(&m_cipher, &Cipher::cipherText, this, &MainWindow::cipherText);
    QObject::connect(&m_cipher, &Cipher::recoverText, &m_threadCipher, &QThread::quit);
    QObject::connect(&m_cipher, &Cipher::cipherText, &m_threadCipher, &QThread::quit);

    QObject::connect(&m_cipher, &Cipher::recoverFile, this, &MainWindow::recoverFile);
    QObject::connect(&m_cipher, &Cipher::cipherFile, this, &MainWindow::cipherFile);
    QObject::connect(&m_cipher, &Cipher::recoverFile, &m_threadCipher, &QThread::quit);
    QObject::connect(&m_cipher, &Cipher::cipherFile, &m_threadCipher, &QThread::quit);

    QObject::connect(&m_cipher, &Cipher::error, this, &MainWindow::dialogError);
    QObject::connect(&m_cipher, &Cipher::error, &m_threadCipher, &QThread::quit);

    QObject::connect(&m_threadCipher, &QThread::started, &m_processBar, &ProcessBar::show);
    QObject::connect(&m_cipher, &Cipher::proceed, &m_processBar, &ProcessBar::proceed);
    QObject::connect(&m_cipher, &Cipher::recoverText, &m_processBar, &ProcessBar::hide);
    QObject::connect(&m_cipher, &Cipher::cipherText, &m_processBar, &ProcessBar::hide);
    QObject::connect(&m_cipher, &Cipher::recoverFile, &m_processBar, &ProcessBar::hide);
    QObject::connect(&m_cipher, &Cipher::cipherFile, &m_processBar, &ProcessBar::hide);
    QObject::connect(&m_cipher, &Cipher::error, &m_processBar, &ProcessBar::hide);

    QObject::connect(&m_cipher, &Cipher::processing, &m_processBar, &ProcessBar::processing);

    QObject::connect(&m_cipher, &Cipher::autoDetect, this, &MainWindow::autoDectectFields);

    QObject::connect(&m_processBar, &ProcessBar::canceled, this, &MainWindow::cipherKill);
}

void MainWindow::generateKey(Encoding encoding)
{
    const int keylengthIndex = ui->m_keyMLength->currentIndex();
    const KeyLength keylength = keylengthFrom(keylengthIndex);

    m_keygen->setKeyLength(keylength);
    m_keygen->generateKey();
    setKeyLoadedText(QString::fromStdString(m_serial.keyToString(*m_keygen, encoding)));
}
void MainWindow::shortcuts()
{
    m_actions[0]->setShortcut(QKeySequence("Alt+k"));
    m_actions[1]->setShortcut(QKeySequence("Alt+e"));
    m_actions[2]->setShortcut(QKeySequence("Alt+d"));
    m_actions[3]->setShortcut(QKeySequence("Alt+q"));
}
void MainWindow::toolTips()
{
    m_actions[0]->setToolTip("Alt+k");
    m_actions[1]->setToolTip("Alt+e");
    m_actions[2]->setToolTip("Alt+d");
}
void MainWindow::importSymmectric()
{
    try {
        m_fimporterKey.clear();
        Encoding encoding = static_cast<Encoding>(ui->m_keyMEncodingsI->currentIndex());
        bool imported = m_serial.importKeygen(m_keygen, (ifstream*)m_fimporterKey.importFile(this, "Import symmetric key"));
        if(m_keygen->isReady() && imported) {
            string keyStr = m_serial.keyToString(*m_keygen, encoding);
            setKeyLoadedText(QString::fromStdString(keyStr));

            string message = "key " + std::to_string(m_keygen->getKey().size()) + " bytes - encoded ";
            message += m_serial.encodingToString(encoding);
            message += "<br />has been successfully imported";
            dialogSuccess(message);
        }
    }
    catch(exception& e) {
        dialogError(e.what());
    }
}
void MainWindow::importAsymmectric()
{
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

bool MainWindow::isFileExist(const string& path) const
{
    std::fstream f(path, ios::in | ios::binary);
    bool exists = f.good();
    f.close();
    return exists;
}
QMessageBox::ButtonRole MainWindow::dialogFileExists(const string& message)
{
    if(m_warning) {
        string text = MESSAGE_FILE_EXISTS_START + message + MESSAGE_FILE_EXISTS_END;
        QMessageBox msg(this);
        QPushButton* changeDirectory =  msg.addButton("Change &directory", QMessageBox::AcceptRole);
        QPushButton* override =  msg.addButton("&Override file", QMessageBox::ApplyRole);
        QPushButton* create =  msg.addButton("&Create file", QMessageBox::ActionRole);
        QPushButton* cancel =  msg.addButton("Cancel", QMessageBox::RejectRole);

        changeDirectory->setShortcut(QKeySequence("Ctrl+d"));
        override->setShortcut(QKeySequence("Ctrl+o"));
        create->setShortcut(QKeySequence("Ctrl+c"));

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
bool MainWindow::dialogConfirm(const string& message, const string& description)
{
    bool isConfirmed = true;
    if(m_warning) {
        string text = MESSAGE_CONFIRM_START + message + MESSAGE_CONFIRM_END;
        QMessageBox msg(this);
        QPushButton* ok =  msg.addButton("&Ok", QMessageBox::AcceptRole);
        QPushButton* cancel =  msg.addButton("&Cancel", QMessageBox::RejectRole);

        ok->setShortcut(QKeySequence("Ctrl+o"));
        cancel->setShortcut(QKeySequence("Ctrl+c"));

        msg.setWindowTitle("xKrypt - Warning");
        msg.setWindowIcon(QIcon(QPixmap(ICON_WARNING)));
        msg.setText(QString::fromStdString(text));
        msg.setDetailedText(QString::fromStdString(description));
        msg.setDefaultButton(cancel);
        msg.setEscapeButton(cancel);
        msg.setModal(true);
        msg.exec();

        if(msg.clickedButton() == ok) isConfirmed = true;
    }

    return isConfirmed;
}
void MainWindow::dialogNoKeyMessage(const string& action, const string &description)
{
    string text = MESSAGE_NOKEY_START+ action + MESSAGE_NOKEY_END;
    QMessageBox msg(this);
    QPushButton* ok =  msg.addButton("Ok", QMessageBox::AcceptRole);

    msg.setWindowTitle("xKrypt - Error");
    msg.setWindowIcon(QIcon(QPixmap(ICON_ERROR)));
    msg.setText(QString::fromStdString(text));
    msg.setDetailedText(QString::fromStdString(description));
    msg.setDefaultButton(ok);
    msg.setEscapeButton(ok);
    msg.setModal(true);
    msg.exec();
}
void MainWindow::dialogSuccess(const string& message, const string& description)
{
    if(m_warning) {
        string text = MESSAGE_SUCCESS_START+ message + MESSAGE_SUCCESS_END;
        QMessageBox msg(this);
        QPushButton* ok =  msg.addButton("&Ok", QMessageBox::AcceptRole);

        ok->setShortcut(QKeySequence("Ctrl+o"));

        msg.setWindowTitle("xKrypt - Success");
        msg.setWindowIcon(QIcon(QPixmap(ICON_ERROR)));
        msg.setText(QString::fromStdString(text));
        msg.setDetailedText(QString::fromStdString(description));
        msg.setDefaultButton(ok);
        msg.setEscapeButton(ok);
        msg.setModal(true);
        msg.exec();
    }
}
void MainWindow::dialogError(const string &message, const string& description)
{
    string text = MESSAGE_ERROR_START+ message + MESSAGE_ERROR_END;
    QMessageBox msg(this);
    QPushButton* ok =  msg.addButton("O&k", QMessageBox::AcceptRole);

    ok->setShortcut(QKeySequence("Ctrl+o"));

    msg.setWindowTitle("xKrypt - Error");
    msg.setWindowIcon(QIcon(QPixmap(ICON_ERROR)));
    msg.setText(QString::fromStdString(text));
    msg.setDetailedText(QString::fromStdString(description));
    msg.setDefaultButton(ok);
    msg.setEscapeButton(ok);
    msg.setModal(true);
    msg.exec();
}
string MainWindow::dialogSave(QWidget* parent, const string& caption, const string& openDir)
{
    bool m_override = false;
    bool m_create = false;
    bool m_changeDirectory = false;
    m_path.clear();
    m_dir.clear();
    m_fname.clear();
    string dir, path;

    while(true) {
        if(!m_override && !m_create) dir = QFileDialog::getExistingDirectory(parent, QString::fromStdString(caption), QString::fromStdString(openDir)).toStdString();
        if(!dir.empty()) {
            bool canWrite = true;
            if(!m_override && !m_create && !m_changeDirectory) canWrite = dialogInsertFilename("Please insert filename");
            if(canWrite) {
                path = dir +  "/" + m_fname;
                if(!isFileExist(path) || m_override) {
                    m_path =  path;
                    m_dir = dir;
                    break;
                }
                else {
                    QMessageBox::ButtonRole role = dialogFileExists("File already exists! What you want to do?");
                    if(role == QMessageBox::AcceptRole)  { path.clear(); m_changeDirectory = true; continue; }
                    if(role == QMessageBox::ApplyRole) { m_override = true; continue; }
                    if(role == QMessageBox::ActionRole) { m_create = true; continue; }
                    if(role == QMessageBox::RejectRole) break;
                }
            }
            else break;
        }
        else break;
    }
    return m_path;
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

bool MainWindow::isRunningThread()
{
    return m_threadCipher.isRunning();
}
string MainWindow::refsToString()
{
    string refs;
    refs.resize(XKRYPT_REF_SIZE);
    refs[0] = XKRYPT_REF_VERSION;
    refs[1] = XKRYPT_REF_MODEL;
    refs[2] = (CryptoPP::byte)ui->m_encTabTextEncodings->currentIndex();
    refs[3] = (CryptoPP::byte)m_cipher.algId();
    refs[4] = (CryptoPP::byte)m_cipher.modeId();

    return refs;
}

// protected methods
void MainWindow::closeEvent(QCloseEvent*)
{
    QMainWindow::close();
}

// slots

void MainWindow::on_m_encTabTextEncrypt_clicked()
{
    try {
        if(!m_keygen->isReady()) throw UnreadyKeyException();
        string plainText = ui->m_encTabTextField->toPlainText().toStdString();

        if(plainText.empty()) throw EmptyTextException();
        string alg = ui->m_encTabTextAlgs->currentText().toStdString();
        string mode = ui->m_encTabTextModes->currentText().toStdString();
        Encoding encoding = static_cast<Encoding>(ui->m_encTabTextEncodings->currentIndex());
        
        m_cipher.cipherNew(alg, mode);
        m_cipher.setEncfname(false);

        m_processBar.setMax();
        m_threadCipher.start();
        emit startEncText(plainText, m_keygen, encoding);
    }
    catch(exception& e) {
        dialogError(e.what());
    }
}
void MainWindow::on_m_decTabTextDecrypt_clicked()
{
    try {
        if(!m_keygen->isReady()) throw UnreadyKeyException();
        string cipherText = ui->m_decTabTextField->toPlainText().toStdString();

        if(cipherText.empty()) throw EmptyTextException();
        string alg = ui->m_decTabTextAlgs->currentText().toStdString();
        string mode = ui->m_decTabTextModes->currentText().toStdString();
        Encoding encoding = static_cast<Encoding>(ui->m_decTabTextEncodings->currentIndex());
        
        m_cipher.cipherNew(alg, mode);

        m_processBar.setMax();
        m_threadCipher.start();
        emit startDecText(cipherText, m_keygen, encoding);
    }
    catch(exception& e) {
        dialogError(e.what());
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

void MainWindow::on_m_encTabFileImport_clicked()
{
    m_fimporterEnc.importFiles(this, "Select file(s) to encrypt");

    stringstream ss;
    auto paths = m_fimporterEnc.getFilePaths();

    if(paths.size() > 0)
        for(const string& path : paths) ss << path << "\n";
    else ss << NO_FILE_LOADED;
    ui->m_encTabFileSelected->setPlainText(QString::fromStdString(ss.str()));
}
void MainWindow::on_m_decTabFileImport_clicked()
{
    m_fimporterDec.importFiles(this, "Select file(s) to decrypt");

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
        if(size < 1) throw FileSelectedException("-- error no file selected");

        string alg = ui->m_encTabFileAlgs->currentText().toStdString();
        string mode = ui->m_encTabFileModes->currentText().toStdString();
        Encoding encoding = static_cast<Encoding>(ui->m_encTabFileEncodings->currentIndex());
        bool encFname = ui->m_encTabFileEncFname->isChecked();
        
        m_cipher.cipherNew(alg, mode);
        m_cipher.setEncfname(encFname);

        m_processBar.setMax(size);
        m_threadCipher.start();
        emit startEncFile(paths, m_keygen, encoding);
    }
    catch (std::exception& e) {
        dialogError(e.what());
    }
}
void MainWindow::on_m_decTabFileDecrypt_clicked()
{
    try {
        size_t size = 0;
        vector<string> paths = m_fimporterDec.getFilePaths();
        size =  paths.size();
        if(size < 1) throw FileSelectedException();

        string alg = ui->m_decTabFileAlgs->currentText().toStdString();
        string mode = ui->m_decTabFileModes->currentText().toStdString();
        bool decFname = ui->m_decTabFileDecFname->isChecked();

        m_cipher.setDecfname(decFname);
        m_processBar.setMax(size);
        m_threadCipher.start();
        emit startDecFile(paths, m_keygen);
    }
    catch (std::exception& e) {
        dialogError(e.what());
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

void MainWindow::on_m_keyMGenerate_clicked()
{
    Encoding encoding = static_cast<Encoding>(ui->m_keyMEncodingsG->currentIndex());
    generateKey(encoding);
    if(ui->m_keyMSaveOnF->isChecked()) {
        if(!dialogSave(this).empty()) {
            m_serial.keyToFile(m_path, *m_keygen, encoding);
            ui->m_keyMSaveOnF->setChecked(false);
            dialogSuccess(m_serial.writeSuccess(m_path, *m_keygen, encoding));
        }
    }
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

void MainWindow::recoverText(const std::string &recoverText)
{
    try {
        if(ui->m_decTabTextSaveOnF->isChecked() && !dialogSave(this).empty()) {
            std::ofstream file(m_path, std::ios::out | std::ios::trunc);
            file << recoverText;
            file.close();
            dialogSuccess(m_cipher.successDecMsg() + "at " + m_path);
        }
        ui->m_decTabTextSaveOnF->setChecked(false);
        ui->m_decTabTextField->setPlainText(QString::fromStdString(recoverText));
    }
    catch(std::exception& e) {
        dialogError(e.what());
    }
}
void MainWindow::cipherText(const std::string &cipherText)
{
    string description;
    try {
        if(ui->m_encTabTextSaveOnF->isChecked() && !dialogSave(this).empty()) {
            if(ui->m_encTabTextEncFname->isChecked()) {
                m_cipher.setEncfname(true);
                m_path = m_dir + DELIMITOR + m_cipher.encryptText(m_fname, m_keygen, Encoding::HEX);
            }
            if(isFileExist(m_path)){
                description = "-- This error has been occured cause the file you're trying to create using \"Encrypt filename\" mode already exists.\n\n"\
                    "-- In this mode override files is not allowed.\n\n"\
                    "-- Please retry modifying the filename or change directory.";
                throw FileSelectedException("-- error: wrong path file<br />Encrypted filename already exists");
            }
            std::ofstream file(m_path, std::ios::out | std::ios::trunc);
            file << m_cipher.encodeText(refsToString(), Encoding::BASE64);;
            file << cipherText;
            file.close();
            dialogSuccess(m_cipher.successEncMsg() + "at " + m_path);
        }
        ui->m_encTabTextSaveOnF->setChecked(false);
        ui->m_encTabTextField->setPlainText(QString::fromStdString(cipherText));
    }
    catch(std::exception& e) {
        dialogError(e.what(), description);
    }
}
void MainWindow::recoverFile(const string& success)
{
    Encoding encoding = static_cast<Encoding>(ui->m_decTabFileEncodings->currentIndex());
    ui->m_decTabFileDecFname->setChecked(true);
    dialogSuccess(success + " Encoding: " + m_serial.encodingToString(encoding));
}
void MainWindow::cipherFile(const string& success)
{
    Encoding encoding = static_cast<Encoding>(ui->m_encTabFileEncodings->currentIndex());
    ui->m_encTabFileEncFname->setChecked(true);
    dialogSuccess(success + " Encoding: " + m_serial.encodingToString(encoding));
}
void MainWindow::cipherError(const std::string& error)
{
    char* msg = new char[error.size()];
    for(size_t i = 0; i < error.size(); i++) msg[i] = error[i];
    throw CipherException(msg);
}
void MainWindow::cipherKill()
{
    m_cipher.kill();
}

void MainWindow::toogleEncFname(bool checked)
{
    ui->m_encTabTextEncFname->setChecked(checked);
    ui->m_encTabTextEncFname->setEnabled(checked);
}
void MainWindow::actionSelected()
{
    AbstractActionBase* sender = static_cast<AbstractActionBase*>(QObject::sender());
    AbstractActionBase* current = m_currentAction;
    if(sender != current) {
        string senderPath = sender->iconPath();
        string currentPath = current->iconPath();
        string iconPath;
        int len;

        len = currentPath.size() - strlen(IMG_SELECTED_SUFFIX);
        iconPath = currentPath.substr(0, len) + IMG_UNSELECTED_SUFFIX;
        current->setIcon(iconPath);

        len = senderPath.size() - strlen(IMG_UNSELECTED_SUFFIX);
        iconPath = senderPath.substr(0, len) + IMG_SELECTED_SUFFIX;
        sender->setIcon(iconPath);

        m_currentAction = static_cast<AbstractActionBase*>(sender);
    }
}

void MainWindow::disable()
{
    setDisabled(true);
}
void MainWindow::enable()
{
    setDisabled(false);
}
void MainWindow::autoDectectFields(const string &alg, const string &mode, const Encoding encoding)
{
    QComboBox* combo = ui->m_decTabFileModes;
    combo->clear();
    if(alg == AbstractCipherAes::AlgName) combo->addItems(*m_aesModes);
    if(alg == AbstractCipherRsa::AlgName) combo->addItems(*m_rsaModes);
    ui->m_decTabFileAlgs->setCurrentText(QString::fromStdString(alg));
    ui->m_decTabFileModes->setCurrentText(QString::fromStdString(mode));
    ui->m_decTabFileEncodings->setCurrentText(QString::fromStdString(m_serial.encodingToString(encoding)));
}


