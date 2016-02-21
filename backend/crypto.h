#ifndef CRYPTO_H_
#define CRYPTO_H_

#include "files.h"

void read_bytes(const char*, byte*, int&);

int encrypt_file(const char*, const char*, const char*);

#endif
