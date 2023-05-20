#include "cipheraes.h"
#include <QFileDialog>
#include <sstream>

using namespace std;

const std::string AbstractCipherAes::AlgName = "Symmetric - Aes";

// constructors
AbstractCipherAes::AbstractCipherAes() {}

// destructor
AbstractCipherAes::~AbstractCipherAes() {};

// virtual methods
std::string AbstractCipherAes::algName() const
{
    return AbstractCipherAes::AlgName;
}
Algorithms AbstractCipherAes::algId() const
{
    return Algorithms::AES;
}
