#ifndef ENUMS_H
#define ENUMS_H

#include "aes.h"

enum Algorithms {
    AES,
    RSA,
};

namespace Rsa {
enum class KeySize {
    LENGTH_1024 = 1024,
    LENGTH_2048 = 2048,
    LENGTH_3072 = 3072,
    LENGTH_4096 = 4096,
    LENGTH_5120 = 5120,
    LENGTH_6144 = 6144,
    LENGTH_DEFAULT = LENGTH_3072,
    LENGTH_MIN = LENGTH_1024,
    LENGTH_MAX = LENGTH_6144
};
}

namespace Aes {
enum class KeySize {
    LENGTH_16 = 16,
    LENGTH_32= 32,
    LENGTH_64 = 64,
    LENGTH_128 = 128,
    LENGTH_256 = 256,
    LENGTH_512 = 512,
    LENGTH_1024 = 1024,
    LENGTH_2048 = 2048,
    LENGTH_DEFAULT = LENGTH_16,
    LENGTH_MIN = LENGTH_16,
    LENGTH_MAX = LENGTH_2048
};
enum class IvSize {
    LENGTH_DEFAULT = CryptoPP::AES::BLOCKSIZE,
};
}
enum Mode {
    CBC = 0x01,
    CCM = 0x02,
    CFB = 0x03,
    CTR = 0x04,
    EAX = 0x05,
    ECB = 0x06,
    GCM = 0x07,
    OFB = 0x08,
    OEAP = 0x09,
    SSA = 0x0A,
};
enum Encoding {
    BASE64 = 0x01,
    HEX = 0x02,
    NONE = 0x03,
    BER = 0x04,
    DER = 0x05,
    PEM = 0x06,
};


enum Page {
    generate,
    encrypt,
    decrypt,
};

#endif // ENUMS_H
