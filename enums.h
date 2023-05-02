#ifndef ENUMS_H
#define ENUMS_H

#include "aes.h"

enum Page {
    generate,
    encrypt,
    decrypt,
};
enum class KeyLength {
    LENGTH_DEFAULT = 16,
    LENGTH_MIN = LENGTH_DEFAULT,
    LENGTH_32= 32,
    LENGTH_64 = 64,
    LENGTH_128 = 128,
    LENGTH_256 = 256,
    LENGTH_512 = 512,
    LENGTH_1024 = 1024,
    LENGTH_2048 = 2048,
    LENGTH_MAX = LENGTH_2048
};
enum class IvLength {
    LENGTH_DEFAULT = CryptoPP::AES::BLOCKSIZE,
};
enum Encoding {
    BASE64,
    HEX,
    NONE,
};
enum class EmitType {
    EMIT,
    NO_EMIT,
    CHECKED = NO_EMIT,
    UNCHECKED = EMIT,
};

#endif // ENUMS_H
