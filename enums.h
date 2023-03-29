#ifndef ENUMS_H
#define ENUMS_H

enum Page {
    generate,
    encrypt,
    decrypt,
};
enum Key {
    KEYLENGTH_DEFAULT = 16,
    KEYLENGTH_32= 32,
    KEYLENGTH_64 = 64,
    KEYLENGTH_128 = 128,
    KEYLENGTH_256 = 256,
    KEYLENGTH_512 = 512,
    KEYLENGTH_1024 = 1024,
    KEYLENGTH_2048 = 2048,
};

#endif // ENUMS_H
