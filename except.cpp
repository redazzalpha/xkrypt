#include "except.h"

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

InvalidRefsException::InvalidRefsException(const char* message)
{
    m_message = message;
}
const char*  InvalidRefsException::what() const noexcept
{
    return m_message;
}

AlgRefsException::AlgRefsException(const char* message)
{
    m_message = message;
}
const char*  AlgRefsException::what() const noexcept
{
    return m_message;
}

ModeRefsException::ModeRefsException(const char* message)
{
    m_message = message;
}
const char*  ModeRefsException::what() const noexcept
{
    return m_message;
}

EncodingRefsException::EncodingRefsException(const char* message)
{
    m_message = message;
}
const char*  EncodingRefsException::what() const noexcept
{
    return m_message;
}

AlgException::AlgException(const char* message)
{
    m_message = message;
}
const char*  AlgException::what() const noexcept
{
    return m_message;
}

ModeException::ModeException(const char* message)
{
    m_message = message;
}
const char*  ModeException::what() const noexcept
{
    return m_message;
}

EncodingException::EncodingException(const char* message)
{
    m_message = message;
}
const char*  EncodingException::what() const noexcept
{
    return m_message;
}

DecFnameRefsException::DecFnameRefsException(const char* message)
{
    m_message = message;
}
const char*  DecFnameRefsException::what() const noexcept
{
    return m_message;
}

PkRefsException::PkRefsException(const char* message)
{
    m_message = message;
}
const char*  PkRefsException::what() const noexcept
{
    return m_message;
}

SaltRefsException::SaltRefsException(const char* message)
{
    m_message = message;
}
const char*  SaltRefsException::what() const noexcept
{
    return m_message;
}

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

LogicException::LogicException(const char* message)
{
    m_message = message;
}
const char*  LogicException::what() const noexcept
{
    return m_message;
}

PkStateException::PkStateException(const char* message)
{
    m_message = message;
}
const char*  PkStateException::what() const noexcept
{
    return m_message;
}
