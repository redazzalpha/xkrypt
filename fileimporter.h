#ifndef FILEIMPORTER_H
#define FILEIMPORTER_H

#include <iostream>
#include <fstream>
#include <QStringList>

class FileImporter {
private:
    std::fstream* m_file = nullptr;
    std::string m_dir;
    std::string m_fname;
    std::string m_path;
    const std::string m_delim = "/";

public:

    // constructors
    FileImporter(const std::string& dir = "", const std::string& fname = "");

    // destructor
    ~FileImporter();

    // methods
    void setDir(const std::string& dir);
    void setFname(const std::string& fname);
    void setPath(const std::string& dir, const std::string& fname);
    void setPath(const std::string& path);
    void setPath();

    std::string getDir();
    std::string getFname();
    std::string getPath();
    std::fstream* getFile();
    size_t getFSize();

    std::fstream* importFile();
    std::fstream* importFile(const std::string& dir, const std::string& fname);
    std::fstream* importFile(const std::string& path);
    std::vector<std::fstream> importFiles();

    std::fstream* openRead(const std::string& path);
    std::fstream* openWriteTrunc(const std::string& path);
    std::fstream* openWriteApp(const std::string& path);

private:
    void setDirFname(const std::string& path);
    std::fstream* newFile(const std::ios::openmode mode);
    std::fstream* newFile(const std::string& path, const std::ios::openmode mode);

};

#endif // FILEIMPORTER_H
