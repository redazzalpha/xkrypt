#ifndef KEXCEPT_H
#define KEXCEPT_H

#include <exception>

class UnsupportedEncoding : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    UnsupportedEncoding(const char* message = "-- error: Unsupported encoding --");

    // methods
    virtual const char* what() const noexcept;
};

#endif // KEXCEPT_H
