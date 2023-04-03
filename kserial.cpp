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
#include <bits/streambuf_iterator.h>

using namespace CryptoPP;
using namespace std;

// constructors
KSerial::KSerial(QMainWindow* parent): m_parent(parent){};

// methods
string KSerial::encodingToString(const Encoding encoding)
{
    string encodingStr;
    switch(static_cast<int>(encoding))  {
    case Encoding::BASE64: return "Base64";
    case Encoding::HEX: return "Hex";
    case Encoding::BINARY: return "Binary";
    default: return "Base64";
    }
}
void KSerial::saveOnFile(KeyGen& keygen, const Encoding encoding)
{
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
bool KSerial::importKeygen(KeyGen* keygen, const Encoding encoding) noexcept(false)
{
    bool imported = false;
    m_dir = QFileDialog::getOpenFileName(m_parent,"Import key", "", "All Files (*)");

    if(!m_dir.isEmpty()) {
        ifstream f(m_dir.toStdString(), std::ios::binary | std::ios::in);
        if(f.good()) {
            string decoded;
            int blocksize = AES::BLOCKSIZE;
            std::vector<char> bytes( (istreambuf_iterator<char>(f)), (istreambuf_iterator<char>()));
            bool hex = isHex(bytes), base64 = isBase64(bytes);

            if(encoding == Encoding::BASE64 && !base64) throw UnsupportedEncoding();
            if(encoding == Encoding::HEX && !hex) throw UnsupportedEncoding();
            if(encoding == Encoding::BINARY && (base64 || hex)) throw UnsupportedEncoding();

            switch(encoding) {
            case Encoding::BASE64 :
                StringSource(bytes.data(), true, new Base64Decoder(new StringSink(decoded)));
                break;
            case Encoding::HEX :
                StringSource(bytes.data(), true, new HexDecoder(new StringSink(decoded)));
                break;
            case Encoding::BINARY :
                StringSource(bytes.data(), true, new StringSink(decoded));
                break;
            default :
                StringSource(bytes.data(), true, new Base64Decoder(new StringSink(decoded)));
            }

            keygen->flush();
            keygen->setIv(SecByteBlock((CryptoPP::byte*)&decoded[0], blocksize));
            keygen->setKey(SecByteBlock((CryptoPP::byte*)&decoded[blocksize], decoded.size() - blocksize));
            f.close();
            imported = true;
        }
    }

    return imported;
}
string KSerial::keyToString(KeyGen& keygen, const Encoding encoding)
{
    string keyIv;
    size_t size = keygen.getIv().size() + keygen.getKey().size();
    CryptoPP::byte* destPtr = new CryptoPP::byte[size];
    memcpy(destPtr, keygen.getIv().BytePtr(), keygen.getIv().size());
    memcpy(destPtr + keygen.getIv().size(), keygen.getKey().BytePtr(), keygen.getKey().size());

    switch(encoding) {
    case Encoding::BASE64 :
        StringSource(destPtr, size, true, new Base64Encoder(new StringSink(keyIv)));
        break;
    case Encoding::HEX :
        StringSource(destPtr, size, true, new HexEncoder(new StringSink(keyIv)));
        break;
    case Encoding::BINARY :
        StringSource(destPtr, size, true, new StringSink(keyIv));
        break;
    default :
        StringSource(destPtr, size, true, new Base64Encoder(new StringSink(keyIv)));
    }
    delete[] destPtr;
    destPtr = nullptr;

    return keyIv;
}

// private methods
void KSerial::keyToFile(KeyGen& keygen, const Encoding encoding)
{
    size_t size = keygen.getIv().size() + keygen.getKey().size();
    CryptoPP::byte* destPtr = new CryptoPP::byte[size];
    memcpy(destPtr, keygen.getIv().BytePtr(), keygen.getIv().size());
    memcpy(destPtr + keygen.getIv().size(), keygen.getKey().BytePtr(), keygen.getKey().size());

    switch(encoding) {
    case Encoding::BASE64 :
        StringSource(destPtr, size, true, new Base64Encoder(new FileSink(m_dir.toStdString().c_str())));
        break;
    case Encoding::HEX :
        StringSource(destPtr, size, true, new HexEncoder(new FileSink(m_dir.toStdString().c_str())));
        break;
    case Encoding::BINARY :
        StringSource(destPtr, size, true, new FileSink(m_dir.toStdString().c_str()));
        break;
    default :
        StringSource(destPtr, size, true, new Base64Encoder(new FileSink(m_dir.toStdString().c_str())));
    }
    delete[] destPtr;
}
bool KSerial::isFileExist(const string& filename)
{
    return std::fstream(filename).good();
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
bool KSerial::isBase64(vector<char>& bytes)
{
    int fsize = bytes.size();
    stringstream ss;
    ss << bytes[fsize-2];
    return ss.str() == "=";
}
bool KSerial::isHex(vector<char>& bytes)
{
    bool hex = true;

    for(char c : bytes) {
        c = std::toupper(c);
        if(!(c >= 48 && c <= 57) && !(c >= 65 && c <= 70)) {
            hex = false;
            break;
        }
    }
    return hex;
}
