#include "aesofb.h"
#include "aes.h"
#include "defines.h"
#include "files.h"
#include "filters.h"
#include "hex.h"
#include "base64.h"
#include "modes.h"
#include "except.h"
#include <QFile>

using namespace CryptoPP;
using namespace std;

const std::string AesOFB::ModeName = "OFB";

// constructors
AesOFB::AesOFB() {}

// destructor
AesOFB::~AesOFB() {}

// virtual methods
std::string AesOFB::modeName() const
{
    return AesOFB::ModeName;
}
Mode AesOFB::modeId() const
{
    return Mode::OFB;
}
string AesOFB::encryptText(const string& plain, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::string cipher = "";
    const SecByteBlock& key = keygen->getKey();
    const SecByteBlock& iv = keygen->getIv();
    StringSink* ss = new StringSink(cipher);
    OFB_Mode<CryptoPP::AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(key, key.size(), iv);
    StreamTransformationFilter* textFilter = new StreamTransformationFilter(encryptor);

    switch(encoding) {
    case Encoding::BASE64 : textFilter->Attach(new Base64Encoder(ss)); break;
    case Encoding::HEX : textFilter->Attach(new HexEncoder(ss)); break;
    case Encoding::NONE : textFilter->Attach(ss); break;
    default : throw EncodingException();
    }

    StringSource(plain, true, textFilter);
    return cipher;
}
string AesOFB::decryptText(const string& cipher, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::string recover;
    const SecByteBlock& key = keygen->getKey();
    const SecByteBlock& iv = keygen->getIv();
    StringSink* ss = new StringSink(recover);
    OFB_Mode<CryptoPP::AES>::Decryption decryptor;
    decryptor.SetKeyWithIV(key, key.size(), iv);
    StreamTransformationFilter* textFilter = new StreamTransformationFilter(decryptor, ss);

    switch(encoding) {
    case Encoding::BASE64 : StringSource(cipher, true, new Base64Decoder(textFilter)); break;
    case Encoding::HEX : StringSource(cipher, true, new HexDecoder(textFilter)); break;
    case Encoding::NONE : StringSource(cipher, true, textFilter); break;
    default : throw EncodingException();
    }

    return recover;
}
void AesOFB::encryptFile(const string& path, Keygen* keygen, const Encoding encoding)
{
    string filename, output;
    const SecByteBlock& key = keygen->getKey();
    const SecByteBlock& iv = keygen->getIv();
    OFB_Mode<CryptoPP::AES>::Encryption encryptor;
    DirFname dirfname = extractFname(path);

    if(m_encfname) {
        encryptor.SetKeyWithIV(key, key.size(), iv);
        StreamTransformationFilter* filenameFilter = new StreamTransformationFilter(encryptor, new HexEncoder(new StringSink(filename)));
        StringSource(dirfname.m_fname, true, filenameFilter);
    }
    else filename += dirfname.m_fname + FILE_TEMP_SUFFIX;

    FileSink* fs = new FileSink((output = dirfname.m_dir + DELIMITOR + filename).c_str());
    encryptor.SetKeyWithIV(key, key.size(), iv);
    StreamTransformationFilter* fileFilter = new StreamTransformationFilter(encryptor);

    injectRefs(fs, encoding);
    switch(encoding) {
    case Encoding::BASE64 : fileFilter->Attach(new Base64Encoder(fs)); break;
    case Encoding::HEX : fileFilter->Attach(new HexEncoder(fs)); break;
    case Encoding::NONE : fileFilter->Attach(fs); break;
    default : throw EncodingException();
    }

    FileSource source(path.c_str(), true, new Redirector(*fileFilter));

    remove(path.c_str());
    if(!m_encfname) {
        QString out = QString::fromStdString(output);
        QFile(out).rename(QString::fromStdString(output.substr(0, output.size()-strlen(FILE_TEMP_SUFFIX))));
    }
}
void AesOFB::decryptFile(const string& path, Keygen* keygen, const Encoding encoding)
{
    string filename, output;
    const SecByteBlock& key = keygen->getKey();
    const SecByteBlock& iv = keygen->getIv();
    OFB_Mode<CryptoPP::AES>::Decryption decryptor;
    DirFname dirfname = extractFname(path);

    if(m_decfname) {
        decryptor.SetKeyWithIV(key, key.size(), iv);
        StreamTransformationFilter* filenameFilter  = new StreamTransformationFilter(decryptor, new StringSink(filename));
        StringSource(dirfname.m_fname, true, new HexDecoder(filenameFilter));
    }
    else filename += dirfname.m_fname + FILE_TEMP_SUFFIX;

    FileSink* fs = new FileSink((output = dirfname.m_dir + DELIMITOR + filename).c_str());
    decryptor.SetKeyWithIV(key, key.size(), iv);
    StreamTransformationFilter* fileFilter  = new StreamTransformationFilter(decryptor, fs);
    FileSource source(path.c_str(), false);

    afterRefs(&source);
    switch(encoding) {
    case Encoding::BASE64 : source.Attach(new Base64Decoder(fileFilter)); break;
    case Encoding::HEX : source.Attach(new HexDecoder(fileFilter)); break;
    case Encoding::NONE : source.Attach(fileFilter); break;
    default : throw EncodingException();
    }

    source.PumpAll();

    remove(path.c_str());
    if(!m_decfname) {
        QString out = QString::fromStdString(output);
        QFile(out).rename(QString::fromStdString(output.substr(0, output.size()-strlen(FILE_TEMP_SUFFIX))));
    }
}
