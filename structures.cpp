#include "structures.h"
#include "defines.h"

using namespace std;

// constructors
DirFname::DirFname() {}
DirFname::DirFname(const string& dir, const string& fname) {
    m_dir = dir;
    m_fname = fname;
    m_path = m_dir + DELIMITOR + m_fname;
}
