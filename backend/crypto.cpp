#include "crypto.h"

#include <iostream>
#include <iomanip>

#include "modes.h"
#include "aes.h"
#include "filters.h"
#include "files.h"


void read_bytes(char const* filename, char* bytes, int& len)
{
    FILE *fileptr;
    fileptr = fopen(filename, "rb");
    fseek(fileptr, 0, SEEK_END);
    len = ftell(fileptr);
    rewind(fileptr);
    bytes = (char*)malloc((len+1)*sizeof(char));
    fread(bytes, len, 1, fileptr);
    fclose(fileptr);
}


int AES::nice(char const* in_file, char const* out_file)
{
    char* bytes;
    int len;
    read_bytes(in_file, bytes, len);

    byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
    memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);

    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::FileSink(out_file));
    stfEncryptor.Put(reinterpret_cast<const unsigned char*>(bytes), len+1);
    stfEncryptor.MessageEnd();

    return 0;
}
