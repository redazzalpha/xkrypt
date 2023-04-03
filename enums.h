#ifndef ENUMS_H
#define ENUMS_H

enum Page {
    generate,
    encrypt,
    decrypt,
};
enum KeyLength {
    LENGTH_DEFAULT = 16,
    LENGTH_32= 32,
    LENGTH_64 = 64,
    LENGTH_128 = 128,
    LENGTH_256 = 256,
    LENGTH_512 = 512,
    LENGTH_1024 = 1024,
    LENGTH_2048 = 2048,
};
enum Encoding {
    BASE64,
    HEX,
    NONE,
};

#endif // ENUMS_H
