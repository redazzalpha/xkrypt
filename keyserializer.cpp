#include "keyserializer.h"
#include "base64.h"
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
KeySerializer::KeySerializer(QMainWindow* parent): m_parent(parent){};

// methods
void KeySerializer::saveOnFile(SecByteBlock key, Encoding encoding) {
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
                    keyToFile(key, encoding);
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
bool KeySerializer::isFileExist(const string& filename) {
    return std::fstream(filename).good();
}
void KeySerializer::keyToFile(SecByteBlock key, Encoding encoding) {
    FileSink* fs = new FileSink(m_dir.toStdString().c_str());
    BufferedTransformation* encoder = nullptr;;

    switch(encoding) {
    case Encoding::BASE64 : encoder = new Base64Encoder(fs); break;
    case Encoding::HEX : encoder = new HexEncoder(fs); break;
    case Encoding::BINARY : StringSource(key.BytePtr(), key.size(), true, fs); break;
    default : encoder = new HexEncoder(fs);
    }

    if(encoding != Encoding::BINARY) {
        encoder->Put(key, key.size());
        encoder->MessageEnd();
        delete encoder;
        encoder = nullptr;
    }
}
string KeySerializer::keyToString(SecByteBlock key, Encoding encoding) {
    stringstream ss;
    FileSink* fs = new FileSink(ss);
    BufferedTransformation* encoder;

    switch(encoding) {
    case Encoding::BASE64 : encoder = new Base64Encoder(fs); break;
    case Encoding::HEX : encoder = new HexEncoder(fs); break;
    case Encoding::BINARY : StringSource(key.BytePtr(), key.size(), true, fs); break;
    default : encoder = new HexEncoder(fs);
    }

    if(encoding != Encoding::BINARY) {
        encoder->Put(key, key.size());
        encoder->MessageEnd();

        delete encoder;
        encoder = nullptr;
    }

    return ss.str();
}
SecByteBlock KeySerializer::importKey(Encoding encoding) noexcept(false)  {
    m_dir = QFileDialog::getOpenFileName(m_parent,"Import key", "", "All Files (*)");
    SecByteBlock key;

    if(!m_dir.isEmpty()) {
        ifstream f(m_dir.toStdString(), std::ios::binary | std::ios::in);
        if(f.good()) {
            BufferedTransformation* decoder = new Base64Decoder;
            string decoded, line;
            ostringstream os;
            std::vector<char> bytes((std::istreambuf_iterator<char>(f)), (std::istreambuf_iterator<char>()));

            switch(encoding) {
            case Encoding::BASE64 : decoder = new Base64Decoder; break;
            case Encoding::HEX : decoder = new HexDecoder; break;
            case Encoding::BINARY : key = SecByteBlock((CryptoPP::byte*)&bytes[0], bytes.size()); break;
            default : decoder = new HexDecoder;
            }

            if(encoding != Encoding::BINARY) {
                bool hex = isHex(bytes), base64 = isBase64(bytes);

                if(encoding == Encoding::BASE64 && !(base64 || hex)) throw UnsupportedEncoding("-- error: Unsupported encoding! Try Binary encoding.");
                if(encoding == Encoding::HEX && !hex) throw UnsupportedEncoding("-- error: Unsupported encoding! Try Binary or Base64 encoding.");

                decoder->Put((CryptoPP::byte*)&bytes[0], bytes.size());
                decoder->MessageEnd();
                word64 size = decoder->MaxRetrievable();
                if(size && size <= SIZE_MAX) {
                    decoded.resize(size);
                    decoder->Get((CryptoPP::byte*)&decoded[0], decoded.size());
                }
                key = SecByteBlock((CryptoPP::byte*)&decoded[0], decoded.size());
            }
            f.close();
        }
    }
    return key;
}

// private methods
QMessageBox::ButtonRole KeySerializer::dialogFileExists(const string& message) {
    string text =
        "<td><img src=:/assets/warning.png width=50 height=50/></td><td valign=middle>" +
        message +
        "</td>";
    QMessageBox msg(m_parent);
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
bool KeySerializer::dialogInsertFilename(const string& message) {
    string text =
        "<td><img src=:/assets/file.png width=50 height=50/></td><td valign=middle>" +
        message +
        "</td>";
    QInputDialog input(m_parent);
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
bool KeySerializer::dialogConfirm(const string& message) {
    string text =
        "<td><img src=:/assets/warning.png width=50 height=50/></td><td valign=middle>" +
        message +
        "</td>";
    QMessageBox msg(m_parent);
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
bool KeySerializer::isBase64(const vector<char> bytes) {
    int fsize = bytes.size();
    stringstream ss;
    ss << bytes[fsize-2];
    return ss.str() == "=";
}
bool KeySerializer::isHex(const vector<char> bytes) {
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
