#ifndef KEXCEPT_H
#define KEXCEPT_H

#include <exception>

class UnsupportedEncoding : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    UnsupportedEncoding(const char* message = "-- error: Unsupported encoding");

    // methods
    virtual const char* what() const noexcept;
};
class UnsupportedKey : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    UnsupportedKey(const char* message = "-- error: Unsupported key<br /> Must be at least 16 bytes");

    // methods
    virtual const char* what() const noexcept;
};

#endif // KEXCEPT_H
