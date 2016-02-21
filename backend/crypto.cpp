#include "crypto.h"

#include <iostream>
#include <iomanip>

#include "modes.h"
#include "aes.h"
#include "filters.h"


void FileReader::read_bytes(char const* filename)
{
    FILE *fileptr;
    fileptr = fopen(filename, "rb");
    fseek(fileptr, 0, SEEK_END);
    len = ftell(fileptr);
    rewind(fileptr);
    bytes = (char *)malloc((len+1)*sizeof(char));
    fread(bytes, len, 1, fileptr);
    fclose(fileptr);
}


int AES::nice(char const* filename)
{
    FileReader fr = FileReader();
    fr.read_bytes(filename);

    byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ], iv[ CryptoPP::AES::BLOCKSIZE ];
    memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
    memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

    std::string ciphertext;

    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );
    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( ciphertext ) );
    stfEncryptor.Put( reinterpret_cast<const unsigned char*>( fr.bytes ), fr.len+1 );
    stfEncryptor.MessageEnd();

    std::cout << "Cipher Text (" << ciphertext.size() << " bytes)" << std::endl;
    for( int i = 0; i < ciphertext.size(); i++ ) {

        std::cout << "0x" << std::hex << (0xFF & static_cast<byte>(ciphertext[i])) << " ";
    }
    std::cout << std::hex << std::endl << std::endl;
    return 0;
}
