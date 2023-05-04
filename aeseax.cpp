#include "aeseax.h"
#include "defines.h"
#include "eax.h"
#include "files.h"

#include <QFile>
#include <base64.h>
#include <hex.h>

using namespace CryptoPP;
using namespace std;

const std::string AesEAX::ModeName = "EAX";

// constructors
AesEAX::AesEAX() {}

// destructor
AesEAX::~AesEAX() {};

// virtual methods
std::string AesEAX::getModeName() const {
    return AesEAX::ModeName;
}


// slots
string AesEAX::encryptText(const string& plain, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::string cipher = "";
    try {
        const SecByteBlock& key = keygen->getKey();
        const SecByteBlock& iv = keygen->getIv();
        StringSink* ss = new StringSink(cipher);
        EAX<AES>::Encryption encryptor;
        AuthenticatedEncryptionFilter* aef = new AuthenticatedEncryptionFilter(encryptor);
        encryptor.SetKeyWithIV(key, key.size(), iv);

        switch(encoding) {
        case Encoding::BASE64 : aef->Attach(new Base64Encoder(ss)); break;
        case Encoding::HEX : aef->Attach(new HexEncoder(ss)); break;
        case Encoding::NONE : aef->Attach(ss); break;
        default: aef->Attach(new Base64Encoder(ss));;
        }

        StringSource(plain, true, aef);
        emit proceed();
        if(!m_encFname) emit cipherText(cipher);
        return cipher;
    }
    catch(exception& e) {
        emit error(e.what());
    }
    return cipher;
}
string AesEAX::decryptText(const string& cipher, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::string recover;
    try {
        const SecByteBlock& key = keygen->getKey();
        const SecByteBlock& iv = keygen->getIv();
        StringSink* ss = new StringSink(recover);
        EAX<AES>::Decryption decryptor;
        AuthenticatedDecryptionFilter* aef = new AuthenticatedDecryptionFilter(decryptor, ss);
        decryptor.SetKeyWithIV(key, key.size(), iv);

        switch(encoding) {
        case Encoding::BASE64 : StringSource(cipher, true, new Base64Decoder(aef)); break;
        case Encoding::HEX : StringSource(cipher, true, new HexDecoder(aef)); break;
        case Encoding::NONE : StringSource(cipher, true, aef); break;
        default: StringSource(cipher, true, new Base64Decoder(aef));
        }

        emit proceed();
        emit recoverText(recover);
        return recover;
    }
    catch(exception& e) {
        emit error(e.what());
    }
    return recover;
}
void AesEAX::encryptFile(vector<string> paths, Keygen* keygen, const Encoding encoding)
{
    string output;
    string filenameEnc;
    try {
        const SecByteBlock& key = keygen->getKey();
        const SecByteBlock& iv = keygen->getIv();

        size_t progress;
        for(progress = 0; progress < paths.size() && m_run; progress++) {
            const string& path = paths[progress];
            DirFname dirfname = extractFname(path);

            EAX<AES>::Encryption encryptor;

            if(m_encFname) {
                encryptor.SetKeyWithIV(key, key.size(), iv);
                AuthenticatedEncryptionFilter* filenameFilter = new AuthenticatedEncryptionFilter(encryptor, new HexEncoder(new StringSink(filenameEnc)));
                StringSource(dirfname.m_fname, true, filenameFilter);
            }
            else  filenameEnc = dirfname.m_fname;

            encryptor.SetKeyWithIV(key, key.size(), iv);

            filenameEnc = filenameEnc == dirfname.m_fname? filenameEnc + FILE_TEMP_SUFFIX:filenameEnc;
            FileSink* fs = new FileSink((output = (dirfname.m_dir + DELIMITOR + filenameEnc)).c_str());
            AuthenticatedEncryptionFilter* fileFilter = new AuthenticatedEncryptionFilter(encryptor);

            switch(encoding) {
            case Encoding::BASE64 : fileFilter->Attach(new Base64Encoder(fs)); break;
            case Encoding::HEX : fileFilter->Attach(new HexEncoder(fs)); break;
            case Encoding::NONE : fileFilter->Attach(fs); break;
            default: fileFilter->Attach(new Base64Encoder(fs));;
            }

            FileSource(path.c_str(), true, fileFilter);
            removeFile(path);
            if(!m_encFname)
            QFile(QString::fromStdString(output)).rename(
                QString::fromStdString(
                    output.substr(0, output.size()-strlen(FILE_TEMP_SUFFIX))
                )
            );
            filenameEnc.clear();
            output.clear();
            emit proceed(progress+1);
        }
        emit cipherFile(successEncMsg(progress));
    }
    catch(exception& e) {
        emit error(e.what());
    }
}
void AesEAX::decryptFile(vector<string> paths, Keygen* keygen, const Encoding encoding)
{
    string output;
    string filenameDec;
    try {
        const SecByteBlock& key = keygen->getKey();
        const SecByteBlock& iv = keygen->getIv();

        size_t progress;
        for(progress = 0; progress < paths.size() && m_run; progress++) {
            const string& path = paths[progress];
            DirFname dirfname = extractFname(path);

            EAX<AES>::Decryption decryptor;

            if(m_decFname) {
                decryptor.SetKeyWithIV(key, key.size(), iv);
                AuthenticatedDecryptionFilter* filenameFilter = new AuthenticatedDecryptionFilter(decryptor, new StringSink(filenameDec));
                StringSource(dirfname.m_fname, true, new HexDecoder(filenameFilter));
            }
            else filenameDec = dirfname.m_fname;

            decryptor.SetKeyWithIV(key, key.size(), iv);

            filenameDec = filenameDec == dirfname.m_fname? filenameDec + FILE_TEMP_SUFFIX:filenameDec;
            FileSink* fs = new FileSink((output = (dirfname.m_dir + DELIMITOR + filenameDec)).c_str());
            AuthenticatedDecryptionFilter* fileFilter = new AuthenticatedDecryptionFilter(decryptor, fs);

            switch(encoding) {
            case Encoding::BASE64 : FileSource(path.c_str(), true, new Base64Decoder(fileFilter)); break;
            case Encoding::HEX : FileSource(path.c_str(), true, new HexDecoder(fileFilter)); break;
            case Encoding::NONE : FileSource(path.c_str(), true, fileFilter); break;
            default: FileSource(path.c_str(), true, new Base64Decoder(fileFilter));
            }

            removeFile(path);
            if(!m_decFname)
            QFile(QString::fromStdString(output)).rename(
                QString::fromStdString(
                    output.substr(0, output.size()-strlen(FILE_TEMP_SUFFIX))
                )
            );
            filenameDec.clear();
            output.clear();
            emit proceed(progress+1);
        }
        emit recoverFile(successDecMsg(progress));
    }
    catch(exception& e) {
        removeFile(output);
        emit error(e.what());
    }
}

