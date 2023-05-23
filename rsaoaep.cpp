#include "rsaoaep.h"
#include "defines.h"
#include "hex.h"
#include "rsa.h"
#include "keygenrsa.h"
#include "except.h"

#include <QFile>
#include <base64.h>

using namespace CryptoPP;
using namespace std;

const std::string RsaOAEP::ModeName = "ES-OAEP-SHA";

// constructors
RsaOAEP::RsaOAEP() {}

// destructor
RsaOAEP::~RsaOAEP() {};

// virtual methods
std::string RsaOAEP::modeName() const
{
    return RsaOAEP::ModeName;
}
Mode RsaOAEP::modeId() const
{
    return Mode::OEAP;
}
string RsaOAEP::encryptText(const string& plain, AbstractKeygen* keygen, const Encoding encoding) noexcept(false)
{
    KeygenRsa* keygen_rsa = (KeygenRsa*)keygen;
    CryptoPP::RSA::PrivateKey* pvk = keygen_rsa->getPrivate();
    AutoSeededX917RNG<CryptoPP::AES> prng;
    RSAES<OAEP<SHA512>>::Encryptor encryptor(*pvk);
    PK_EncryptorFilter* textFilter = new PK_EncryptorFilter(prng, encryptor);
    string cipher;

    switch(encoding) {
    case Encoding::BASE64 : textFilter->Attach(new Base64Encoder(new StringSink(cipher))); break;
    case Encoding::HEX : textFilter->Attach(new HexEncoder(new StringSink(cipher))); break;
    case Encoding::NONE : textFilter->Attach(new StringSink(cipher)); break;
    default : throw EncodingException();
    }

    StringSource source(plain, true, textFilter);
    return cipher;
}
string RsaOAEP::decryptText(const string& cipher, AbstractKeygen* keygen, const Encoding encoding) noexcept(false)
{
    KeygenRsa* keygen_rsa = (KeygenRsa*)keygen;
    CryptoPP::RSA::PrivateKey* pvk = keygen_rsa->getPrivate();
    string recover;
    AutoSeededX917RNG<CryptoPP::AES> prng;
    RSAES<OAEP<SHA512>>::Decryptor decryptor(*pvk);
    PK_DecryptorFilter* textFilter = new PK_DecryptorFilter(prng, decryptor, new StringSink(recover));

    switch(encoding) {
    case Encoding::BASE64 : StringSource(cipher, true, new Base64Decoder(textFilter)); break;
    case Encoding::HEX : StringSource(cipher, true, new HexDecoder(textFilter)); break;
    case Encoding::NONE : StringSource(cipher, true, textFilter); break;
    default : throw EncodingException();
    }

    return recover;
}
void RsaOAEP::encryptFile(const string& path, AbstractKeygen* keygen, const Encoding encoding)
{
    KeygenRsa* keygen_rsa = (KeygenRsa*)keygen;
    CryptoPP::RSA::PrivateKey* pvk = keygen_rsa->getPrivate();
    AutoSeededX917RNG<CryptoPP::AES> prng;
    RSAES<OAEP<SHA512>>::Encryptor encryptor(*pvk);

    string filename, output;
    DirFname dirfname = extractFname(path);

    if(m_encfname) {
        PK_EncryptorFilter* filenameFilter = new PK_EncryptorFilter(prng, encryptor, new HexEncoder(new StringSink(filename)));
        StringSource(dirfname.m_fname, true, filenameFilter);
    }
    else filename += dirfname.m_fname + FILE_TEMP_SUFFIX;

    FileSink* fs = new FileSink((output = dirfname.m_dir + DELIMITOR + filename).c_str());
    PK_EncryptorFilter* fileFilter = new PK_EncryptorFilter(prng, encryptor);

    injectRefs(fs, keygen);
    switch(encoding) {
    case Encoding::BASE64 : fileFilter->Attach(new Base64Encoder(new Redirector(*fs))); break;
    case Encoding::HEX : fileFilter->Attach(new HexEncoder(new Redirector(*fs))); break;
    case Encoding::NONE : fileFilter->Attach(new Redirector(*fs)); break;
    default : throw EncodingException();
    }

    FileSource source(path.c_str(), true, fileFilter);

    remove(path.c_str());
    if(!m_encfname) {
        QString out = QString::fromStdString(output);
        QFile(out).rename(QString::fromStdString(output.substr(0, output.size()-strlen(FILE_TEMP_SUFFIX))));
    }
}
void RsaOAEP::decryptFile(const string& path, AbstractKeygen* keygen, const Encoding encoding)
{
    KeygenRsa* keygen_rsa= (KeygenRsa*)keygen;
    CryptoPP::RSA::PrivateKey* pvk = keygen_rsa->getPrivate();
    AutoSeededX917RNG<CryptoPP::AES> prng;
    RSAES<OAEP<SHA512>>::Decryptor decryptor(*pvk);

    string filename, output;
    DirFname dirfname = extractFname(path);

    if(m_decfname) {
        PK_DecryptorFilter* filenameFilter = new PK_DecryptorFilter(prng, decryptor, new StringSink(filename));
        StringSource(dirfname.m_fname, true, new HexDecoder(filenameFilter));
    }
    else filename += dirfname.m_fname + FILE_TEMP_SUFFIX;

    FileSink* fs = new FileSink((output = dirfname.m_dir + DELIMITOR + filename).c_str());
    PK_DecryptorFilter* fileFilter = new PK_DecryptorFilter(prng, decryptor, fs);
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


