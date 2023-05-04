#include "cipherbase.h"
#include "defines.h"
#include <fstream>

using namespace std;

// constructors
AbstractCipherBase::AbstractCipherBase(){}

// destructor
AbstractCipherBase::~AbstractCipherBase(){}

void AbstractCipherBase::encFname(const bool encFname)
{
    m_encFname = encFname;
}

void AbstractCipherBase::decFname(const bool decFname)
{
    m_decFname = decFname;
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
DirFname AbstractCipherBase::extractFname(const std::string& path) const {
    int pos = path.find_last_of(DELIMITOR);
    string dir = path.substr(0, pos);
    string fname = path.substr(pos+1, path.size() - pos);
    return DirFname(dir, fname);
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

