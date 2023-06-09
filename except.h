#ifndef EXCEPT_H
#define EXCEPT_H

#include <exception>

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
class InvalidRefsException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    InvalidRefsException(const char* message = "-- error: Invalid refs<br />file is corrupt or unknown");

    // methods
    virtual const char* what() const noexcept;
};
class AlgRefsException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    AlgRefsException(const char* message = "-- error: Invalid refs algorithm <br />file is corrupt or unknown");

    // methods
    virtual const char* what() const noexcept;
};
class ModeRefsException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    ModeRefsException(const char* message = "-- error: Invalid refs mode<br />file is corrupt or unknown");

    // methods
    virtual const char* what() const noexcept;
};
class EncodingRefsException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    EncodingRefsException(const char* message = "-- error: Invalid refs encoding<br />file is corrupt or unknown");

    // methods
    virtual const char* what() const noexcept;
};
class DecFnameRefsException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    DecFnameRefsException(const char* message = "-- error: Invalid refs decfname<br />file is corrupt or unknown");

    // methods
    virtual const char* what() const noexcept;
};
class PkRefsException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    PkRefsException(const char* message = "-- error: Invalid use password refs<br />file is corrupt or unknown");

    // methods
    virtual const char* what() const noexcept;
};
class SaltRefsException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    SaltRefsException(const char* message = "-- error: Invalid end refs check<br />file is corrupt or unknown");

    // methods
    virtual const char* what() const noexcept;
};
class AlgException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    AlgException(const char* message = "-- error: Bad algorithm data");

    // methods
    virtual const char* what() const noexcept;
};
class ModeException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    ModeException(const char* message = "-- error: Bad mode data");

    // methods
    virtual const char* what() const noexcept;
};
class EncodingException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    EncodingException(const char* message = "-- error: Bad encoding data");

    // methods
    virtual const char* what() const noexcept;
};
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
class CipherException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    CipherException(const char* message = "-- error: bad file(s)");

    // methods
    virtual const char* what() const noexcept;
};
class LogicException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    LogicException(const char* message = "-- error: Invalid logic between cipher and keygen");

    // methods
    virtual const char* what() const noexcept;
};
class PkStateException : public std::exception {
private:
    const char* m_message;

public:
    // constructors
    PkStateException(const char* message = "-- error: Invalid password key use");

    // methods
    virtual const char* what() const noexcept;
};

#endif // EXCEPT_H
