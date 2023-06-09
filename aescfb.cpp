#include "aescfb.h"
#include "aes.h"
#include "defines.h"
#include "files.h"
#include "filters.h"
#include "hex.h"
#include "base64.h"
#include "keygenaes.h"
#include "modes.h"
#include "except.h"
#include <QFile>

using namespace CryptoPP;
using namespace std;

const std::string AesCFB::ModeName = "CFB";

// constructors
AesCFB::AesCFB() {}

// destructor
AesCFB::~AesCFB() {}

// virtual methods
std::string AesCFB::modeName() const
{
    return AesCFB::ModeName;
}
Mode AesCFB::modeId() const
{
    return Mode::CFB;
}
string AesCFB::encryptText(const string& plain, AbstractKeygen* keygen, const Encoding encoding) noexcept(false)
{
    KeygenAes* kg_aes = (KeygenAes*)keygen;
    std::string cipher = "";
    const SecByteBlock& key = kg_aes->key();
    const SecByteBlock& iv = kg_aes->Iv();
    StringSink* ssink = new StringSink(cipher);
    CFB_Mode<CryptoPP::AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(key, key.size(), iv);
    StreamTransformationFilter* textFilter = new StreamTransformationFilter(encryptor);

    string refsCipher;
    injectRefs(refsCipher, keygen);

    switch(encoding) {
    case Encoding::BASE64 : textFilter->Attach(new Base64Encoder); break;
    case Encoding::HEX : textFilter->Attach(new HexEncoder); break;
    case Encoding::NONE : break;
    default : throw EncodingException();
    }

    textFilter->Attach(ssink);
    StringSource(plain, true, textFilter);
    refsCipher += cipher;

    if(m_isContentEnc) return refsCipher;
    return cipher;
}
string AesCFB::decryptText(const string& cipher, AbstractKeygen* keygen, const Encoding encoding) noexcept(false)
{
    KeygenAes* kg_aes = (KeygenAes*)keygen;
    std::string recover;
    const SecByteBlock& key = kg_aes->key();
    const SecByteBlock& iv = kg_aes->Iv();
    StringSink* ssink = new StringSink(recover);
    CFB_Mode<CryptoPP::AES>::Decryption decryptor;
    decryptor.SetKeyWithIV(key, key.size(), iv);
    StreamTransformationFilter* textFilter = new StreamTransformationFilter(decryptor, ssink);
    StringSource source(cipher, false);

    afterRefs(&source);

    switch(encoding) {
    case Encoding::BASE64 : source.Attach(new Base64Decoder); break;
    case Encoding::HEX : source.Attach(new HexDecoder); break;
    case Encoding::NONE : break;
    default : throw EncodingException();
    }

    source.Attach(textFilter);
    source.PumpAll();

    return recover;
}
void AesCFB::encryptFile(const string& path, AbstractKeygen* keygen, const Encoding encoding, const string& newDir)
{
    KeygenAes* kg_aes = (KeygenAes*)keygen;
    string filename, output;
    const SecByteBlock& key = kg_aes->key();
    const SecByteBlock& iv = kg_aes->Iv();
    CFB_Mode<CryptoPP::AES>::Encryption encryptor;
    DirFname dirfname = extractFname(path);

    if(m_encfname) {
        encryptor.SetKeyWithIV(key, key.size(), iv);
        StreamTransformationFilter* filenameFilter = new StreamTransformationFilter(encryptor, new HexEncoder(new StringSink(filename)));
        StringSource(dirfname.m_fname, true, filenameFilter);
    }
    else filename += dirfname.m_fname + FILE_TEMP_SUFFIX;

    if(!newDir.empty()) dirfname.m_dir = newDir;
    FileSink* fs = new FileSink((output = dirfname.m_dir + DELIMITOR + filename).c_str());
    encryptor.SetKeyWithIV(key, key.size(), iv);
    StreamTransformationFilter* fileFilter = new StreamTransformationFilter(encryptor);

    injectRefs(fs, keygen);
    switch(encoding) {
    case Encoding::BASE64 : fileFilter->Attach(new Base64Encoder); break;
    case Encoding::HEX : fileFilter->Attach(new HexEncoder); break;
    case Encoding::NONE :  break;
    default : throw EncodingException();
    }

    fileFilter->Attach(new Redirector(*fs));
    FileSource source(path.c_str(), true, fileFilter);

    remove(path.c_str());
    if(!m_encfname) {
        QString out = QString::fromStdString(output);
        QFile(out).rename(QString::fromStdString(output.substr(0, output.size()-strlen(FILE_TEMP_SUFFIX))));
    }
}
void AesCFB::decryptFile(const string& path, AbstractKeygen* keygen, const Encoding encoding, const string& newDir)
{
    KeygenAes* keygen_aes = (KeygenAes*)keygen;
    string filename, output;
    const SecByteBlock& key = keygen_aes->key();
    const SecByteBlock& iv = keygen_aes->Iv();
    CFB_Mode<CryptoPP::AES>::Decryption decryptor;
    DirFname dirfname = extractFname(path);

    if(m_decfname) {
        decryptor.SetKeyWithIV(key, key.size(), iv);
        StreamTransformationFilter* filenameFilter  = new StreamTransformationFilter(decryptor, new StringSink(filename));
        StringSource(dirfname.m_fname, true, new HexDecoder(filenameFilter));
    }
    else filename += dirfname.m_fname + FILE_TEMP_SUFFIX;

    if(!newDir.empty()) dirfname.m_dir = newDir;
    FileSink* fs = new FileSink((output = dirfname.m_dir + DELIMITOR + filename).c_str());
    decryptor.SetKeyWithIV(key, key.size(), iv);
    StreamTransformationFilter* fileFilter  = new StreamTransformationFilter(decryptor, fs);
    FileSource source(path.c_str(), false);

    afterRefs(&source);
    switch(encoding) {
    case Encoding::BASE64 : source.Attach(new Base64Decoder); break;
    case Encoding::HEX : source.Attach(new HexDecoder); break;
    case Encoding::NONE : break;
    default : throw EncodingException();
    }

    source.Attach(fileFilter);
    source.PumpAll();

    remove(path.c_str());
    if(!m_decfname) {
        QString out = QString::fromStdString(output);
        QFile(out).rename(QString::fromStdString(output.substr(0, output.size()-strlen(FILE_TEMP_SUFFIX))));
    }
}

