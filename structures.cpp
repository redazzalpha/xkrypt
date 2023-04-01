#include "structures.h"

using namespace CryptoPP;

KeyIv::KeyIv(const SecByteBlock& key, const SecByteBlock& iv): m_key(key), m_iv(iv) {}
