#include <iostream>
#include <string>
#include <cstring>
#include "crypto.h"

enum RETURN_CODE
{
    RETURN_CODE_OK = 0,
    RETURN_CODE_INPUT_FILE_ERROR = 1,
    RETURN_CODE_OUTPUT_FILE_ERROR = 2,
    RETURN_CODE_KEY_FILE_ERROR = 3,
    RETURN_CODE_WRONG_ARGUMENT = 4,
    RETURN_CODE_ENCRYPTION_ERROR = 5,
    RETURN_CODE_DECRYPTION_ERROR = 6,
};

enum class ReadState
{
    Normal,
    InFile,
    OutFile,
    KeyFile,
};

static const char* INFILE_ARG = "-i";
static const char* OUTFILE_ARG = "-o";
static const char* KEYFILE_ARG = "-k";
static const char* ENCRYPT_ARG = "-e";
static const char* DECRYPT_ARG = "-d";

static bool FileExists(const char* fileName)
{
    if (FILE *file = fopen(fileName, "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char** argv)
{
    ReadState state = ReadState::Normal;
    bool has_in_file = false;
    bool has_out_file = false;
    bool has_key_file = false;
    bool encrypt = false, decrypt = false;
    char* in_file;
    char* out_file;
    char* key_file;
    std::string report_message;
    int rc = RETURN_CODE_OK;

    for (int i = 1; i < argc && rc == RETURN_CODE_OK; i++)
    {
        switch (state)
        {
        case ReadState::Normal:
            if (strcmp(INFILE_ARG, argv[i]) == 0)
            {
                state = ReadState::InFile;
            }
            else if (strcmp(OUTFILE_ARG, argv[i]) == 0)
            {
                state = ReadState::OutFile;
            }
            else if (strcmp(KEYFILE_ARG, argv[i]) == 0)
            {
                state = ReadState::KeyFile;
            }
            else if (strcmp(ENCRYPT_ARG, argv[i]) == 0)
            {
                encrypt = true;
            }
            else if (strcmp(DECRYPT_ARG, argv[i]) == 0)
            {
                decrypt = true;
            }
            else
            {
                report_message = "Unknown argument: ";
                report_message.append(argv[i]);
                rc = RETURN_CODE_WRONG_ARGUMENT;
            }
            break;
        case ReadState::InFile:
            if (FileExists(argv[i]) == false)
            {
                report_message = "Input file does not exist ";
                report_message.append(argv[i]);
                rc = RETURN_CODE_INPUT_FILE_ERROR;
            }
            else
            {
                has_in_file = true;
                in_file = argv[i];
            }
            state = ReadState::Normal;
            break;
        case ReadState::OutFile:
            if (FileExists(argv[i]))
            {
                rc = RETURN_CODE_OUTPUT_FILE_ERROR;
                report_message =  "Output file already exists";
                report_message.append(argv[i]);
            }
            else
            {
                has_out_file = true;
                out_file = argv[i];
            }
            state = ReadState::Normal;
            break;
        case ReadState::KeyFile:
            if (FileExists(argv[i]) == false)
            {
                report_message = "Key File missing: ";
                report_message.append(argv[i]);
                rc = RETURN_CODE_KEY_FILE_ERROR;
            }
            else
            {
                has_key_file = true;
                key_file = argv[i];
            }
            state = ReadState::Normal;
            break;
        }
    }

    if (rc == RETURN_CODE_OK)
    {
        if (has_in_file == false)
        {
            report_message = "InFile parameter missing";
            rc = RETURN_CODE_WRONG_ARGUMENT;
        }
        else if (has_out_file == false)
        {
            report_message = "OutFile parameter missing";
            rc = RETURN_CODE_WRONG_ARGUMENT;
        }
        else if (has_key_file == false)
        {
            report_message = "KeyFile parameter missing";
            rc = RETURN_CODE_WRONG_ARGUMENT;
        }
        else if (!encrypt and !decrypt)
        {
            report_message = "Method missing (encrypt or decrypt)";
            rc = RETURN_CODE_WRONG_ARGUMENT;
        }
        else if (encrypt and decrypt)
        {
            report_message = "Both methods present";
            rc = RETURN_CODE_WRONG_ARGUMENT;
        }
    }

    if (rc == RETURN_CODE_OK)
    {
        if (encrypt)
        {
            int response = encrypt_file(in_file, out_file, key_file);
            std::cout << "response: " << response << std::endl;
        }
        else
        {
            int response = decrypt_file(in_file, out_file, key_file);
            std::cout << "response: " << response << std::endl;
        }
    }
    else
    {
        std::cout << report_message << std::endl;
    }

    return rc;
}
