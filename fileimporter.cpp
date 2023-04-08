#include "fileimporter.h"
#include <QFileDialog>
#include <vector>
#include <bits/stream_iterator.h>

using namespace std;

// constructors
FileImporter::FileImporter(const string& dir, const string& fname) : m_dir(dir), m_fname(fname)
{
    m_dir += !m_fname.empty()? m_delim : "" + m_fname;
}

// destructor
FileImporter::~FileImporter()
{
    if(m_file) delete m_file;
}

// methods
void FileImporter::setDir(const string& dir)
{
    m_dir = dir;
}
void FileImporter::setFname(const string& fname)
{
    m_fname = fname;
}
string FileImporter::getDir()
{
    return m_dir;
}
string FileImporter::getFname()
{
    return m_fname;
}
size_t FileImporter::getFSize()
{
    size_t fsize = 0;
    ifstream f(m_dir);
    if(f.good()) {
        std::vector<char> bytes((std::istream_iterator<char>(f)), std::istream_iterator<char>());
        fsize = bytes.size();
    }
    f.close();
    return fsize;
}
fstream* FileImporter::getFile()
{
    return m_file;
}

fstream* FileImporter::importFile()
{
    m_dir = QFileDialog::getOpenFileName(nullptr,"Import file", "", "All Files (*)").toStdString();
    int pos = m_dir.find_last_of(m_delim) + 1;
    m_fname = m_dir.substr(pos, m_dir.max_size() - pos);

    fstream* f = new fstream(m_dir, std::ios::in | std::ios::out | std::ios::binary);
    if(f->good()) {
//        if(m_file) delete m_file;
//        m_file = f;
    }
    else {
        delete f;
        f = nullptr;
    }
    return f;
}
fstream* FileImporter::openRead()
{
    if(!m_dir.empty() && !m_fname.empty()) {
        if(m_file) delete m_file;
        return m_file = new fstream(m_dir, std::ios::in | std::ios::binary);
    }
    return nullptr;
}
fstream* FileImporter::openWriteTrunc()
{
    if(m_file) delete m_file;
    return m_file = new fstream(m_dir, std::ios::out | std::ios::trunc | std::ios::binary);
}
fstream* FileImporter::openWriteApp()
{
    if(m_file) delete m_file;
    return m_file = new fstream(m_dir, std::ios::out | std::ios::app | std::ios::binary);
}

