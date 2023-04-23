#include "aescbc.h"
#include "aes.h"
#include "files.h"
#include "filters.h"
#include "hex.h"
#include "base64.h"
#include "modes.h"

#include <regex>
#include <thread>

using namespace CryptoPP;
using namespace std;

const std::string AesCBC::ModeName = "CBC";

// constructors
AesCBC::AesCBC() {}

// destructor
AesCBC::~AesCBC() {};

// virtual methods
std::string AesCBC::getModeName() const
{
    return AesCBC::ModeName;
}


// slots
string AesCBC::encryptText(const string& plain, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::string cipher = "";
    try {
        const SecByteBlock& key = keygen->getKey();
        const SecByteBlock& iv = keygen->getIv();
        StringSink* ss = new StringSink(cipher);
        CBC_Mode<AES>::Encryption encryptor;
        StreamTransformationFilter* stf = new StreamTransformationFilter(encryptor);
        encryptor.SetKeyWithIV(key, key.size(), iv);

        switch(encoding) {
        case Encoding::BASE64 : stf->Attach(new Base64Encoder(ss)); break;
        case Encoding::HEX : stf->Attach(new HexEncoder(ss)); break;
        case Encoding::NONE : stf->Attach(ss); break;
        default: stf->Attach(new Base64Encoder(ss));;
        }
        StringSource(plain, true, stf);
        emit cipherText(cipher);
        emit finished();
        return cipher;
    }
    catch(exception& e) {
        emit error(e.what());
    }
    return cipher;
}
string AesCBC::decryptText(const string& cipher, Keygen* keygen, const Encoding encoding) noexcept(false)
{
    std::string recover;
    try {
        const SecByteBlock& key = keygen->getKey();
        const SecByteBlock& iv = keygen->getIv();
        StringSink* ss = new StringSink(recover);
        CBC_Mode<AES>::Decryption decryptor;
        StreamTransformationFilter* stf = new StreamTransformationFilter(decryptor, ss);
        decryptor.SetKeyWithIV(key, key.size(), iv);

        switch(encoding) {
        case Encoding::BASE64 : StringSource(cipher, true, new Base64Decoder(stf)); break;
        case Encoding::HEX : StringSource(cipher, true, new HexDecoder(stf)); break;
        case Encoding::NONE : StringSource(cipher, true, stf); break;
        default: StringSource(cipher, true, new Base64Decoder(stf));
        }
        emit recoverText(recover);
        emit finished();
        return recover;
    }
    catch(exception& e) {
        emit error(e.what());
    }
    return recover;
}
void AesCBC::encryptFile(vector<string> paths, Keygen* keygen, const Encoding encoding)
{
    string output;
    try {
        const SecByteBlock& key = keygen->getKey();
        const SecByteBlock& iv = keygen->getIv();
        CBC_Mode<AES>::Encryption encryptor;
        encryptor.SetKeyWithIV(key, key.size(), iv);

        int progress = 0;
        for(const string& path : paths) {
            DirFname dirfname = extractFname(path, m_delim);
            output = (dirfname.m_dir + dirfname.m_delim + encryptText(dirfname.m_fname, keygen, Encoding::HEX));
            FileSink* fs = new FileSink(output.c_str());
            StreamTransformationFilter* stf = new StreamTransformationFilter(encryptor);

            switch(encoding) {
            case Encoding::BASE64 : stf->Attach(new Base64Encoder(fs)); break;
            case Encoding::HEX : stf->Attach(new HexEncoder(fs)); break;
            case Encoding::NONE : stf->Attach(fs); break;
            default: stf->Attach(new Base64Encoder(fs));;
            }
            FileSource(path.c_str(), true, stf);
            removeFile(path);
            emit proceed(++progress);
        }
        emit finished();
        emit success(successEncMsg(progress));
    }
    catch(exception& e) {
        removeFile(output);
        emit error(e.what());
        emit finished();
    }
}
void AesCBC::decryptFile(vector<string> paths, Keygen* keygen, const Encoding encoding)
{
    string output;
    try {
        const SecByteBlock& key = keygen->getKey();
        const SecByteBlock& iv = keygen->getIv();
        CBC_Mode<AES>::Decryption decryptor;
        decryptor.SetKeyWithIV(key, key.size(), iv);
        int progress = 0;
        for(const string& path : paths) {
            DirFname dirfname = extractFname(path, m_delim);
            output = (dirfname.m_dir + dirfname.m_delim + decryptText(dirfname.m_fname, keygen, Encoding::HEX));
            FileSink* fs = new FileSink(output.c_str());
            StreamTransformationFilter* stf  = new StreamTransformationFilter(decryptor, fs);

            switch(encoding) {
            case Encoding::BASE64 : FileSource(path.c_str(), true, new Base64Decoder(stf)); break;
            case Encoding::HEX : FileSource(path.c_str(), true, new HexDecoder(stf)); break;
            case Encoding::NONE : FileSource(path.c_str(), true, stf); break;
            default: FileSource(path.c_str(), true, new Base64Decoder(stf));
            }
            removeFile(path);
            emit proceed(++progress);
        }
        emit finished();
        emit success(successDecMsg(progress));
    }
    catch(exception& e) {
        removeFile(output);
        emit error(e.what());
        emit finished();
    }
}

