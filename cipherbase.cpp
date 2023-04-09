#include "cipherbase.h"
#include <fstream>


// constructors
AbstractCipherBase::AbstractCipherBase(): m_fi(new FileImporter) {}

// destructor
AbstractCipherBase::~AbstractCipherBase()
{
    delete m_fi;
}
