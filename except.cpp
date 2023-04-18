#include "except.h"

/*--------------------------------------------------------*/

EncodingException::EncodingException(const char* message)
{
    m_message = message;
}
const char*  EncodingException::what() const noexcept
{
    return m_message;
}

BadKeyException::BadKeyException(const char* message)
{
    m_message = message;
}
const char*  BadKeyException::what() const noexcept
{
    return m_message;
}

WrongDataException::WrongDataException(const char* message)
{
    m_message = message;
}
const char*  WrongDataException::what() const noexcept
{
    return m_message;
}

VersionException::VersionException(const char* message)
{
    m_message = message;
}
const char*  VersionException::what() const noexcept
{
    return m_message;
}

ModelException::ModelException(const char* message)
{
    m_message = message;
}
const char*  ModelException::what() const noexcept
{
    return m_message;
}

/*--------------------------------------------------------*/

UnreadyKeyException::UnreadyKeyException(const char* message)
{
    m_message = message;
}
const char*  UnreadyKeyException::what() const noexcept
{
    return m_message;
}
EmptyTextException::EmptyTextException(const char* message)
{
    m_message = message;
}
const char*  EmptyTextException::what() const noexcept
{
    return m_message;
}
BadCipherException::BadCipherException(const char* message)
{
    m_message = message;
}
const char*  BadCipherException::what() const noexcept
{
    return m_message;
}
FileSelectedException::FileSelectedException(const char* message)
{
    m_message = message;
}
const char*  FileSelectedException::what() const noexcept
{
    return m_message;
}
CipherException::CipherException(const char* message)
{
    m_message = message;
}
const char*  CipherException::what() const noexcept
{
    return m_message;
}
