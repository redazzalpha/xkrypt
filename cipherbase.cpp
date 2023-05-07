#include "cipherbase.h"
#include "defines.h"
#include "except.h"
#include <base64.h>
#include <fstream>
#include <hex.h>

using namespace CryptoPP;
using namespace std;

// constructors
AbstractCipherBase::AbstractCipherBase(){}

// destructor
AbstractCipherBase::~AbstractCipherBase(){}

// methods
void AbstractCipherBase::setEncfname(bool newEncfname)
{
    m_encfname = newEncfname;
}
void AbstractCipherBase::setDecfname(bool newDecfname)
{
    m_decfname = newDecfname;
}
bool AbstractCipherBase::encfname() const
{
    return m_encfname;
}
bool AbstractCipherBase::decfname() const
{
    return m_decfname;
}

DirFname AbstractCipherBase::extractFname(const std::string& path) const {
    int pos = path.find_last_of(DELIMITOR);
    string dir = path.substr(0, pos);
    string fname = path.substr(pos+1, path.size() - pos);
    return DirFname(dir, fname);
}
string AbstractCipherBase::pumpRefs(const string &path)
{
    string refs, decodedRefs;
    FileSource source(path.c_str(), false, new StringSink(refs));
    do {
        source.Pump(1);
    } while(refs[refs.size()-1] != '\n' && refs[refs.size()-1] != '\0' && refs[refs.size()-1] != '=');
    StringSource(refs.c_str(), true, new Base64Decoder(new CryptoPP::StringSink(decodedRefs)));
    return decodedRefs;
}
void AbstractCipherBase::injectRefs(FileSink* fs, const Encoding encoding)
{
    std::vector<CryptoPP::byte> xkrypt_refs {
        XKRYPT_REF_VERSION,
        XKRYPT_REF_MODEL,
        (CryptoPP::byte)encoding,
        (CryptoPP::byte)algId(),
        (CryptoPP::byte)modeId(),
        (CryptoPP::byte)m_encfname,
    };
    StringSource refsSource(&xkrypt_refs[0], xkrypt_refs.size(), true, new Base64Encoder(new Redirector(*fs)));
}
int AbstractCipherBase::afterRefs(FileSource* fs)
{
    string sink;
    int i = 0;
    fs->Attach(new StringSink(sink));
    do { fs->Pump(1); i++;} while(sink[sink.size()-1] != '\n' && sink[sink.size()-1] != '\0' && sink[sink.size()-1] != '=');
    fs->Detach();
    return i;
}
string AbstractCipherBase::checkRefs(const std::string &path)
{
    string refs = pumpRefs(path);
    if(refs.size() != XKRYPT_REF_SIZE) throw InvalidRefsException();
    if((refs[0] < XKRYPT_REF_VERSION)) throw VersionException();
    if((refs[1] != XKRYPT_REF_MODEL)) throw ModelException();
    if(!(refs[5] == XKRYPT_REF_DECFNAME || refs[5] == XKRYPT_REF_NOTDECFNAME)) throw DecFnameRefsException();
    return refs;
}

