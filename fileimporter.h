#ifndef FILEIMPORTER_H
#define FILEIMPORTER_H

#include <iostream>
#include <fstream>
#include <QStringList>
#include <QWidget>

class FileImporter {
private:
    std::fstream* m_file = new std::fstream;
    std::vector<std::fstream> m_files;
    std::vector<std::string> m_filePaths;
    const std::string m_delim = "/";
    std::string m_dir;
    std::string m_fname;
    std::string m_path;

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

    std::string getDir() const;
    std::string getFname() const;
    std::string getPath() const;
    std::fstream* getFile() const;
    const std::vector<std::fstream>& getFiles();
    const std::vector<std::string>& getFilePaths();
    size_t getFSize() const;

    std::fstream* importFile(
        QWidget* parent = nullptr,
        const std::string& caption = "Import file",
        const std::string& dir = "",
        const std::string& filter = "All Files (*)"
    );
    std::fstream* importFile(const std::string& dir, const std::string& fname);
    std::fstream* importFile(const std::string& path);
    const std::vector<std::fstream>& importFiles(
        QWidget* parent = nullptr,
        const std::string& caption = "Import file",
        const std::string& dir = "",
        const std::string& filter = "All Files (*)"
    );

    std::fstream* openRead(const std::string& path);
    std::fstream* openWriteTrunc(const std::string& path);
    std::fstream* openWriteApp(const std::string& path);

    void clear();

private:
    void setDirFname(const std::string& path);
    std::fstream* newFile(const std::ios::openmode mode);
    std::fstream* newFile(const std::string& path, const std::ios::openmode mode);
};

#endif // FILEIMPORTER_H
