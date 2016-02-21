#include <iostream>
#include <string>
#include <cstring>

enum RETURN_CODE 
{
    RETURN_CODE_OK = 0,
    RETURN_CODE_INPUT_FILE_ERROR = 1,
    RETURN_CODE_OUTPUT_FILE_ERROR = 2,
    RETURN_CODE_KEY_FILE_ERROR = 3,
    RETURN_CODE_ENCRYPTION_ERROR = 4,
    RETURN_CODE_WRONG_ARGUMENT = 5,
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
            }
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
            }
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
            }
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
    }
    
    if (rc != RETURN_CODE_OK)
    {
        std::cout << report_message;
    }
    
    return rc;
}