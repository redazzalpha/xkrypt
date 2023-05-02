#include "cipherbase.h"
#include <fstream>

using namespace std;

// constructors
AbstractCipherBase::AbstractCipherBase(){}

// destructor
AbstractCipherBase::~AbstractCipherBase(){}

void AbstractCipherBase::encFname(const EmitType emitType)
{
    m_encFname = emitType;
}

void AbstractCipherBase::decFname(const EmitType emitType)
{
    m_decFname = emitType;
}

bool &AbstractCipherBase::run()
{
    return m_run;
}

// protected methods
void AbstractCipherBase::removeFile(const string &filePath) const
{
    remove(filePath.c_str());
}
DirFname AbstractCipherBase::extractFname(const std::string& path, const string& delim) const {
    int pos = path.find_last_of(delim);
    string dir = path.substr(0, pos);
    string fname = path.substr(pos+1, path.size() - pos);
    return DirFname(dir, fname, delim);
}
string AbstractCipherBase::successEncMsg(const int succeed)
{
    return  "Encryption successfull!<br />" +
        std::to_string(succeed) + " file(s) written<br />"
        "Using " +
        getAlgName() + " - " + getModeName() +
        " mode<br />";
}
string AbstractCipherBase::successDecMsg(const int succeed)
{
    return  "Decryption successfull!<br />" +
        std::to_string(succeed) + " file(s) written<br />" +
        "Using " +
        getAlgName() + " - " + getModeName() +
           " mode<br />";
}

void AbstractCipherBase::kill()
{
    m_run = false;
}

