#include "keygenserial.h"
#include "base64.h"
#include "defines.h"
#include "files.h"
#include "cryptopp/pem.h"
#include "hex.h"
#include "except.h"
#include <QFileDialog>
#include <fstream>
#include<vector>
#include <bits/streambuf_iterator.h>

using namespace CryptoPP;
using namespace std;

// constructors
KeygenSerial::KeygenSerial(){};

// methods
bool KeygenSerial::deserialize(ifstream* file, KeygenAes* keygen) const noexcept(false)
{
    bool imported = false;

    if(file) {
        size_t ivsize = static_cast<size_t>(Aes::IvSize::LENGTH_DEFAULT);
        string refs, keyiv;
        FileSource fs(*file, false);

        fs.Attach(new StringSink(refs));
        fs.Pump(XKRYPT_KEY_REF_SIZE);

        if((refs[0] < XKRYPT_REF_VERSION)) throw VersionException();
        if( (refs[1] != XKRYPT_REF_MODEL)) throw ModelException();

        switch(refs[2]) {
        case Encoding::BASE64 : fs.Detach(new Base64Decoder); break;
        case Encoding::HEX : fs.Detach(new HexDecoder); break;
        case Encoding::NONE : fs.Detach(); break;
        default : throw EncodingException();
        }

        fs.Attach(new StringSink(keyiv));
        fs.PumpAll();

        keygen->setIv(SecByteBlock((uchar*) &keyiv[0], ivsize));
        keygen->setKey(SecByteBlock((uchar*) &keyiv[ivsize], keyiv.size() - ivsize));

        imported = true;
    }

    return imported;
}
bool KeygenSerial::deserialize(ifstream* file, KeygenRsa* keygen) const noexcept(false)
{
    FileSource fsource(*file, true);
    switch(keygen->encoding()) {
    case Encoding::BER :
    case Encoding::DER:
        keygen->getPrivate()->Load(fsource);
        break;
    case Encoding::PEM :
        CryptoPP::PEM_Load(fsource, *keygen->getPrivate());
        break;
    default: throw EncodingException();
    }
}
void KeygenSerial::serialize(const string& where, KeygenAes* keygen) const
{
    size_t ivSize = keygen->getIv().size();
    size_t keySize = keygen->getKey().size();
    size_t keyIvSize = ivSize + keySize;
    std::vector<CryptoPP::byte> xkrypt_refs {
        XKRYPT_REF_VERSION,
        XKRYPT_REF_MODEL,
        (CryptoPP::byte)keygen->encoding(),
    };
    CryptoPP::byte* keyIv = new CryptoPP::byte[keyIvSize];
    StringSource refsSource(&xkrypt_refs[0], xkrypt_refs.size(), false);
    StringSource keyIvSource(keyIv, keyIvSize, false);
    FileSink fs(where.c_str(), true);

    memcpy(keyIv, keygen->getIv().BytePtr(), ivSize);
    memcpy(keyIv + ivSize, keygen->getKey().BytePtr(), keySize);

    switch(keygen->encoding()) {
    case Encoding::BASE64 :
        keyIvSource.Attach(new Base64Encoder);
        break;
    case Encoding::HEX :
        keyIvSource.Attach(new HexEncoder);
    case Encoding::NONE :
        break;
    default :
        keyIvSource.Attach(new Base64Encoder);
        break;
    }

    refsSource.Attach(new Redirector(fs));
    keyIvSource.Attach(new Redirector(fs));

    refsSource.PumpAll();
    keyIvSource.PumpAll();
}
void KeygenSerial::serialize(const string& where, KeygenRsa* keygen) const
{
    FileSink fsink(where.data(), true);
    switch(keygen->encoding()) {
    case Encoding::BER :
        keygen->getPrivate()->::PKCS8PrivateKey::BEREncode(fsink);
        break;
    case Encoding::DER:
        keygen->getPrivate()->DEREncode(fsink);
        break;
    case Encoding::PEM :
        CryptoPP::PEM_Save(fsink, *keygen->getPrivate());
        break;
    default: throw EncodingException();
    }
}
string KeygenSerial::serialize(KeygenAes* keygen) const
{
    StringSource keySource(keygen->getKey().BytePtr(), keygen->getKey().size(), false);
    string key;

    switch(keygen->encoding()) {
    case Encoding::BASE64 :
        keySource.Attach(new Base64Encoder);
        break;
    case Encoding::HEX :
        keySource.Attach(new HexEncoder);
    case Encoding::NONE :
        break;
    default :
        keySource.Attach(new Base64Encoder);
        break;
    }

    keySource.Attach(new StringSink(key));
    keySource.PumpAll();
    return key;
}
string KeygenSerial::serialize(KeygenRsa* keygen) const
{
    return "Asymmetric Rsa key\nkey size: " + std::to_string(keygen->keysize()) + " bits" ;
}
string KeygenSerial::serializeEncoding(const Encoding encoding) const
{
    switch(encoding)  {
    case Encoding::BASE64: return "Base64";
    case Encoding::HEX: return "Hex";
    case Encoding::NONE: return "None";
    case Encoding::BER: return "Ber";
    case Encoding::DER: return "Der";
    case Encoding::PEM: return "Pem";
    default: throw EncodingException();
    }
}

string KeygenSerial::successWriteKey(const string& path, KeygenAes* keygen)
{
    string message = "key " + std::to_string(keygen->getKey().size()) + " bytes - encoded ";
    message += serializeEncoding(keygen->encoding());
    message += "<br />has been successfully written on file<br />" + path;
    return message;
}
string KeygenSerial::successWriteKey(const string& path, KeygenRsa* keygen)
{
}

