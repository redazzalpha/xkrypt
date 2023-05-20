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
    delete m_algTypes;
    delete m_aesModes;
    delete m_rsaModes;
    delete m_aesKeysizes;
    delete m_rsaKeysizes;
    delete m_aesEncodings;
    delete m_rsaEncodings;
    delete m_aesText_encodings;

    foreach(AbstractAction* action, m_actions) delete action;
}

// private methods
void MainWindow::uiInit()
{
    ui->setupUi(this);
    initAlgorithms();
    initModes();
    initKeysizes();
    initEncodings();

    // tab widgets
    ui->m_encTab->setTabText(0, TAB_NAME_FILE);
    ui->m_encTab->setTabText(1, TAB_NAME_TEXT);
    ui->m_decTab->setTabText(0, TAB_NAME_FILE);
    ui->m_decTab->setTabText(1, TAB_NAME_TEXT);

    // comboxes
    ui->m_keyMSizes->addItems(*m_aesKeysizes);
    ui->m_keyMEncodingsI->addItems(*m_aesEncodings);
    ui->m_keyMEncodingsG->addItems(*m_aesEncodings);
    ui->m_keyMTypesI->addItems(*m_algTypes);
    ui->m_keyMTypesG->addItems(*m_algTypes);

    ui->m_encTabFileTypes->addItems(*m_algTypes);
    ui->m_encTabFileModes->addItems(*m_aesModes);
    ui->m_encTabFileEncodings->addItems(*m_aesEncodings);
    ui->m_decTabFileTypes->addItems(*m_algTypes);
    ui->m_decTabFileModes->addItems(*m_aesModes);
    ui->m_decTabFileEncodings->addItems(*m_aesEncodings);

    ui->m_encTabTextTypes->addItems(*m_algTypes);
    ui->m_encTabTextModes->addItems(*m_aesModes);
    ui->m_encTabTextEncodings->addItems(*m_aesText_encodings);
    ui->m_decTabTextTypes->addItems(*m_algTypes);
    ui->m_decTabTextModes->addItems(*m_aesModes);
    ui->m_decTabTextEncodings->addItems(*m_aesText_encodings);
}
void MainWindow::initAlgorithms()
{
    for(string& alg : m_algorithms) {
        m_algTypes->push_back(QString::fromStdString(alg));
    }
}
void MainWindow::initModes()
{
    for(pair<const string&, const string&> p : m_modes) {
        if(p.first == AbstractCipherAes::AlgName)
            m_aesModes->push_back(QString::fromStdString(p.second));
        if(p.first == AbstractCipherRsa::AlgName)
            m_rsaModes->push_back(QString::fromStdString(p.second));
    }
}
void MainWindow::initKeysizes()
{
    for(pair<const string&, const string&> p : m_keysizes) {
        if(p.first == AbstractCipherAes::AlgName)
            m_aesKeysizes->push_back(QString::fromStdString(p.second));
        if(p.first == AbstractCipherRsa::AlgName)
            m_rsaKeysizes->push_back(QString::fromStdString(p.second));
    }
}
void MainWindow::initEncodings()
{
    for(pair<const string&, const string&> p : m_encodings) {
        if(p.first == AbstractCipherAes::AlgName) {
            m_aesEncodings->push_back(QString::fromStdString(p.second));
            if(p.second != "None") m_aesText_encodings->push_back(QString::fromStdString(p.second));
        }
        if(p.first == AbstractCipherRsa::AlgName)
            m_rsaEncodings->push_back(QString::fromStdString(p.second));
    }
}
void MainWindow::connectItems()
{
    connectCipher();

    // connect combos
    QObject::connect(ui->m_encTabTextTypes, &QComboBox::textActivated, this, &MainWindow::setTypeCipher);
    QObject::connect(ui->m_decTabTextTypes, &QComboBox::textActivated, this, &MainWindow::setTypeCipher);
    QObject::connect(ui->m_encTabFileTypes, &QComboBox::textActivated, this, &MainWindow::setTypeCipher);
    QObject::connect(ui->m_decTabFileTypes, &QComboBox::textActivated, this, &MainWindow::setTypeCipher);
    QObject::connect(ui->m_keyMTypesG, &QComboBox::textActivated, this, &MainWindow::setTypeKey);
    QObject::connect(ui->m_keyMTypesI, &QComboBox::textActivated, this, &MainWindow::setTypeKey);

    // connect checkboxes
    QObject::connect(ui->m_keyMHide, &QCheckBox::clicked, this, &MainWindow::hideKey);
    QObject::connect(ui->m_encTabTextSaveOnF, &QCheckBox::stateChanged, this, &MainWindow::autoEncfname);

    // connect buttons
    QObject::connect(ui->m_keyMFlush, &QPushButton::clicked, this, &MainWindow::flushKey);

    // connect plain texts
    QObject::connect(ui->m_keyMLoaded, &QPlainTextEdit::textChanged, this, &MainWindow::colorKeyLoaded);
    QObject::connect(ui->m_encTabFileSelected, &QPlainTextEdit::textChanged, this, &MainWindow::colorFilesLoaded);
    QObject::connect(ui->m_decTabFileSelected, &QPlainTextEdit::textChanged, this, &MainWindow::colorFilesLoaded);

    // create and connect actions
    foreach (AbstractAction* action, m_actions) {
        ui->m_toolBar->addAction(action);
        QObject::connect(action, &QAction::triggered, action, &AbstractAction::onActionClick);
        QObject::connect(action, &AbstractAction::quit, this, &QMainWindow::close);
        QObject::connect(action, &AbstractAction::setStackPage, ui->m_mainStack, &QStackedWidget::setCurrentIndex);
        QObject::connect(action, &QAction::triggered, this, &MainWindow::actionSelected);
    }
}
void MainWindow::connectCipher()
{
    m_cipher.moveToThread(&m_threadCipher);
    QObject::connect(this, &MainWindow::startEncText, &m_cipher, &Cipher::encryptText);
    QObject::connect(this, &MainWindow::startDecText, &m_cipher, &Cipher::decryptText);
    QObject::connect(this, &MainWindow::startEncFile, &m_cipher, &Cipher::encryptFile);
    QObject::connect(this, &MainWindow::startDecFile, &m_cipher, &Cipher::decryptFile);

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
    QObject::connect(&m_cipher, &Cipher::autoDetect, this, &MainWindow::dectectFields);
    QObject::connect(&m_processBar, &ProcessBar::canceled, this, &MainWindow::cipherKill);
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
size_t MainWindow::keysizeFrom(const string& size)
{
    return QString::fromStdString(size).toInt();
}
Encoding MainWindow::encodingFrom(QComboBox* combo)
{
    Encoding encoding;
    string pattern = "Encodings";
    string comboName = combo->objectName().toStdString();
    int index = comboName.find(pattern);
    string type = comboName.substr(0, index);
    string section = comboName.substr(index + pattern.size());
    const QObject* parent = combo->parent();
    QComboBox*  comboType = parent->findChild<QComboBox*>(QString::fromStdString(type + "Types" + section));

    if(comboType->currentText() == QString::fromStdString(AbstractCipherAes::AlgName)) {
        switch(combo->currentIndex()) {
        case 0 :  encoding = Encoding::BASE64; break;
        case 1 : encoding = Encoding::HEX; break;
        case 2 : encoding = Encoding::NONE; break;
        default: throw EncodingException();
        }
    }
    else if(comboType->currentText() == QString::fromStdString(AbstractCipherRsa::AlgName)) {
        switch(combo->currentIndex()) {
        case 0 : encoding = Encoding::BER; break;
        case 1 : encoding = Encoding::DER; break;
        case 2 : encoding = Encoding::PEM; break;
        default: throw EncodingException();
        }
    }
    else throw EncodingException();

    return encoding;
}

Encoding MainWindow::encodingFrom2(QComboBox *combo)
{
    Encoding encoding;
    string pattern = "Encodings";
    string comboName = combo->objectName().toStdString();

    switch(combo->currentIndex()) {
    case 0 :  encoding = Encoding::BASE64; break;
    case 1 : encoding = Encoding::HEX; break;
    case 2 : encoding = Encoding::NONE; break;
    default: throw EncodingException();
    }

    return encoding;
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
void MainWindow::keyLoadedSelectable(const Qt::TextInteractionFlags flags) const
{
    ui->m_keyMLoaded->setTextInteractionFlags(flags);
    ui->m_encTabFileLoaded->setTextInteractionFlags(flags);
    ui->m_decTabFileLoaded->setTextInteractionFlags(flags);
    ui->m_encTabTextLoaded->setTextInteractionFlags(flags);
    ui->m_decTabTextLoaded->setTextInteractionFlags(flags);
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
    refs[2] = (CryptoPP::byte)encodingFrom(ui->m_encTabTextEncodings);
    refs[3] = (CryptoPP::byte)m_cipher.algId();
    refs[4] = (CryptoPP::byte)m_cipher.modeId();
    refs[5] = (CryptoPP::byte)m_cipher.encfname();

    return refs;
}
void MainWindow::closeEvent(QCloseEvent*)
{
    QMainWindow::close();
}
void MainWindow::importFile(FileImporter& fimporter, const string& caption)
{
    fimporter.importFiles(this, caption);

    stringstream ss;
    auto paths = fimporter.getFilePaths();

    if(paths.size() > 0)
        for(const string& path : fimporter.getFilePaths()) ss << path << "\n";
    else ss << NO_FILE_LOADED;

    if(caption.find("encrypt") < caption.size())
        ui->m_encTabFileSelected->setPlainText(QString::fromStdString(ss.str()));
    if(caption.find("decrypt") < caption.size())
        ui->m_decTabFileSelected->setPlainText(QString::fromStdString(ss.str()));
}

template<class T>
void MainWindow::generateKey()
{
    delete m_keygen;
    m_keygen = new T;

    const string& keysizeText = ui->m_keyMSizes->currentText().toStdString();
    const size_t keysize = keysizeFrom(keysizeText);

    m_keygen->generateKey(keysize, encodingFrom(ui->m_keyMEncodingsG));
    setKeyLoadedText(QString::fromStdString(m_kserial.serialize((T*)m_keygen)));

    if(ui->m_keyMSaveOnF->isChecked())
        saveKey<T>();
}
template<class T>
void MainWindow::saveKey()
{
    if(!dialogSave(this).empty()) {
        m_kserial.serialize(m_path, (T*)m_keygen);
        ui->m_keyMSaveOnF->setChecked(false);
        dialogSuccess(m_kserial.successWriteKey(m_path, m_keygen));
    }
}
template<class T>
void MainWindow::importKey(const string &caption)
{
    AbstractKeygen* keygen_cpy = m_keygen->keygenCpy();
    delete m_keygen;
    m_keygen = new T;

    try {
        m_fimporterKey.clear();
        Encoding encoding = encodingFrom(ui->m_keyMEncodingsI);
        ifstream* keyFile = (ifstream*)m_fimporterKey.importFile(this, caption);
        m_keygen->setEncoding(encoding);
        bool imported = m_kserial.deserialize(keyFile, (T*)m_keygen);
        if(m_keygen->isReady() && imported) {
            string keyStr = m_kserial.serialize((T*)m_keygen);
            setKeyLoadedText(QString::fromStdString(keyStr));
            delete keygen_cpy;

            stringstream ss;
            ss << "key "  << std::to_string(((T*)m_keygen)->keysize()) << " bytes ";
            ss << " - encoded " << m_kserial.serializeEncoding(encoding) << "<br />";
            ss << "has been successfully imported";
            dialogSuccess(ss.str());
        }
        else m_keygen = keygen_cpy;
    }
    catch(exception& e) {
        m_keygen = keygen_cpy;
        dialogError(e.what());
    }
}

// slots
void MainWindow::on_m_encTabTextEncrypt_clicked()
{
    try {
        if(!m_keygen->isReady()) throw UnreadyKeyException();
        string plainText = ui->m_encTabTextField->toPlainText().toStdString();

        if(plainText.empty()) throw EmptyTextException();
        string alg = ui->m_encTabTextTypes->currentText().toStdString();
        string mode = ui->m_encTabTextModes->currentText().toStdString();
        Encoding encoding = encodingFrom2(ui->m_encTabTextEncodings);

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
        string alg = ui->m_decTabTextTypes->currentText().toStdString();
        string mode = ui->m_decTabTextModes->currentText().toStdString();
        Encoding encoding = encodingFrom2(ui->m_decTabTextEncodings);
        
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
    importFile(m_fimporterEnc, "Select file(s) to encrypt");
}
void MainWindow::on_m_decTabFileImport_clicked()
{
    importFile(m_fimporterDec, "Select file(s) to decrypt");
}

void MainWindow::on_m_encTabFileEncrypt_clicked()
{
    try {
        vector<string> paths = m_fimporterEnc.getFilePaths();
        size_t size = paths.size();
        if(size < 1) throw FileSelectedException("-- error no file selected");

        string alg = ui->m_encTabFileTypes->currentText().toStdString();
        string mode = ui->m_encTabFileModes->currentText().toStdString();
        Encoding encoding = encodingFrom2(ui->m_encTabFileEncodings);
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
        vector<string> paths = m_fimporterDec.getFilePaths();
        size_t size = paths.size();
        if(size < 1) throw FileSelectedException("-- error no file selected");
        /*
         * useless cause of detect fields function
         * and refs system
        */
//      string alg = ui->m_decTabFileAlgs->currentText().toStdString();
//      string mode = ui->m_decTabFileModes->currentText().toStdString();
//      Encoding encoding = encodingFrom(ui->m_decTabFileEncodings);

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
    if(ui->m_keyMTypesG->currentText() == QString::fromStdString(AbstractCipherAes::AlgName))
        generateKey<KeygenAes>();
    if(ui->m_keyMTypesG->currentText() == QString::fromStdString(AbstractCipherRsa::AlgName))
        generateKey<KeygenRsa>();
}
void MainWindow::on_m_keyMImport_clicked()
{
    string type = ui->m_keyMTypesI->currentText().toStdString();
    if(type == AbstractCipherAes::AlgName) importKey<KeygenAes>("Import symmetric key");
    if(type == AbstractCipherRsa::AlgName) importKey<KeygenRsa>("Import asymmetric key");
}
void MainWindow::on_m_keyMDisable_toggled(bool checked)
{
    if(checked) m_warning = false;
    else m_warning = true;
}

void MainWindow::setTypeKey(const QString &type)
{
    QObject* sender = QObject::sender();
    QObject* parent = sender->parent();
    bool isImport = sender->objectName() == "m_keyMTypesI";
    string encodingName = "m_keyMEncodings" ;

    QComboBox* comboSizes = static_cast<QComboBox*>(parent->findChild<QComboBox*>("m_keyMSizes"));
    QComboBox* comboEncodings = static_cast<QComboBox*>(parent->findChild<QComboBox*>(QString::fromStdString(encodingName + (isImport? "I":"G"))));
    comboEncodings->clear();
    if(type.toStdString() == AbstractCipherAes::AlgName) {
        comboEncodings->addItems(*m_aesEncodings);
        if(!isImport){
            comboSizes->clear();
            comboSizes->addItems(*m_aesKeysizes);
        }
    }
    else if(type.toStdString() == AbstractCipherRsa::AlgName) {
        comboEncodings->addItems(*m_rsaEncodings);
        if(!isImport){
            comboSizes->clear();
            comboSizes->addItems(*m_rsaKeysizes);
        }
    }

}
void MainWindow::setTypeCipher(const QString& alg)
{
    QComboBox* sender = static_cast<QComboBox*>(QObject::sender());
    QObject* parent = sender->parent();
    string senderName = sender->objectName().toStdString();
    string modeName = senderName.substr(0, senderName.find("Types")) + "Modes";
    QComboBox* mode = parent->findChild<QComboBox*>(QString::fromStdString(modeName));

    mode->clear();
    if(alg.toStdString() == AbstractCipherAes::AlgName)
        mode->addItems(*m_aesModes);
    if(alg.toStdString() == AbstractCipherRsa::AlgName)
        mode->addItems(*m_rsaModes);
    autoEncfname();
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
void MainWindow::flushKey()
{
    m_keygen->flush();
    ui->m_keyMHide->setChecked(false);
    setKeyLoadedText(NO_KEY_LOADED);
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

void MainWindow::recoverText(const std::string &recoverText)
{
    try {
        if(ui->m_decTabTextSaveOnF->isChecked() && !dialogSave(this).empty()) {
            std::ofstream file(m_path, std::ios::out | std::ios::trunc);
            file << recoverText;
            file.close();
            dialogSuccess(m_cipher.successMsg(1, false) + "at " + m_path);
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
            dialogSuccess(m_cipher.successMsg() + "at " + m_path);
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
    Encoding encoding = encodingFrom(ui->m_decTabFileEncodings);
    dialogSuccess(success + " Encoding: " + m_kserial.serializeEncoding(encoding));
}
void MainWindow::cipherFile(const string& success)
{
    Encoding encoding = encodingFrom(ui->m_encTabFileEncodings);
    dialogSuccess(success + " Encoding: " + m_kserial.serializeEncoding(encoding));
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

void MainWindow::actionSelected()
{
    AbstractAction* sender = static_cast<AbstractAction*>(QObject::sender());
    AbstractAction* current = m_currentAction;
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

        m_currentAction = static_cast<AbstractAction*>(sender);
    }
}
void MainWindow::dectectFields(
    const string &alg,
    const string &mode,
    const Encoding encoding,
    const bool decfname)
{
    QComboBox* combo = ui->m_decTabFileModes;
    combo->clear();
    if(alg == AbstractCipherAes::AlgName) combo->addItems(*m_aesModes);
    if(alg == AbstractCipherRsa::AlgName) combo->addItems(*m_rsaModes);
    ui->m_decTabFileTypes->setCurrentText(QString::fromStdString(alg));
    ui->m_decTabFileModes->setCurrentText(QString::fromStdString(mode));
    ui->m_decTabFileEncodings->setCurrentText(QString::fromStdString(m_kserial.serializeEncoding(encoding)));
    ui->m_decTabFileDecFname->setChecked(decfname);
}

void MainWindow::autoEncfname()
{
    QObject* sender = QObject::sender();
    QObject* parent = sender->parent();
    string senderName = sender->objectName().toStdString();

    std::smatch match;
    std::regex regex (".*(Types|SaveOnF)$");
    std::regex_search (senderName, match, regex);

    string typeName = senderName.substr(0, senderName.find(match[1]));
    string checkboxName = typeName + "EncFname";
    string checkboxSName = typeName + "SaveOnF";
    string comboName = senderName.substr(0, senderName.find(match[1])) + "Types";
    QCheckBox* checkboxEncf = parent->findChild<QCheckBox*>(QString::fromStdString(checkboxName));
    QCheckBox* checkboxSaveOnF = parent->findChild<QCheckBox*>(QString::fromStdString(checkboxSName));
    QComboBox* comboType = parent->findChild<QComboBox*>(QString::fromStdString(comboName));
    bool checkedS = checkboxSaveOnF?checkboxSaveOnF->isChecked(): true;

    if(comboType->currentText() == QString::fromStdString(AbstractCipherAes::AlgName) && checkedS) {
        checkboxEncf->setChecked(true);
        checkboxEncf->setEnabled(true);
    }
    else if(comboType->currentText() == QString::fromStdString(AbstractCipherRsa::AlgName) && checkedS) {
        checkboxEncf->setChecked(false);
        checkboxEncf->setEnabled(false);
    }
    else {
        checkboxEncf->setChecked(false);
        checkboxEncf->setEnabled(false);
    }
}



