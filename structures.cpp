#include "structures.h"

using namespace std;

// constructors
DirFname::DirFname() {}
DirFname::DirFname(const string& dir, const string& fname, const string& delim) {
    m_dir = dir;
    m_fname = fname;
    m_delim = delim;
    m_path = m_dir + m_delim + m_fname;
}
