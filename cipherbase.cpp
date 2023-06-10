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
AbstractCipher::AbstractCipher() {}

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
void AbstractCipher::setIsContentEnc(bool newCipherRefs)
{
    m_isContentEnc = newCipherRefs;
}
bool AbstractCipher::encfname() const
{
    return m_encfname;
}
bool AbstractCipher::decfname() const
{
    return m_decfname;
}
bool AbstractCipher::isContentEnc() const
{
    return m_isContentEnc;
}

DirFname AbstractCipher::extractFname(const std::string& path) const {
    int pos = path.find_last_of(DELIMITOR);
    string dir = path.substr(0, pos);
    string fname = path.substr(pos+1, path.size() - pos);
    return DirFname(dir, fname);
}
std::vector<CryptoPP::byte> &AbstractCipher::vector_xrefs(AbstractKeygen *keygen)
{
    SecByteBlock salt = keygen->salt();

    m_xrefs.clear();
    m_xrefs.push_back(XREF_VERSION);
    m_xrefs.push_back(XREF_MODEL);
    m_xrefs.push_back(keygen->encoding());
    m_xrefs.push_back(algId());
    m_xrefs.push_back(modeId());
    m_xrefs.push_back(m_encfname);
    m_xrefs.push_back(keygen->pkState());

    for(size_t i = 0; i < SALT_SIZE; i++) m_xrefs.push_back(salt[i]);

    return m_xrefs;
}

void AbstractCipher::injectRefs(Sink *sink, AbstractKeygen *keygen)
{
    auto v_xrefs = (CryptoPP::byte *)&vector_xrefs(keygen)[0];
    StringSource(v_xrefs, m_xrefs.size(), true,new Base64Encoder(new Redirector(*sink)));


/*
 * SECOND VERSION OF
 * REFS INJECTION WITH NO END LINE AND
 * EQUAL SIGN AT THE END
 *
 *  auto v_xrefs = (CryptoPP::byte *)&vector_xrefs(keygen)[0];
 *  string encodedRefs;
 *  Base64Encoder encoder;
 *  encoder.PutMessageEnd(v_xrefs, m_xrefs.size());
 *  encodedRefs.resize(encoder.MaxRetrievable());
 *  encoder.Get((CryptoPP::byte*)encodedRefs.data(), encodedRefs.size());
 *
 *  int eqSignIndex = 0, endLineIndex = 0;
 *  eqSignIndex = encodedRefs.find("=");
 *  endLineIndex = encodedRefs.find("\n");
 *
 *  if(eqSignIndex > 0) encodedRefs = encodedRefs.substr(0, encodedRefs.size()-1);
 *  else encodedRefs = encodedRefs.replace(endLineIndex, 1, "=");
 *
 *  StringSource(encodedRefs, true, new Redirector(*sink));
 *
*/

}
void AbstractCipher::injectRefs(string &sink, AbstractKeygen *keygen)
{
    StringSink ssink(sink);
    injectRefs(&ssink, keygen);
}

string AbstractCipher::pumpRefs(Source *source)
{
    string refs, decodedRefs;
    source->Attach(new StringSink(refs));

    do source->Pump(1);
    while(
        refs[refs.size()-1] != '\n' &&
        refs[refs.size()-1] != '\0' &&
        refs[refs.size()-1] != '='
    );

    StringSource(refs.c_str(), true, new Base64Decoder(new CryptoPP::StringSink(decodedRefs)));
    source->Detach();
    return decodedRefs;
}
string AbstractCipher::pumpRefs(const string& cipherText)
{
    StringSource source(cipherText, false);
    return pumpRefs(&source);
}

string AbstractCipher::checkRefs(CryptoPP::Source *source)
{
    string refs = pumpRefs(source);

    if(refs.size() != XREF_SIZE) throw InvalidRefsException();
    if((refs[0] < XREF_VERSION)) throw VersionException();
    if((refs[1] != XREF_MODEL)) throw ModelException();
    if(!(refs[5] == XREF_DECFNAME || refs[5] == XREF_NOTDECFNAME)) throw DecFnameRefsException();
    if(!(refs[6] == XREF_PK_ON || refs[6] == XREF_PK_OFF)) throw PkRefsException();

    return refs;
}
string AbstractCipher::checkRefs(const std::string& path)
{
    FileSource fsource(path.data(), false);
    return checkRefs(&fsource);
}

string AbstractCipher::stringRefs(AbstractKeygen* keygen)
{
    auto v_xrefs = vector_xrefs(keygen);
    string xrefs;
    xrefs.resize(v_xrefs.size());
    int count = 0;

    for(CryptoPP::byte data : v_xrefs) xrefs[count++] = data;

    return xrefs;
}
int AbstractCipher::afterRefs(CryptoPP::Source *source)
{
    string sink;
    size_t size;
    int count = 0;
    source->Attach(new StringSink(sink));

    do { source->Pump(1); count++; size = sink.size() - 1; }
    while(
        sink[size] != '\n' &&
        sink[size] != '\0' &&
        sink[size] != '='
    );

    source->Detach();
    return count;
}



