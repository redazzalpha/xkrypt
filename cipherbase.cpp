#include "cipherbase.h"
#include "defines.h"
#include "except.h"
#include <base64.h>
#include <fstream>
#include <hex.h>
#include <sstream>

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
string AbstractCipher::pumpSalt(CryptoPP::StringSource* cipher)
{
    string salt, decodedSalt;
    cipher->Detach(new StringSink(salt));
    do {
        cipher->Pump(1);
    } while(salt[salt.size()-1] != '\n' && salt[salt.size()-1] != '\0' && salt[salt.size()-1] != '=');
    StringSource(salt.c_str(), true, new Base64Decoder(new CryptoPP::StringSink(decodedSalt)));
    cipher->Detach();
    return decodedSalt;
}
string AbstractCipher::pumpRefs(FileSource* source)
{
    string refs, decodedRefs;
    source->Attach(new StringSink(refs));
    do {
        source->Pump(1);
    } while(refs[refs.size()-1] != '\n' && refs[refs.size()-1] != '\0' && refs[refs.size()-1] != '=');
    StringSource(refs.c_str(), true, new Base64Decoder(new CryptoPP::StringSink(decodedRefs)));
    source->Detach();
    return decodedRefs;
}
string AbstractCipher::checkRefs(const std::string &path)
{
    string refs = pumpRefs(new FileSource(path.data(), false));
    if(refs.size() != XREF_SIZE) throw InvalidRefsException();
    if((refs[0] < XREF_VERSION)) throw VersionException();
    if((refs[1] != XREF_MODEL)) throw ModelException();
    if(!(refs[5] == XREF_DECFNAME || refs[5] == XREF_NOTDECFNAME)) throw DecFnameRefsException();
    return refs;
}
string AbstractCipher::checkRefs(FileSource* source)
{
    string refs = pumpRefs(source);
    if(refs.size() != XREF_SIZE) throw InvalidRefsException();
    if((refs[0] < XREF_VERSION)) throw VersionException();
    if((refs[1] != XREF_MODEL)) throw ModelException();
    if(!(refs[5] == XREF_DECFNAME || refs[5] == XREF_NOTDECFNAME)) throw DecFnameRefsException();
    return refs;
}
int AbstractCipher::afterRefs(const std::string &path)
{
    string sink;
    size_t size;
    int count = 0;
    FileSource source(path.data(), false, new StringSink(sink));
    do { source.Pump(1); count++; size = sink.size() - 1;}
    while(sink[size] != '\n' &&
           sink[size] != '\0' &&
           sink[size] != '='
           );
    source.Detach();
    return count;
}
int AbstractCipher::afterRefs(FileSource* fs)
{
    string sink;
    size_t size;
    int count = 0;
    fs->Attach(new StringSink(sink));
    do { fs->Pump(1); count++; size = sink.size() - 1;}
    while(sink[size] != '\n' &&
           sink[size] != '\0' &&
           sink[size] != '='
           );
    fs->Detach();
    return count;
}
int AbstractCipher::afterRefs(StringSource* ss)
{
    string sink;
    size_t size;
    int count = 0;
    ss->Attach(new StringSink(sink));
    do { ss->Pump(1); count++; size = sink.size() - 1;}
    while(sink[size] != '\n' &&
           sink[size] != '\0' &&
           sink[size] != '='
           );
    ss->Detach();
    return count;
}
void AbstractCipher::injectRefs(FileSink* fs, AbstractKeygen* keygen)
{
    SecByteBlock salt = keygen->salt();
    std::vector<CryptoPP::byte> xrefs {
        XREF_VERSION,
        XREF_MODEL,
        (CryptoPP::byte)keygen->encoding(),
        (CryptoPP::byte)algId(),
        (CryptoPP::byte)modeId(),
        (CryptoPP::byte)m_encfname,
    };

    for(size_t i = 0; i < SALT_SIZE; i++)
        xrefs.push_back(salt[i]);

    StringSource refsSource(&xrefs[0], xrefs.size(), true, new Base64Encoder(new Redirector(*fs)));
}
string AbstractCipher::stringRefs(AbstractKeygen* keygen)
{
    SecByteBlock salt = keygen->salt();
    int count = 0;
    string xrefs;
    xrefs.resize(XREF_SIZE);

    xrefs[count++] = XREF_VERSION;
    xrefs[count++] = XREF_MODEL;
    xrefs[count++] = (CryptoPP::byte)keygen->encoding();
    xrefs[count++] = (CryptoPP::byte)algId();
    xrefs[count++] = (CryptoPP::byte)modeId();
    xrefs[count++] = (CryptoPP::byte)encfname();

    for(size_t i = 0; i < SALT_SIZE; i++)
        xrefs[count++] = salt[i];

    return xrefs;
}


