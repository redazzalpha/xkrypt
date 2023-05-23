#include "cipherbase.h"
#include "defines.h"
#include "except.h"
#include "keygenaes.h"
#include <base64.h>
#include <fstream>
#include <hex.h>

using namespace CryptoPP;
using namespace std;

// constructors
AbstractCipher::AbstractCipher(){}

// destructor
AbstractCipher::~AbstractCipher(){}

// methods
void AbstractCipher::setEncfname(bool newEncfname)
{
    m_encfname = newEncfname;
}
void AbstractCipher::setDecfname(bool newDecfname)
{
    m_decfname = newDecfname;
}
bool AbstractCipher::encfname() const
{
    return m_encfname;
}
bool AbstractCipher::decfname() const
{
    return m_decfname;
}

DirFname AbstractCipher::extractFname(const std::string& path) const {
    int pos = path.find_last_of(DELIMITOR);
    string dir = path.substr(0, pos);
    string fname = path.substr(pos+1, path.size() - pos);
    return DirFname(dir, fname);
}
string AbstractCipher::pumpRefs(const  string &path)
{
    string refs, decodedRefs;
    FileSource source(path.c_str(), false, new StringSink(refs));
    do {
        source.Pump(1);
    } while(refs[refs.size()-1] != '\n' && refs[refs.size()-1] != '\0' && refs[refs.size()-1] != '=');
    StringSource(refs.c_str(), true, new Base64Decoder(new CryptoPP::StringSink(decodedRefs)));
    return decodedRefs;
}
void AbstractCipher::injectRefs(FileSink* fs, AbstractKeygen* keygen)
{
    std::vector<CryptoPP::byte> xkrypt_refs {
        XKRYPT_REF_VERSION,
        XKRYPT_REF_MODEL,
        (CryptoPP::byte)keygen->encoding(),
        (CryptoPP::byte)algId(),
        (CryptoPP::byte)modeId(),
        (CryptoPP::byte)m_encfname,
    };

//    SecByteBlock salt = keygen->salt();
//    for(size_t i = 0; i < XKRYPT_SALT_SIZE; i++)
//        xkrypt_refs.push_back(salt[i]);

//    if(auto kg_aes_cast = dynamic_cast<KeygenAes*>(keygen)) {
//        SecByteBlock iv = kg_aes_cast->Iv();
//        for(size_t i = 0; i < XKRYPT_IV_SIZE; i++)
//            xkrypt_refs.push_back(iv[i]);
//    }

    StringSource refsSource(&xkrypt_refs[0], xkrypt_refs.size(), true, new Base64Encoder(new Redirector(*fs)));
}
int AbstractCipher::afterRefs(FileSource* fs)
{
    string sink;
    int count = 0;
    fs->Attach(new StringSink(sink));
    do { fs->Pump(1); count++;} while(sink[sink.size()-1] != '\n' && sink[sink.size()-1] != '\0' && sink[sink.size()-1] != '=');
    fs->Detach();

    std::cout << "sink : " << sink << std::endl;

    return count;
}
string AbstractCipher::checkRefs(const std::string &path)
{
    string refs = pumpRefs(path);
    if(refs.size() != XKRYPT_REF_SIZE) throw InvalidRefsException();
    if((refs[0] < XKRYPT_REF_VERSION)) throw VersionException();
    if((refs[1] != XKRYPT_REF_MODEL)) throw ModelException();
    if(!(refs[5] == XKRYPT_REF_DECFNAME || refs[5] == XKRYPT_REF_NOTDECFNAME)) throw DecFnameRefsException();
//    if(refs.size() - XKRYPT_REF_SIZE_UNIT != XKRYPT_SALT_SIZE + XKRYPT_IV_SIZE) throw SaltRefsException();
    return refs;
}

