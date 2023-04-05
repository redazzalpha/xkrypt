#include "aesgcm.h"

using namespace CryptoPP;
using namespace std;

const QString AesGCM::ModeName = "GCM";

// constructors
AesGCM::AesGCM(){}

// destructor
AesGCM::~AesGCM(){};

// virtual methods
QString AesGCM::getModeName() const
{
    return AesGCM::AlgName;
}

string AesGCM::encrypt(const KeyGen& keygen, const string& plain)
{
    std::cout << "cipher Aes gcm encrypt" << std::endl;
}
string AesGCM::decrypt(const KeyGen& keygen, const string& cipher)
{
    std::cout << "cipher Aes gcm decrypt" << std::endl;
}

