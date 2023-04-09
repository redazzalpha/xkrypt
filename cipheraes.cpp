#include "cipheraes.h"
#include <QFileDialog>
#include <sstream>

using namespace std;

const QString AbstractCipherAes::AlgName = "Symmectric - Aes";

// constructors
AbstractCipherAes::AbstractCipherAes() {}

// destructor
AbstractCipherAes::~AbstractCipherAes() {};

// virtual methods
QString AbstractCipherAes::getAlgName() const
{
    return AbstractCipherAes::AlgName;
}
