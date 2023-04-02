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

using namespace CryptoPP;
using namespace std;

// constructors
KSerial::KSerial(QMainWindow* parent): m_parent(parent){};

// methods
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
string KSerial::keyToString(KeyGen& keygen, const Encoding encoding)
{
    stringstream ss;
    FileSink* fs = new FileSink(ss);
    BufferedTransformation* encoder;
    size_t size;
    CryptoPP::byte* destPtr;

    switch(encoding) {
    case Encoding::BASE64 :
        encoder = new Base64Encoder(fs);
        break;
    case Encoding::HEX :
        encoder = new HexEncoder(fs);
        break;
    case Encoding::BINARY :
        size = keygen.getIv().size() + keygen.getKey().size();
        destPtr = new CryptoPP::byte[size];
        memcpy(destPtr, keygen.getIv().BytePtr(), keygen.getIv().size());
        memcpy(destPtr + keygen.getIv().size(), keygen.getKey().BytePtr(), keygen.getKey().size());
        StringSource(destPtr, size, true, fs);
        delete[] destPtr;
        break;
    default : encoder = new HexEncoder(fs);
    }

    if(encoding != Encoding::BINARY) {
        encoder->Put(keygen.getIv().BytePtr(), keygen.getIv().size());
        encoder->Put(keygen.getKey().BytePtr(), keygen.getKey().size());
        encoder->MessageEnd();

        delete encoder;
        encoder = nullptr;
    }

    return ss.str();
}
bool KSerial::importKeygen(KeyGen* keygen, const Encoding encoding) noexcept(false)
{
    bool imported = false;
    m_dir = QFileDialog::getOpenFileName(m_parent,"Import key", "", "All Files (*)");

    if(!m_dir.isEmpty()) {
        ifstream f(m_dir.toStdString(), std::ios::binary | std::ios::in);
        if(f.good()) {
            BufferedTransformation* decoder = new Base64Decoder;
            string data, line;
            ostringstream os;
            std::vector<char> bytes((std::istreambuf_iterator<char>(f)), (std::istreambuf_iterator<char>()));
            CryptoPP::byte* bytesPtr = (CryptoPP::byte*)&bytes[0];
            int blocksize = AES::BLOCKSIZE;

            switch(encoding) {
            case Encoding::BASE64 :
                decoder = new Base64Decoder;
                break;
            case Encoding::HEX :
                decoder = new HexDecoder;
                break;
            case Encoding::BINARY :
                keygen->flush();
                keygen->setIv(SecByteBlock(bytesPtr, blocksize));
                keygen->setKey(SecByteBlock((CryptoPP::byte*)&bytes[blocksize], bytes.size() - blocksize));
                imported = true;
                break;
            default : decoder = new HexDecoder;
            }

            if(encoding != Encoding::BINARY) {
                bool hex = isHex(bytes), base64 = isBase64(bytes);
                if(encoding == Encoding::BASE64 && !base64 && !hex) throw UnsupportedEncoding();
                if(encoding == Encoding::HEX && !hex) throw UnsupportedEncoding();

                decoder->Put(bytesPtr, bytes.size());
                decoder->MessageEnd();
                word64 size = decoder->MaxRetrievable();
                if(size && size <= SIZE_MAX) {
                    data.resize(size);
                    decoder->Get((CryptoPP::byte*)&data[0], data.size());
                }
                keygen->flush();
                keygen->setIv(SecByteBlock((CryptoPP::byte*)&data[0], blocksize));
                keygen->setKey(SecByteBlock((CryptoPP::byte*)&data[blocksize], data.size() - blocksize));
                imported = true;
            }

            f.close();
            delete decoder;
            decoder = nullptr;
        }
    }
    return imported;
}

// private methods
void KSerial::keyToFile(KeyGen& keygen, const Encoding encoding)
{
    FileSink* fs = new FileSink(m_dir.toStdString().c_str());
    BufferedTransformation* encoder = nullptr;
    size_t size;
    CryptoPP::byte* destPtr;

    switch(encoding) {
    case Encoding::BASE64 :
        encoder = new Base64Encoder(fs);
        break;
    case Encoding::HEX :
        encoder = new HexEncoder(fs);
        break;
    case Encoding::BINARY :
        size = keygen.getIv().size() + keygen.getKey().size();
        destPtr = new CryptoPP::byte[size];
        memcpy(destPtr, keygen.getIv().BytePtr(), keygen.getIv().size());
        memcpy(destPtr + keygen.getIv().size(), keygen.getKey().BytePtr(), keygen.getKey().size());
        StringSource(destPtr, size, true, fs);
        delete[] destPtr;
        break;
    default : encoder = new HexEncoder(fs);
    }

    if(encoding != Encoding::BINARY) {
        encoder->Put(keygen.getIv().BytePtr(), keygen.getIv().size());
        encoder->Put(keygen.getKey().BytePtr(), keygen.getKey().size());
        encoder->MessageEnd();
        delete encoder;
        encoder = nullptr;
    }
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
bool KSerial::isBase64(const vector<char> bytes)
{
    int fsize = bytes.size();
    stringstream ss;
    ss << bytes[fsize-2];
    return ss.str() == "=";
}
bool KSerial::isHex(const vector<char> bytes)
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
