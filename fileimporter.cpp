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
void FileImporter::setPath(const string& path)
{
    m_path = path;
    setDirFname(path);
}
void FileImporter::setPath(const string& dir, const string& fname)
{
    m_dir = dir;
    m_fname = fname;
    m_path = m_dir + m_delim + m_fname;
}
void FileImporter::setPath()
{
    m_path = m_dir + m_delim + m_fname;
}

string FileImporter::getDir() const
{
    return m_dir;
}
string FileImporter::getFname() const
{
    return m_fname;
}
string FileImporter::getPath() const
{
    return m_path;
}
fstream* FileImporter::getFile() const
{
    return m_file;
}
const std::vector<fstream>& FileImporter::getFiles()
{
    return m_files;
}
const std::vector<string>& FileImporter::getFilePaths()
{
    return m_filePaths;
}
size_t FileImporter::getFSize() const
{
    size_t fsize = 0;
    ifstream f(m_path);
    if(f.good()) {
        std::vector<char> bytes((std::istream_iterator<char>(f)), std::istream_iterator<char>());
        fsize = bytes.size();
    }
    f.close();
    return fsize;
}

fstream* FileImporter::importFile(QWidget* parent, const string& caption, const string& dir, const string& filter)
{
    setPath(QFileDialog::getOpenFileName(parent, QString::fromStdString(caption), QString::fromStdString(dir), QString::fromStdString(filter)).toStdString());
    return newFile(m_path, std::ios::in | std::ios::out | std::ios::binary);
}
fstream* FileImporter::importFile(const string& dir, const string& fname)
{
    setPath(dir, fname);
    fstream* f = new fstream(m_path, std::ios::in | std::ios::out | std::ios::binary);
    if(f->good()) {
        if(m_file) delete m_file;
        m_file = f;
    }
    else {
        delete f;
        f = nullptr;
    }
    return f;
}
fstream* FileImporter::importFile(const string& path)
{
    setPath(path);
    return newFile(std::ios::in | std::ios::out | std::ios::binary);
}
const vector<fstream>& FileImporter::importFiles(QWidget* parent, const string& caption, const string& dir, const string& filter)
{
    QStringList paths;
    QFileDialog dialog(parent, QString::QString::fromStdString(caption), QString::fromStdString(dir), QString::fromStdString(filter));
    dialog.setFileMode(QFileDialog::ExistingFiles);
    if (dialog.exec()) {
        clear();
        paths = dialog.selectedFiles();
    }
    foreach(QString path, paths) {
        m_files.push_back(fstream (path.toStdString(), ios::in | ios::out | ios::binary));
        m_filePaths.push_back(path.toStdString());
    }
    return m_files;
}

fstream* FileImporter::openRead(const string& path)
{
    setPath(path);
    return newFile(std::ios::in | std::ios::binary);
}
fstream* FileImporter::openWriteTrunc(const string& path)
{
    setPath(path);
    return newFile(std::ios::out | std::ios::trunc | std::ios::binary);
}
fstream* FileImporter::openWriteApp(const string& path)
{
    setPath(path);
    return newFile(std::ios::out | std::ios::app | std::ios::binary);
}

void FileImporter::clear()
{
    delete m_file;
    m_file = nullptr;
    m_files.clear();
    m_filePaths.clear();
    m_path = "";
    m_dir = "";
    m_fname = "";
}

// private methods
void FileImporter::setDirFname(const std::string& path)
{
    if(!path.empty()) {
        int pos = path.find_last_of(m_delim);
        m_dir = path.substr(0, pos);
        m_fname = path.substr(pos+1, m_dir.max_size() - pos);
    }
}
fstream* FileImporter::newFile(const ios::openmode mode)
{
    if(!m_path.empty()) {
        if(m_file) delete m_file;
        return m_file = new fstream(m_path, mode);
    }
    else return nullptr;
}
fstream* FileImporter::newFile(const string& path, const ios::openmode mode)
{
    setPath(path);
    if(!path.empty()) {
        if(m_file) delete m_file;
        return m_file = new fstream(m_path, mode);
    }
    else return nullptr;
}



