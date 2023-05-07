#include "aesccm.h"
#include "base64.h"
#include "defines.h"
#include "files.h"
#include "hex.h"
#include "ccm.h"
#include "except.h"
#include <iterator>

#include <QFile>

using namespace CryptoPP;
using namespace std;

const std::string AesCCM::ModeName = "CCM";

// constructors
AesCCM::AesCCM(){}

// destructor
AesCCM::~AesCCM(){};

// virtual methods
std::string AesCCM::modeName() const
{
    return AesCCM::ModeName;
}
Mode AesCCM::modeId() const
{
    return Mode::CCM;
}
string AesCCM::encryptText(const string& plain, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::string cipher = "";
    const SecByteBlock& key = keygen->getKey();
    const SecByteBlock& iv = keygen->getIv();
    StringSink* ss = new StringSink(cipher);
    CryptoPP::CCM<CryptoPP::AES, XKRYPT_TAG_SIZE>::Encryption encryptor;
    AuthenticatedEncryptionFilter* textFilter = new AuthenticatedEncryptionFilter(encryptor);
    encryptor.SetKeyWithIV(key, key.size(), iv);
    encryptor.SpecifyDataLengths(0, plain.size(), 0);
    BufferedTransformation* encoder;

    switch(encoding) {
    case Encoding::BASE64 :
        encoder = new Base64Encoder;
        encoder->Attach(ss);
        textFilter->Attach(encoder);
        break;
    case Encoding::HEX :
        encoder = new HexEncoder;
        encoder->Attach(ss);
        textFilter->Attach(encoder);
        break;
    case Encoding::NONE :
        encoder = nullptr;
        textFilter->Attach(ss);
        break;
    default : throw EncodingException();
    }

    StringSource(plain, true, textFilter);
    return cipher;
}
string AesCCM::decryptText(const string& cipher, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::string recover;
    const SecByteBlock& key = keygen->getKey();
    const SecByteBlock& iv = keygen->getIv();
    StringSink* ss = new StringSink(recover);
    CryptoPP::CCM<CryptoPP::AES, XKRYPT_TAG_SIZE>::Decryption decryptor;
    AuthenticatedDecryptionFilter* textFilter = new AuthenticatedDecryptionFilter(decryptor, ss);
    BufferedTransformation* decoder;

    switch(encoding) {
    case Encoding::BASE64 :
        decoder = new Base64Decoder;
        break;
    case Encoding::HEX :
        decoder = new HexDecoder;
        break;
    case Encoding::NONE :
        decoder = nullptr;
        break;
    default : throw EncodingException();
    }

    if(decoder) {
        decoder->PutMessageEnd((CryptoPP::byte*)cipher.c_str(), cipher.size());
        decryptor.SetKeyWithIV(key, key.size(), iv);

        decryptor.SpecifyDataLengths(0, decoder->MaxRetrievable(), 0);
        decoder->Attach(textFilter);
        StringSource(cipher, true, decoder);
    }
    else {
        decryptor.SetKeyWithIV(key, key.size(), iv);
        decryptor.SpecifyDataLengths(0, cipher.size()-XKRYPT_TAG_SIZE, 0);
        StringSource(cipher, true, textFilter);

    }

    return recover;
}
void AesCCM::encryptFile(const string& path, Keygen* keygen, const Encoding encoding)
{
    string filename, output;
    const SecByteBlock& key = keygen->getKey();
    const SecByteBlock& iv = keygen->getIv();
    CryptoPP::CCM<CryptoPP::AES, XKRYPT_TAG_SIZE>::Encryption encryptor;
    DirFname dirfname = extractFname(path);

    if(m_encfname) {
        encryptor.SetKeyWithIV(key, key.size(), iv);
        encryptor.SpecifyDataLengths(0, dirfname.m_fname.size(), 0 );
        AuthenticatedEncryptionFilter* filenameFilter = new AuthenticatedEncryptionFilter(encryptor, new HexEncoder(new StringSink(filename)));
        StringSource(dirfname.m_fname, true, filenameFilter);
    }
    else filename += dirfname.m_fname + FILE_TEMP_SUFFIX;

    FileSink* fs = new FileSink((output = dirfname.m_dir + DELIMITOR + filename).c_str());
    AuthenticatedEncryptionFilter* fileFilter = new AuthenticatedEncryptionFilter(encryptor);
    encryptor.SetKeyWithIV(key, key.size(), iv);

    std::ifstream f(path, std::ios::in | std::ios::binary | std::ios::ate);
    size_t fsize = f.tellg();
    f.close();
    encryptor.SpecifyDataLengths(0, fsize, 0);

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
void AesCCM::decryptFile(const string& path, Keygen* keygen, const Encoding encoding)
{
    string filename, output;
    const SecByteBlock& key = keygen->getKey();
    const SecByteBlock& iv = keygen->getIv();
    CryptoPP::CCM<CryptoPP::AES, XKRYPT_TAG_SIZE>::Decryption decryptor;
    DirFname dirfname = extractFname(path);

    if(m_decfname) {
        HexDecoder* decoder = new HexDecoder;
        decoder->PutMessageEnd((CryptoPP::byte*)dirfname.m_fname.c_str(), dirfname.m_fname.size());
        decryptor.SetKeyWithIV(key, key.size(), iv);
        decryptor.SpecifyDataLengths(0, decoder->MaxRetrievable()-XKRYPT_TAG_SIZE, 0 );
        AuthenticatedDecryptionFilter* filenameFilter  = new AuthenticatedDecryptionFilter(decryptor, new StringSink(filename));
        decoder->Attach(filenameFilter);
        StringSource(dirfname.m_fname, true, decoder);
    }
    else filename += dirfname.m_fname + FILE_TEMP_SUFFIX;

    BufferedTransformation* decoder;
    switch(encoding) {
    case Encoding::BASE64 : decoder = new Base64Decoder; break;
    case Encoding::HEX : decoder = new HexDecoder; break;
    case Encoding::NONE : decoder = nullptr; break;
    default : throw EncodingException();
    }

    std::ifstream encodedFile(path.c_str(), std::ios::in | std::ios::binary);
    std::vector<char> encodedBytes((std::istreambuf_iterator<char>(encodedFile)), std::istreambuf_iterator<char>());
    FileSource source(path.c_str(), false);
    int refsCount = afterRefs(&source);

    decoder->PutMessageEnd((CryptoPP::byte*)&encodedBytes[refsCount], encodedBytes.size()-refsCount);

    FileSink* fs = new FileSink((output = dirfname.m_dir + DELIMITOR + filename).c_str());
    AuthenticatedDecryptionFilter* fileFilter = new AuthenticatedDecryptionFilter(decryptor, fs);
    decryptor.SetKeyWithIV(key, key.size(), iv);
    decryptor.SpecifyDataLengths(0, decoder->MaxRetrievable()-XKRYPT_TAG_SIZE, 0 );
    decoder->Attach(fileFilter);
    source.Attach(decoder);
    source.PumpAll();

    remove(path.c_str());
    if(!m_decfname) {
        QString out = QString::fromStdString(output);
        QFile(out).rename(QString::fromStdString(output.substr(0, output.size()-strlen(FILE_TEMP_SUFFIX))));
    }
}
