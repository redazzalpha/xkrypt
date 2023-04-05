#include "kexcept.h"

UnsupportedEncoding::UnsupportedEncoding(const char* message)
{
    m_message = message;
}
const char*  UnsupportedEncoding::what() const noexcept
{
    return m_message;
}

UnsupportedKey::UnsupportedKey(const char* message)
{
    m_message = message;
}
const char*  UnsupportedKey::what() const noexcept
{
    return m_message;
}

UnsupportedData::UnsupportedData(const char* message)
{
    m_message = message;
}
const char*  UnsupportedData::what() const noexcept
{
    return m_message;
}

UnsupportedVersion::UnsupportedVersion(const char* message)
{
    m_message = message;
}
const char*  UnsupportedVersion::what() const noexcept
{
    return m_message;
}

UnsupportedModel::UnsupportedModel(const char* message)
{
    m_message = message;
}
const char*  UnsupportedModel::what() const noexcept
{
    return m_message;
}
