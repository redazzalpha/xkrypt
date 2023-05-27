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
string AbstractCipher::checkRefs(const std::string &path)
{
    string refs = pumpRefs(path);
    if(refs.size() != XREF_SIZE) throw InvalidRefsException();
    if((refs[0] < XREF_VERSION)) throw VersionException();
    if((refs[1] != XREF_MODEL)) throw ModelException();
    if(!(refs[5] == XREF_DECFNAME || refs[5] == XREF_NOTDECFNAME)) throw DecFnameRefsException();
    return refs;
}


