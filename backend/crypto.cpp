#include "crypto.h"
#include "modes.h"
#include "aes.h"
#include "files.h"
#include "osrng.h"
#include <ios>
#include <fstream>


// 256bit
static const int KEY_LENGTH = 32;


// transforms content stored in file to 32byte hash through SHA256
std::string file_hash(char const* filename)
{
    std::string hsh;
    CryptoPP::SHA256 sha256;
    CryptoPP::FileSource fs(filename, true,
        new CryptoPP::HashFilter(sha256,
            new CryptoPP::StringSink(hsh)
        )
    );
    return hsh;
}

int encrypt_file(char const* in_file, char const* out_file, char const* pass_file)
{
    // open output
    std::ofstream fout(out_file, std::ios::binary);
    if(!fout.is_open()) return -1;

    // initialize random iv
    byte iv[CryptoPP::AES::BLOCKSIZE];
    CryptoPP::AutoSeededRandomPool rnd;
    rnd.GenerateBlock(iv, CryptoPP::AES::BLOCKSIZE);

    // make key from password file as 32byte hash (sha256)
    std::string key = file_hash(pass_file);

    // write iv
    for(int i = 0; i < CryptoPP::AES::BLOCKSIZE; i++) fout << iv[i];

    // perform encryption and get cyphertext
    std::string cypher;
    CryptoPP::AES::Encryption aesEncryption((byte*)key.data(), KEY_LENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
    CryptoPP::FileSource file_source(in_file, true,
        new CryptoPP::StreamTransformationFilter(cbcEncryption,
            new CryptoPP::StringSink(cypher)
        )
    );

    // write cypher text to output file
    for(int i = 0; i < cypher.size(); i++) fout << cypher[i];

    // finish
    fout.close();
    return 0;
}

int decrypt_file(char const* in_file, char const* out_file, char const* pass_file)
{
    // open input and output
    std::ifstream fin(in_file, std::ios::binary);
    std::ofstream fout(out_file, std::ios::binary);
    if(!fin.is_open() or !fout.is_open()) return -1;

    // read iv
    byte iv[CryptoPP::AES::BLOCKSIZE];
    for(int i = 0; i < CryptoPP::AES::BLOCKSIZE; i++) fin >> iv[i];

    // make key from password file as 32byte hash (sha256)
    std::string key = file_hash(pass_file);

    // perform decryption and write decrypted text
    std::string decypher;
    CryptoPP::AES::Decryption aesDecryption((byte*)key.data(), KEY_LENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);
    CryptoPP::FileSource file_source(fin, true,
        new CryptoPP::StreamTransformationFilter(cbcDecryption,
            new CryptoPP::StringSink(decypher)
        )
    );

    // write decypher text to output file
    for(int i = 0; i < decypher.size(); i++) fout << decypher[i];

    // finish
    fin.close();
    fout.close();
    return 0;
}
