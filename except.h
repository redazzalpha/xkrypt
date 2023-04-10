#ifndef EXCEPT_H
#define EXCEPT_H

#include <exception>

/*--------------------------------------------------------*/

class EncodingException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    EncodingException(const char* message = "-- error: Bad encoding data");

    // methods
    virtual const char* what() const noexcept;
};
class BadKeyException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    BadKeyException(const char* message = "-- error: Unsupported key");

    // methods
    virtual const char* what() const noexcept;
};
class WrongDataException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    WrongDataException(const char* message = "-- error: Wrong data<br />file is corrupt or unknown");

    // methods
    virtual const char* what() const noexcept;
};
class VersionException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    VersionException(const char* message = "-- error: Unsupported version<br />file is under version or unknown");

    // methods
    virtual const char* what() const noexcept;
};
class ModelException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    ModelException(const char* message = "-- error: Unsupported model<br />file is corrupt or unknown");

    // methods
    virtual const char* what() const noexcept;
};

/*--------------------------------------------------------*/

class UnreadyKeyException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    UnreadyKeyException(const char* message = "-- error: key is not ready or not imported");

    // methods
    virtual const char* what() const noexcept;
};
class EmptyTextException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    EmptyTextException(const char* message = "-- error: Text is empty");

    // methods
    virtual const char* what() const noexcept;
};
class BadCipherException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    BadCipherException(const char* message = "-- error: Bad cipher");

    // methods
    virtual const char* what() const noexcept;
};
class FileSelectedException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    FileSelectedException(const char* message = "-- error: wrong file(s) selected");

    // methods
    virtual const char* what() const noexcept;
};

#endif // EXCEPT_H
