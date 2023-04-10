#include "cipheraes.h"
#include <QFileDialog>
#include <sstream>

using namespace std;

const std::string AbstractCipherAes::AlgName = "Symmectric - Aes";

// constructors
AbstractCipherAes::AbstractCipherAes() {}

// destructor
AbstractCipherAes::~AbstractCipherAes() {};

// virtual methods
std::string AbstractCipherAes::getAlgName() const
{
    return AbstractCipherAes::AlgName;
}
