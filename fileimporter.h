#ifndef FILEIMPORTER_H
#define FILEIMPORTER_H

#include <iostream>
#include <fstream>

class FileImporter {
private:
    std::fstream* m_file = nullptr;
    std::string m_dir;
    std::string m_fname;
    const std::string m_delim = "/";

public:

    // constructors
    FileImporter(const std::string& dir = "", const std::string& fname = "");

    // destructor
    ~FileImporter();

    // methods
    void setDir(const std::string& dir);
    void setFname(const std::string& fname);
    std::string getDir();
    std::string getFname();
    size_t getFSize();
    std::fstream* getFile();

    std::fstream* importFile();
    std::fstream* openRead();
    std::fstream* openWriteTrunc();
    std::fstream* openWriteApp();

};

#endif // FILEIMPORTER_H
