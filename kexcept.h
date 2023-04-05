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
    UnsupportedKey(const char* message = "-- error: Unsupported key<br /> key too heavy");

    // methods
    virtual const char* what() const noexcept;
};
class UnsupportedData : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    UnsupportedData(const char* message = "-- error: Unsupported data<br />file is corrupt or unknown");

    // methods
    virtual const char* what() const noexcept;
};
class UnsupportedVersion : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    UnsupportedVersion(const char* message = "-- error: Unsupported version<br />file is under version or unknown");

    // methods
    virtual const char* what() const noexcept;
};
class UnsupportedModel : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    UnsupportedModel(const char* message = "-- error: Unsupported model<br />file is corrupt or unknown");

    // methods
    virtual const char* what() const noexcept;
};

#endif // KEXCEPT_H
