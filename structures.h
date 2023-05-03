#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>

struct DirFname {
    std::string m_dir;
    std::string m_fname;
    std::string m_path;

    // constructors
    DirFname();
    DirFname(const std::string& dir, const std::string& fname);
};

#endif // STRUCTURES_H
