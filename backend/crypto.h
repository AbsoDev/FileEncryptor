#ifndef CRYPTO_H_
#define CRYPTO_H_

#include <string>

int password_to_key(const char*, std::string);
int encrypt_file(const char*, const char*, const char*);
int decrypt_file(const char*, const char*, const char*);

#endif
