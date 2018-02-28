#include <xautocode/Generator/HeaderFile.h>
#include <cstring>
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
    _name_space[0] = 0;
    bool next_line = DoReadLine();
    while (next_line)
    {
        if (strstr(_buffer, "namespace"))
        {
            _head = Trim(_head);
            size_t len = strlen(_head);
            memcpy(_name_space, _head, len);
            _name_space[len] = 0;
            ParseNamespaceEnd();
            break;
        }
        next_line = DoReadLine();
    }
    return _name_space;
}

void HeaderFile::ParseNamespaceEnd()
{
    char* nse = _name_space_end;
    int _left_brace_count = 0;
    char* next = strchr(_head, '{');
    while (next)
    {
        _left_brace_count++;
        *nse = '}';
        ++nse;
        next = strchr(next + 1, '{');
    }
    *nse = 0;
}

char* HeaderFile::ParseClassName()
{
    _class_name[0] = 0;
    char* dest = nullptr;
    bool next = DoReadLine();
    while (next)
    {
        if (!!(dest = strstr(_head, "class")))
        {
            break;
        }
        else if (!!(dest = strstr(_head, "struct")))
        {
            break;
        }
        next = DoReadLine();
    }
    if (dest)
    {
        dest = TrimLeft(dest);
    }
    return _class_name;
}

bool HeaderFile::ReadLine()
{
}

bool HeaderFile::DoReadLine()
{
    if (feof(_file) || ferror(_file))
    {
        return false;
    }
    fgets(_buffer, sizeof(_buffer), _file);
    _line_length = strlen(_buffer);
    return true;
}

bool HeaderFile::IsFunction()
{
}

char* HeaderFile::Trim(char* str)
{
}

char* HeaderFile::TrimLeft(char* str)
{
}

char* HeaderFile::TrimRight(char* str)
{
}

char* HeaderFile::ParseReturnType()
{
}

char* HeaderFile::ParseFunction()
{
}
