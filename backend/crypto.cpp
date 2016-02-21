#include "crypto.h"

#include <iostream>
#include <iomanip>

#include "modes.h"
#include "aes.h"
#include "filters.h"
#include "files.h"


int encrypt_file(char const* in_file, char const* out_file, char const* key_file)
{
    int key_len=16;
    byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
    //read_bytes(key_file, key, key_len);
    memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);

    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
    CryptoPP::FileSource file_source(in_file, true,
        new CryptoPP::StreamTransformationFilter(cbcEncryption,
            new CryptoPP::FileSink(out_file)
        )
    );
    return 0;
}

int decrypt_file(char const* in_file, char const* out_file, char const* key_file)
{
    int key_len=16;
    byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
    //read_bytes(key_file, key, key_len);
    memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);

    CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);
    CryptoPP::FileSource file_source(in_file, true,
        new CryptoPP::StreamTransformationFilter(cbcDecryption,
            new CryptoPP::FileSink(out_file)
        )
    );

    return 0;
}
