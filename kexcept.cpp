#include "kexcept.h"

// constructors
UnsupportedEncoding::UnsupportedEncoding(const char* message) {
    m_message = message;
}

// virtual methods
const char*  UnsupportedEncoding::what() const noexcept {
    return m_message;
}
