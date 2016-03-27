#ifndef CRYPTO_H_
#define CRYPTO_H_

#include <string>

std::string file_hash(const char*);
int encrypt_file(const char*, const char*, const char*);
int decrypt_file(const char*, const char*, const char*);

#endif
