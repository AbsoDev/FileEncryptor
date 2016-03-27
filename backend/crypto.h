#ifndef CRYPTO_H_
#define CRYPTO_H_

extern const int KEY_LENGTH;
int encrypt_file(const char*, const char*, const char*);
int decrypt_file(const char*, const char*, const char*);

#endif
