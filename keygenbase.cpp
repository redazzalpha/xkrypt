#include "keygenbase.h"

// constructors
AbstractKeygen::AbstractKeygen(size_t keysize): m_keysize(keysize) {}

// destructor
AbstractKeygen::~AbstractKeygen() {}

// methods
void AbstractKeygen::setKeysize(size_t keysize)
{
    m_keysize = keysize;
}
void AbstractKeygen::setEncoding(Encoding newEncoding)
{
    m_encoding = newEncoding;
}
size_t AbstractKeygen::keysize() const
{
    return m_keysize;
}
Encoding AbstractKeygen::encoding() const
{
    return m_encoding;
}
