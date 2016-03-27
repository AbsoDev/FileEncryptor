#include "crypto.h"
#include "modes.h"
#include "aes.h"
#include "files.h"
#include "osrng.h"
#include <ios>
#include <fstream>


// 256bit
static const int KEY_LENGTH = 32;


int encrypt_file(char const* in_file, char const* out_file, char const* key_file)
{
    // open output
    std::ofstream fout(out_file, std::ios::binary);
    if(!fout.is_open()) return -1;

    // initialize random iv
    byte iv[CryptoPP::AES::BLOCKSIZE];
    CryptoPP::AutoSeededRandomPool rnd;
    rnd.GenerateBlock(iv, CryptoPP::AES::BLOCKSIZE);

    // read key from keyfile
    std::string key;
    CryptoPP::FileSource fs(key_file, new CryptoPP::StringSink(key));

    // write iv
    for(int i = 0; i < CryptoPP::AES::BLOCKSIZE; i++) fout << iv[i];

    // perform encryption and write cyphertext
    CryptoPP::AES::Encryption aesEncryption((byte*)key.data(), KEY_LENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
    CryptoPP::FileSource file_source(in_file, true,
        new CryptoPP::StreamTransformationFilter(cbcEncryption,
            new CryptoPP::FileSink(fout)
        )
    );

    // finish
    fout.close();
    return 0;
}

int decrypt_file(char const* in_file, char const* out_file, char const* key_file)
{
    // open input
    std::ifstream fin(in_file, std::ios::binary);
    if(!fin.is_open()) return -1;

    // read iv
    byte iv[CryptoPP::AES::BLOCKSIZE];
    for(int i = 0; i < CryptoPP::AES::BLOCKSIZE; i++) fin >> iv[i];

    // read key from keyfile
    std::string key;
    CryptoPP::FileSource fs(key_file, new CryptoPP::StringSink(key));

    // perform decryption and write decrypted text
    CryptoPP::AES::Decryption aesDecryption((byte*)key.data(), KEY_LENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);
    CryptoPP::FileSource file_source(fin, true,
        new CryptoPP::StreamTransformationFilter(cbcDecryption,
            new CryptoPP::FileSink(out_file)
        )
    );

    // finish
    fin.close();
    return 0;
}
