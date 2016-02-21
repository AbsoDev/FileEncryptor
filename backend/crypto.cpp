#include "crypto.h"
#include "modes.h"
#include "aes.h"
#include "files.h"


int encrypt_file(char const* in_file, char const* out_file, char const* key_file)
{
    byte iv[CryptoPP::AES::BLOCKSIZE];
    memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);

    std::string key;
    CryptoPP::FileSource fs(key_file, new CryptoPP::StringSink(key));

    CryptoPP::AES::Encryption aesEncryption((byte*)key.data(), CryptoPP::AES::DEFAULT_KEYLENGTH);
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
    byte iv[CryptoPP::AES::BLOCKSIZE];
    memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);

    std::string key;
    CryptoPP::FileSource fs(key_file, new CryptoPP::StringSink(key));

    CryptoPP::AES::Decryption aesDecryption((byte*)key.data(), CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);
    CryptoPP::FileSource file_source(in_file, true,
        new CryptoPP::StreamTransformationFilter(cbcDecryption,
            new CryptoPP::FileSink(out_file)
        )
    );

    return 0;
}
