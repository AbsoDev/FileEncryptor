#include "crypto.h"

#include <iostream>
#include <iomanip>

#include "modes.h"
#include "aes.h"
#include "filters.h"
#include "files.h"


void read_bytes(char const* filename, byte* bytes, int& len)
{
    FILE *fileptr;
    fileptr = fopen(filename, "rb");
    fseek(fileptr, 0, SEEK_END);
    len = ftell(fileptr);
    rewind(fileptr);
    bytes = (byte*)malloc((len+1)*sizeof(char));
    fread(bytes, len, 1, fileptr);
    fclose(fileptr);
}


int encrypt_file(char const* in_file, char const* out_file, char const* key_file)
{
    byte* bytes;
    int file_len;
    read_bytes(in_file, bytes, file_len);

    int key_len;
    byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
    read_bytes(key_file, key, key_len);
    //memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);

    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::FileSink(out_file));
    stfEncryptor.Put(bytes, file_len+1);
    stfEncryptor.MessageEnd();

    return 0;
}
