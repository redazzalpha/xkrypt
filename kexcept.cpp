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
