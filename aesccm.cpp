#include "aesccm.h"
#include "base64.h"
#include "defines.h"
#include "files.h"
#include "hex.h"
#include "ccm.h"
#include "except.h"
#include "keygenaes.h"
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
string AesCCM::encryptText(const string& plain, AbstractKeygen* keygen, const Encoding encoding) noexcept(false)
{
    KeygenAes* kg_aes = (KeygenAes*)keygen;
    std::string cipher = "";
    const SecByteBlock& key = kg_aes->key();
    const SecByteBlock& iv = kg_aes->Iv();
    StringSink* ssink = new StringSink(cipher);
    CryptoPP::CCM<CryptoPP::AES, TAG_SIZE>::Encryption encryptor;
    encryptor.SetKeyWithIV(key, key.size(), iv);
    encryptor.SpecifyDataLengths(0, plain.size(), 0);
    AuthenticatedEncryptionFilter* textFilter = new AuthenticatedEncryptionFilter(encryptor);
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
string AesCCM::decryptText(const string& cipher, AbstractKeygen* keygen, const Encoding encoding) noexcept(false)
{
    KeygenAes* kg_aes = (KeygenAes*)keygen;
    std::string recover;
    const SecByteBlock& key = kg_aes->key();
    const SecByteBlock& iv = kg_aes->Iv();
    StringSink* ssink = new StringSink(recover);
    CryptoPP::CCM<CryptoPP::AES, TAG_SIZE>::Decryption decryptor;
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

    int count = afterRefs(new StringSource(cipher, false));
    string bruteCipher = cipher.substr(count);

    if(decoder) {
        decoder->PutMessageEnd((CryptoPP::byte*)bruteCipher.c_str(), bruteCipher.size());
        decryptor.SetKeyWithIV(key, key.size(), iv);
        decryptor.SpecifyDataLengths(0, decoder->MaxRetrievable() - TAG_SIZE, 0);
        AuthenticatedDecryptionFilter* textFilter = new AuthenticatedDecryptionFilter(decryptor, ssink);
        decoder->Attach(textFilter);
        StringSource(bruteCipher, true, decoder);
    }
    else {
        decryptor.SetKeyWithIV(key, key.size(), iv);
        decryptor.SpecifyDataLengths(0, bruteCipher.size() - TAG_SIZE, 0);
        AuthenticatedDecryptionFilter* textFilter = new AuthenticatedDecryptionFilter(decryptor, ssink);
        StringSource(bruteCipher, true, textFilter);
    }

    return recover;
}
void AesCCM::encryptFile(const string& path, AbstractKeygen* keygen, const Encoding encoding, const string& newDir)
{
    KeygenAes* kg_aes = (KeygenAes*)keygen;
    string filename, output;
    const SecByteBlock& key = kg_aes->key();
    const SecByteBlock& iv = kg_aes->Iv();
    CryptoPP::CCM<CryptoPP::AES, TAG_SIZE>::Encryption encryptor;
    DirFname dirfname = extractFname(path);

    if(m_encfname) {
        encryptor.SetKeyWithIV(key, key.size(), iv);
        encryptor.SpecifyDataLengths(0, dirfname.m_fname.size(), 0 );
        AuthenticatedEncryptionFilter* filenameFilter = new AuthenticatedEncryptionFilter(encryptor, new HexEncoder(new StringSink(filename)));
        StringSource(dirfname.m_fname, true, filenameFilter);
    }
    else filename += dirfname.m_fname + FILE_TEMP_SUFFIX;

    std::ifstream f(path, std::ios::in | std::ios::binary | std::ios::ate);
    size_t fsize = f.tellg();
    f.close();

    encryptor.SetKeyWithIV(key, key.size(), iv);
    encryptor.SpecifyDataLengths(0, fsize, 0);
    AuthenticatedEncryptionFilter* fileFilter = new AuthenticatedEncryptionFilter(encryptor);
    if(!newDir.empty()) dirfname.m_dir = newDir;
    FileSink* fs = new FileSink((output = dirfname.m_dir + DELIMITOR + filename).c_str());

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
void AesCCM::decryptFile(const string& path, AbstractKeygen* keygen, const Encoding encoding, const string& newDir)
{   
    KeygenAes* kg_aes = (KeygenAes*)keygen;
    string filename, output;
    const SecByteBlock& key = kg_aes->key();
    const SecByteBlock& iv = kg_aes->Iv();
    CryptoPP::CCM<CryptoPP::AES, TAG_SIZE>::Decryption decryptor;
    DirFname dirfname = extractFname(path);

    if(m_decfname) {
        HexDecoder* decoder = new HexDecoder;
        decoder->PutMessageEnd((CryptoPP::byte*)dirfname.m_fname.c_str(), dirfname.m_fname.size());
        decryptor.SetKeyWithIV(key, key.size(), iv);
        decryptor.SpecifyDataLengths(0, decoder->MaxRetrievable() - TAG_SIZE, 0 );
        AuthenticatedDecryptionFilter* filenameFilter  = new AuthenticatedDecryptionFilter(decryptor, new StringSink(filename));
        decoder->Attach(filenameFilter);
        StringSource(dirfname.m_fname, true, decoder);
    }
    else filename += dirfname.m_fname + FILE_TEMP_SUFFIX;

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

    std::ifstream f(path.c_str(), std::ios::in | std::ios::binary);
    std::vector<char> bytes((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    FileSource source(path.c_str(), false);
    int refsCount = afterRefs(&source);

    if(!newDir.empty()) dirfname.m_dir = newDir;
    FileSink* fs = new FileSink((output = dirfname.m_dir + DELIMITOR + filename).c_str());
    if(decoder) {
        decoder->PutMessageEnd((CryptoPP::byte*)&bytes[refsCount], bytes.size()-refsCount);
        decryptor.SetKeyWithIV(key, key.size(), iv);
        decryptor.SpecifyDataLengths(0, decoder->MaxRetrievable() - TAG_SIZE, 0 );
        AuthenticatedDecryptionFilter* fileFilter = new AuthenticatedDecryptionFilter(decryptor, fs);
        decoder->Attach(fileFilter);
        source.Attach(decoder);
    }
    else {
        decryptor.SetKeyWithIV(key, key.size(), iv);
        decryptor.SpecifyDataLengths(0, bytes.size() - TAG_SIZE - refsCount, 0 );
        AuthenticatedDecryptionFilter* fileFilter = new AuthenticatedDecryptionFilter(decryptor, fs);
        source.Attach(fileFilter);
    }

    source.PumpAll();

    remove(path.c_str());
    if(!m_decfname) {
        QString out = QString::fromStdString(output);
        QFile(out).rename(QString::fromStdString(output.substr(0, output.size()-strlen(FILE_TEMP_SUFFIX))));
    }
}
