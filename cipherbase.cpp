#include "cipherbase.h"
#include <fstream>

using namespace std;

// constructors
AbstractCipherBase::AbstractCipherBase(){}

// destructor
AbstractCipherBase::~AbstractCipherBase(){}

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
        std::to_string(succeed) + "file(s) encrypted<br />"
        "Using " +
        getAlgName() + " - " + getModeName() +
        " mode<br />";
}
string AbstractCipherBase::successDecMsg(const int succeed)
{
    return  "Decryption successfull!<br />" +
        std::to_string(succeed) + "file(s) decrypted<br />" +
        "Using " +
        getAlgName() + " - " + getModeName() +
        " mode<br />";
}

