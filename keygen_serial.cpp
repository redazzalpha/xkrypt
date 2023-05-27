#include "keygen_serial.h"
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
Keygen_serial::Keygen_serial(){};

// methods
bool Keygen_serial::deserialize(ifstream* file, KeygenAes* keygen) const noexcept(false)
{
    bool imported = false;

    if(file) {
        string refs, keyiv;
        size_t ivsize = keygen->Iv().size();
        FileSource fs(*file, false);

        fs.Attach(new StringSink(refs));
        fs.Pump(XREF_SIZE_KEY);

        if((refs[0] < XREF_VERSION)) throw VersionException();
        if( (refs[1] != XREF_MODEL)) throw ModelException();

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
bool Keygen_serial::deserialize(ifstream* file, KeygenRsa* keygen) const noexcept(false)
{
    bool imported = false;

    if(file) {
        FileSource fsource(*file, true);
        CryptoPP::RSA::PrivateKey* pvk = keygen->getPrivate();

        switch(keygen->encoding()) {
        case Encoding::BER :
        case Encoding::DER: pvk->Load(fsource); break;
        case Encoding::PEM : CryptoPP::PEM_Load(fsource, *pvk); break;
        default: throw EncodingException();
        }
        keygen->setPublic(pvk);
        keygen->setKeysize(pvk->MaxImage().ByteCount() * 8);
        imported = true;
    }
    return imported;
}
void Keygen_serial::serialize(const string& path, KeygenAes* keygen) const
{
    size_t ivSize = keygen->Iv().size();
    size_t keySize = keygen->key().size();
    size_t keyIvSize = ivSize + keySize;
    std::vector<CryptoPP::byte> xkrypt_refs {
        XREF_VERSION,
        XREF_MODEL,
        (CryptoPP::byte)keygen->encoding(),
    };
    CryptoPP::byte* keyIv = new CryptoPP::byte[keyIvSize];
    StringSource refsSource(&xkrypt_refs[0], xkrypt_refs.size(), false);
    StringSource keyIvSource(keyIv, keyIvSize, false);
    FileSink fs(path.c_str(), true);

    memcpy(keyIv, keygen->Iv().BytePtr(), ivSize);
    memcpy(keyIv + ivSize, keygen->key().BytePtr(), keySize);

    switch(keygen->encoding()) {
    case Encoding::BASE64 : keyIvSource.Attach(new Base64Encoder); break;
    case Encoding::HEX : keyIvSource.Attach(new HexEncoder); break;
    case Encoding::NONE : break;
    default : throw EncodingException();
    }

    refsSource.Attach(new Redirector(fs));
    keyIvSource.Attach(new Redirector(fs));

    refsSource.PumpAll();
    keyIvSource.PumpAll();
}
void Keygen_serial::serialize(const string& path, KeygenRsa* keygen) const
{
    FileSink privateKey((path + "_").data(), true);
    FileSink publicKey(path.data(), true);
    CryptoPP::RSA::PrivateKey* pvk = keygen->getPrivate();
    CryptoPP::RSA::PublicKey* pbk = keygen->getPublic();
    switch(keygen->encoding()) {
    case Encoding::BER :
        pvk->::PKCS8PrivateKey::BEREncode(privateKey);
        pbk->::X509PublicKey::BEREncode(publicKey);
        break;
    case Encoding::DER:
        pvk->DEREncode(privateKey);
        pbk->DEREncode(publicKey);
        break;
    case Encoding::PEM :
        CryptoPP::PEM_Save(privateKey, *pvk);
        CryptoPP::PEM_Save(publicKey, *pbk);
        break;
    default: throw EncodingException();
    }
}
string Keygen_serial::serialize(KeygenAes* keygen) const
{
    StringSource keySource(keygen->key().BytePtr(), keygen->key().size(), false);
    string key;

    switch(keygen->encoding()) {
    case Encoding::BASE64 : keySource.Attach(new Base64Encoder); break;
    case Encoding::HEX : keySource.Attach(new HexEncoder); break;
    case Encoding::NONE : break;
    default : throw EncodingException();
    }

    keySource.Attach(new StringSink(key));
    keySource.PumpAll();

    stringstream ss;
    ss << "-- Symmetric key:\n";
    ss << key;
    return ss.str();
}
string Keygen_serial::serialize(KeygenRsa* keygen) const
{
    keygen->setKeysize(keygen->getPrivate()->MaxImage().ByteCount() * 8);
    InvertibleRSAFunction params = keygen->params();

    stringstream ss;
    ss << "--Asymmetric Rsa keys:\n";
    ss << "size: " << std::to_string(keygen->keysize()) + " bits\n";
    ss << "modulus: " << truncateInteger(params.GetModulus()) << "...\n";
    ss << "prime1: " << truncateInteger(params.GetPrime1()) << "...\n";
    ss << "prime2: " << truncateInteger(params.GetPrime2()) << "...\n";
    ss << "public exponent: " << params.GetPublicExponent() << "\n";
    ss << "private exponent: " << truncateInteger(params.GetPrivateExponent()) << "...\n";

    return ss.str();
}
string Keygen_serial::serializeEncoding(const Encoding encoding) const
{
    switch(encoding)  {
    case Encoding::BASE64: return "Base64";
    case Encoding::HEX: return "Hex";
    case Encoding::NONE: return "None";
    case Encoding::BER: return "BER";
    case Encoding::DER: return "DER";
    case Encoding::PEM: return "PEM";
    default: throw EncodingException();
    }
}

template<class T>
bool Keygen_serial::deserialize(std::ifstream *file, T *keygen, const Encoding encoding) const noexcept(false)
{
    keygen->setEncoding(encoding);
    return deserialize(file, keygen);
}
template<class T>
void Keygen_serial::serialize(const std::string &where, T *keygen, Encoding encoding) const
{
    keygen->setEncoding(encoding);
    serialize(where, keygen);
}
template<class T>
string Keygen_serial::serialize(T* keygen, const Encoding encoding) const
{
    keygen->setEncoding(encoding);
    return serialize(keygen);
}

string Keygen_serial::successWriteKey(const std::string &path, AbstractKeygen *keygen)
{
    stringstream ss;
    ss << "key " << std::to_string(keygen->keysize()) << " bytes ";
    ss << " - encoded " << serializeEncoding(keygen->encoding()) << "<br />";
    ss << "has been successfully written on file<br />" << path;
    return ss.str();
}
string Keygen_serial::truncateInteger(const Integer& integer, const size_t size) const
{
    stringstream ss;
    ss << integer;
    string truncated = ss.str();
    truncated.resize(size);
    return truncated;
}



