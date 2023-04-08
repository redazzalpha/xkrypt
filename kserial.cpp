#include "kserial.h"
#include "base64.h"
#include "defines.h"
#include "files.h"
#include "hex.h"
#include "qinputdialog.h"
#include "qpushbutton.h"
#include "kexcept.h"
#include <QFileDialog>
#include <fstream>
#include<vector>
#include <bits/streambuf_iterator.h>
using namespace CryptoPP;
using namespace std;

// constructors
KSerial::KSerial(QMainWindow* parent): m_parent(parent){};

// methods
string KSerial::getDir() const {
    return m_dir.toStdString();
}
string KSerial::encodingToString(const Encoding encoding) const
{
    string encodingStr;
    switch(static_cast<int>(encoding))  {
    case Encoding::BASE64: return "Base64";
    case Encoding::HEX: return "Hex";
    case Encoding::NONE: return "None";
    default: return "Unknown";
    }
}
bool KSerial::saveOnFile(KeyGen& keygen, const Encoding encoding)
{
    bool written = false;
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
                    keyToFile(keygen, encoding);
                    written = true;
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
    return written;
}
bool KSerial::importKeygen(KeyGen* keygen) noexcept(false)
{
    bool imported = false;
    m_dir = QFileDialog::getOpenFileName(m_parent,"Import key", "", "All Files (*)");

    if(!m_dir.isEmpty()) {
        ifstream f(m_dir.toStdString(), ios::binary | ios::in);
        if(f.good()) {
            size_t ivsize = static_cast<size_t>(IvLength::LENGTH_DEFAULT);
            string refs, keyiv;
            FileSource fs(f, false);

            fs.Attach(new StringSink(refs));
            fs.Pump(XKRYPT_REF_SIZE);

            if((refs[0] < XKRYPT_REF_VERSION)) throw VersionException();
            if( (refs[1] != XKRYPT_REF_MODEL)) throw ModelException();

            switch(refs[2]) {
            case Encoding::BASE64 : fs.Detach(new Base64Decoder); break;
            case Encoding::HEX : fs.Detach(new HexDecoder); break;
            case Encoding::NONE : fs.Detach(); break;
            default : throw EncodingException();
            }

            fs.Attach(new StringSink(keyiv));
            fs.PumpAll();

            keygen->setIv(SecByteBlock((uchar*) &keyiv[0], ivsize));
            keygen->setKey(SecByteBlock((uchar*) &keyiv[ivsize], keyiv.size() - ivsize));

            imported = true;
        }
    }
    return imported;
}
string KSerial::keyToString(KeyGen& keygen, const Encoding encoding)
{
    StringSource keySource(keygen.getKey().BytePtr(), keygen.getKey().size(), false);
    string key;

    switch(encoding) {
    case Encoding::BASE64 :
        keySource.Attach(new Base64Encoder);
        break;
    case Encoding::HEX :
        keySource.Attach(new HexEncoder);
    case Encoding::NONE :
        break;
    default :
        keySource.Attach(new Base64Encoder);
        break;
    }

    keySource.Attach(new StringSink(key));
    keySource.PumpAll();
    return key;
}

// private methods
void KSerial::keyToFile(KeyGen& keygen, const Encoding encoding) const
{
    size_t ivSize = keygen.getIv().size();
    size_t keySize = keygen.getKey().size();
    size_t keyIvSize = ivSize + keySize;
    std::vector<CryptoPP::byte> xkrypt_refs {
        XKRYPT_REF_VERSION,
        XKRYPT_REF_MODEL,
        (CryptoPP::byte)encoding,
    };
    CryptoPP::byte* keyIv = new CryptoPP::byte[keyIvSize];
    StringSource refsSource(&xkrypt_refs[0], xkrypt_refs.size(),false);
    StringSource keyIvSource(keyIv, keyIvSize, false);
    FileSink fs(m_dir.toStdString().c_str(), true);

    memcpy(keyIv, keygen.getIv().BytePtr(), ivSize);
    memcpy(keyIv + ivSize, keygen.getKey().BytePtr(), keySize);

    switch(encoding) {
    case Encoding::BASE64 :
        keyIvSource.Attach(new Base64Encoder);
        break;
    case Encoding::HEX :
        keyIvSource.Attach(new HexEncoder);
    case Encoding::NONE :
        break;
    default :
        keyIvSource.Attach(new Base64Encoder);
        break;
    }

    refsSource.Attach(new Redirector(fs));
    keyIvSource.Attach(new Redirector(fs));

    refsSource.PumpAll();
    keyIvSource.PumpAll();
}
bool KSerial::isFileExist(const string& filename) const
{
    return std::fstream(filename, ios::in | ios::binary).good();
}
QMessageBox::ButtonRole KSerial::dialogFileExists(const string& message)
{
    string text = MESSAGE_FILE_EXISTS_START + message + MESSAGE_FILE_EXISTS_END;
    QMessageBox msg(m_parent);
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
bool KSerial::dialogInsertFilename(const string& message) {
    string text = MESSAGE_INSERT_FNAME_START + message + MESSAGE_INSERT_FNAME_END;
    QInputDialog input(m_parent);
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
bool KSerial::dialogConfirm(const string& message)
{
    string text = MESSAGE_CONFIRM_START + message + MESSAGE_CONFIRM_END;
    QMessageBox msg(m_parent);
    QPushButton* ok =  msg.addButton("Ok", QMessageBox::AcceptRole);
    QPushButton* cancel =  msg.addButton("Cancel", QMessageBox::RejectRole);
    bool isConfirmed = false;

    msg.setWindowTitle("xKrypt - Warning");
    msg.setWindowIcon(QIcon(QPixmap(ICON_WARNING)));
    msg.setText(QString::fromStdString(text));
    msg.setDefaultButton(cancel);
    msg.setEscapeButton(cancel);
    msg.setModal(true);
    msg.exec();

    if(msg.clickedButton() == ok) isConfirmed = true;

    return isConfirmed;
}




