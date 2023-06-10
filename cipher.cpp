#include "cipher.h"
#include "aescbc.h"
#include "aesccm.h"
#include "aescfb.h"
#include "aesctr.h"
#include "aeseax.h"
#include "aesecb.h"
#include "aesgcm.h"
#include "aesofb.h"
#include "cipher.h"
#include "cipheraes.h"
#include "cipherrsa.h"
#include "rsaoaep.h"
#include "defines.h"
#include "except.h"
#include "keygenaes.h"
#include "keygenrsa.h"
#include <QFile>
#include <base64.h>
#include <files.h>
#include <hex.h>

using namespace CryptoPP;
using namespace std;

// constructors
Cipher::Cipher(){}

// destructor
Cipher::~Cipher() {
    delete m_cipher;
    m_cipher = nullptr;
}

// methods
void Cipher::setEncfname(bool newEncfname)
{
    m_cipher->setEncfname(newEncfname);
}
void Cipher::setDecfname(bool newDecfname)
{
    m_cipher->setDecfname(newDecfname);
}
bool Cipher::encfname()
{
    return m_cipher->encfname();
}
bool Cipher::decfname()
{
    return m_cipher->decfname();
}

string Cipher::algName() const
{
    return m_cipher->algName();
}
string Cipher::modeName() const
{
    return m_cipher->modeName();
}
Algorithms Cipher::algId() const
{
    return m_cipher->algId();
}
Mode Cipher::modeId() const
{
    return m_cipher->modeId();
}
string Cipher::successMsg(const int succeed, const bool mode)
{
    stringstream ss;
    ss << (mode?"Encryption ": "Decryption ") << "successfull!<br />";
    ss << std::to_string(succeed) + " file(s) written<br />";
    ss << "Using "  << algName() + " - " + modeName() << " mode<br />";
    return ss.str();
}
void Cipher::cipherNew(const string& alg, const string& mode)
{
    if(m_cipher) {
        delete m_cipher;
        m_cipher = nullptr;
    }

    // aes algs
    if(alg == AbstractCipherAes::AlgName) {
        if(mode == AesCBC::ModeName) m_cipher = new AesCBC;
        else if(mode == AesEAX::ModeName) m_cipher = new AesEAX;
        else if(mode == AesGCM::ModeName) m_cipher = new AesGCM;
        else if(mode == AesCCM::ModeName) m_cipher = new AesCCM;
        else if(mode == AesECB::ModeName) m_cipher = new AesECB;
        else if(mode == AesCFB::ModeName) m_cipher = new AesCFB;
        else if(mode == AesOFB::ModeName) m_cipher = new AesOFB;
        else if(mode == AesCTR::ModeName) m_cipher = new AesCTR;
        else throw ModeException();
    }
    // rsa algs
    else if(alg == AbstractCipherRsa::AlgName) {
        if(mode == RsaOAEP::ModeName) m_cipher = new RsaOAEP;
        else throw ModeException();
    }
    else throw AlgException();
}

void Cipher::setIsContentEnc(const bool state)
{
    m_cipher->setIsContentEnc(state);
}
void Cipher::cipherDetect(const string& refs)
{
    string alg;
    switch(refs[3]) {
    case Algorithms::AES : alg = AbstractCipherAes::AlgName; break;
    case Algorithms::RSA : alg = AbstractCipherRsa::AlgName; break;
    default: throw AlgRefsException();
    }

    string mode;
    if(alg == AbstractCipherAes::AlgName) {
        switch(refs[4]) {
        case Mode::CBC :  mode = AesCBC::ModeName; break;
        case Mode::CCM :  mode = AesCCM::ModeName; break;
        case Mode::CFB :  mode = AesCFB::ModeName; break;
        case Mode::CTR :  mode = AesCTR::ModeName; break;
        case Mode::EAX :  mode = AesEAX::ModeName; break;
        case Mode::ECB :  mode = AesECB::ModeName; break;
        case Mode::GCM :  mode = AesGCM::ModeName; break;
        case Mode::OFB :  mode = AesOFB::ModeName; break;
        default: throw ModeRefsException();
        }
    }
    if(alg == AbstractCipherRsa::AlgName) {
        switch(refs[4]) {
        case Mode::OEAP :  mode = RsaOAEP::ModeName; break;
        default: throw ModeRefsException();
        }
    }
    cipherNew(alg, mode);
}
void Cipher::kill()
{
    m_run = false;
}
string Cipher::encodeText(const std::string &text, const Encoding encoding)
{
    string sink;
    switch(encoding) {
    case Encoding::BASE64 : StringSource(text, true, new Base64Encoder(new StringSink(sink))); break;
    case Encoding::HEX : StringSource(text, true, new HexEncoder(new StringSink(sink))); break;
    case Encoding::NONE : StringSource(text, true, new StringSink(sink)); break;
    default : throw EncodingException();
    }
    return sink;
}
string Cipher::stringRefs(AbstractKeygen* keygen)
{
    return m_cipher->stringRefs(keygen);
}
void Cipher::checkLogic(AbstractKeygen* keygen)
{
    string alg = m_cipher->algName();
    if(alg == AbstractCipherAes::AlgName)
        if(!dynamic_cast<KeygenAes*>(keygen)) throw LogicException();
    if(alg == AbstractCipherRsa::AlgName)
        if(!dynamic_cast<KeygenRsa*>(keygen)) throw LogicException();
}

// slots
string Cipher::encryptText(const string& plain, AbstractKeygen* keygen, const Encoding encoding) noexcept(false)
{
    std::string cipher = "";
    try {
        keygen->setEncoding(encoding);

        if(auto kg_aes_cast = dynamic_cast<KeygenAes*>(keygen)) {
            if(kg_aes_cast->pkState()) kg_aes_cast->pkDerive(keygen->password(), m_cipher->isContentEnc());
            else kg_aes_cast->pkDerive(m_cipher->isContentEnc());
        }

        cipher = m_cipher->encryptText(plain, keygen, encoding);

        emit proceed();
        if(m_cipher->isContentEnc()) emit cipherText(cipher);
        return cipher;
    }
    catch(exception& e) {
        emit error(e.what());
    }
    return cipher;
}
string Cipher::decryptText(const string& cipher, AbstractKeygen* keygen) noexcept(false)
{
    string refs;
    string recover = "";
    try {
        checkLogic(keygen);
        StringSource cipherSource(cipher, false);

        refs = m_cipher->checkRefs(&cipherSource);
        if(refs[6] != keygen->pkState()) throw PkStateException();
        keygen->salt() = SecByteBlock((CryptoPP::byte*)&refs[XREF_SIZE_UNIT], SALT_SIZE);

        Encoding encoding;
        switch(static_cast<Encoding>(refs[2])) {
        case Encoding::BASE64 : encoding = Encoding::BASE64; break;
        case Encoding::HEX : encoding = Encoding::HEX; break;
        case Encoding::NONE : encoding = Encoding::NONE; break;
        default: throw EncodingRefsException();
        }

        cipherDetect(refs);
        m_cipher->setDecfname(refs[5]);
        keygen->setEncoding(encoding);

        if(auto kg_aes_cast = dynamic_cast<KeygenAes*>(keygen)) {
            if(kg_aes_cast->pkState())kg_aes_cast->pkDerive(keygen->password(), false);
            else kg_aes_cast->pkDerive(false);
        }

        recover = m_cipher->decryptText(cipher, keygen, encoding);

        emit autoDetect(m_cipher->algName(), m_cipher->modeName(), encoding, refs[5], "Text");
        emit proceed();
        emit recoverText(recover);
        return recover;
    }
    catch(InvalidRefsException& e) {
        emit error(e.what(), "-- It seems that you are trying to decrypt text\
 that hasn't been encrypted by xkrypt or refs has been corrupt.");
    }
    catch(LogicException& e) {

        string details =
            "The key does not match with the current detected cipher.\n"
            "Please try to import or re-import the proper key type.\n\n"
            "-- type of used encryption: ";
        details += m_cipher->algName();
        emit error(e.what(), details);
    }
    catch(PkStateException& e) {
        string details = "-- The text you are trying to decrypt has been encrypted using ";
        details += (refs[6]? "\"password key\"":"\"symmetric key\"");
        details += ".\n\nPlease ";
        details += (refs[6]? "check ":"uncheck ");
        details += "\"Use password\" in the key manager section ";
        details += (!refs[6]? "import the proper key ":"");
        details += " and retry.";
        emit error(e.what(), details);
    }
    catch(exception& e) {
        emit error(e.what());
    }
    return recover;
}
void Cipher::encryptFile(vector<string> paths, AbstractKeygen* keygen, const Encoding encoding)
{
    try {
        keygen->setEncoding(encoding);
        size_t size = paths.size(), progress;

        for(progress = 0; progress < size && m_run; progress++) {
            const string path = paths[progress];
            DirFname dirfname = m_cipher->extractFname(path);
            emit processing(dirfname.m_fname);

            if(auto kg_aes_cast = dynamic_cast<KeygenAes*>(keygen)) {
                if(kg_aes_cast->pkState()) kg_aes_cast->pkDerive(keygen->password());
                else kg_aes_cast->pkDerive();
            }

            m_cipher->encryptFile(path, keygen, encoding);

            emit proceed(progress+1);
        }

        emit cipherFile(successMsg(progress));
    }
    catch(exception& e) {
        emit error(e.what());
    }
}
void Cipher::decryptFile(vector<string> paths, AbstractKeygen* keygen)
{
    string refs;
    try {
        checkLogic(keygen);
        size_t size = paths.size(), progress;

        for(progress = 0; progress < size && m_run; progress++) {
            const string path = paths[progress];
            DirFname dirfname = m_cipher->extractFname(path);
            emit processing(dirfname.m_fname);

            refs = m_cipher->checkRefs(path);
            if(refs[6] != keygen->pkState()) throw PkStateException();
            keygen->salt() = SecByteBlock((CryptoPP::byte*)&refs[XREF_SIZE_UNIT], SALT_SIZE);

            Encoding encoding;
            switch(static_cast<Encoding>(refs[2])) {
            case Encoding::BASE64 : encoding = Encoding::BASE64; break;
            case Encoding::HEX : encoding = Encoding::HEX; break;
            case Encoding::NONE : encoding = Encoding::NONE; break;
            default: throw EncodingRefsException();
            }

            cipherDetect(refs);
            m_cipher->setDecfname(refs[5]);
            keygen->setEncoding(encoding);

            if(auto kg_aes_cast = dynamic_cast<KeygenAes*>(keygen)) {
                if(kg_aes_cast->pkState()) kg_aes_cast->pkDerive(keygen->password(), false);
                else kg_aes_cast->pkDerive(false);
            }

            m_cipher->decryptFile(path, keygen, encoding);

            emit autoDetect(m_cipher->algName(), m_cipher->modeName(), encoding, refs[5], "File");
            emit proceed(progress+1);
        }

        emit recoverFile(successMsg(progress, false));
    }
    catch(InvalidRefsException& e) {
        emit error(e.what(), "-- It seems that you are trying to decrypt file\
 that hasn't been encrypted by xkrypt or refs has been corrupt.");
    }
    catch(LogicException& e) {
        string details =
            "The key does not match with the current detected cipher.\n"
            "Please try to import or re-import the proper key type.\n\n"
            "-- type of used encryption: ";
        details += m_cipher->algName();
        emit error(e.what(), details);
    }
    catch(PkStateException& e) {
        string details = "-- The file(s) you are trying to decrypt has been encrypted using ";
        details += (refs[6]? "\"password key\"":"\"symmetric key\"");
        details += ".\n\nPlease ";
        details += (refs[6]? "check ":"uncheck ");
        details += "\"Use password\" in the key manager section ";
        details += (!refs[6]? "import the proper key ":"");
        details += " and retry.";
        emit error(e.what(), details);
    }
    catch(exception& e) {
        emit error(e.what());
    }
}




























