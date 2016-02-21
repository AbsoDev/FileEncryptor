#ifndef CRYPTO_H_
#define CRYPTO_H_

class FileReader
{
    public:
        int len;
        char* bytes;

        void read_bytes(const char*);
};

class AES
{
    public:
        int nice(const char*);
};

#endif
