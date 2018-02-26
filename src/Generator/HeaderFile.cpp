#include <xautocode/Generator/HeaderFile.h>
#include <xautocode/Generator/FileException.h>

void HeaderFile::Open(const char* file_name)
{
    _file = fopen(file_name, "r");
    if (!_file)
    {
        throw FileException(file_name, "open");
    }
}

void HeaderFile::Close()
{
    fclose(_file);
}

char* HeaderFile::ParseNamespace()
{
}

char* HeaderFile::ParseClassName()
{
}

bool HeaderFile::ReadLine()
{
}

bool HeaderFile::DoReadLine()
{
}

bool HeaderFile::IsFunction()
{
}

void HeaderFile::Trim()
{
}

void HeaderFile::TrimLeft()
{
}

void HeaderFile::TrimRight()
{
}

char* HeaderFile::ParseReturnType()
{
}

char* HeaderFile::ParseFunction()
{
}
