#include <iostream>
#include <string>

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

static const std::string INFILE_ARG = "-i";
static const std::string OUTFILE_ARG = "-o";
static const std::string KEYFILE_ARG = "-k";

int main(int argc, char* argv[])
{
    ReadState state = ReadState::Normal;
    
    for (int i = 0; i < argc; i++)
    {
        switch (state)
        {
        case ReadState::Normal:
            if (argv[i] == INFILE_ARG)
            {
            }
            else if (argv[i] == OUTFILE_ARG)
            {
            }
            else if (argv[i] == KEYFILE_ARG)
            {
            }
            else 
            break;
        case ReadState::InFile:
            // check if infile exists
            break;
        case ReadState::OutFile:
            // check if outfile exists
            break;
        case ReadState::KeyFile:
            // check if keyfile exists
            break;
        }
    }
    
    return RETURN_CODE_OK;
}