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
        if (dest[0] == 'c')
        {
            dest += 5;
        }
        else if (dest[0] == 's')
        {
            dest += 6;
        }
        dest = TrimLeft(dest);
        char* tail = dest;
        while (*tail != ' ' && *tail != '\t' && *tail != '{' && *tail != '\r' && *tail != '\n')
        {
            ++tail;
        }
        size_t len = 0;
        if (tail > dest)
        {
            len = tail - dest;
        }
        memcpy(_class_name, dest, len);
        _class_name[len] = 0;
    }
    return _class_name;
}

bool HeaderFile::ReadLine()
{
    bool ret = false;
    while (DoReadLine())
    {
        _head = Trim(_head);
        if (IsFunction())
        {
            ret = true;
            ClearRedundant();
            ParseReturnType();
            ParseFunction();
            break;
        }
    }
    return ret;
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
    bool ret = false;
    if (strchr(_head, '(') && strchr(_head, ')') && !strstr(_head, "typedef") && !strstr(_head, "using"))
    {
        ret = true;
    }
    return ret;
}

char* HeaderFile::Trim(char* str)
{
    str = TrimLeft(str);
    str = TrimRight(str);
    return str;
}

char* HeaderFile::TrimLeft(char* str)
{
    char c = 0;
    bool next = true;
    char* tail = str + strlen(str);
    while ((str < tail) && next)
    {
        c = *tail;
        if ((c == ' ') || (c == '\t'))
        {
            ++str;
        }
        else
        {
            next = false;
        }
    }
    if (str >= tail)
    {
        str = nullptr;
    }
    return str;
}

char* HeaderFile::TrimRight(char* str)
{
    char c = 0;
    bool next = true;
    char* tail = str + strlen(str) - 1;
    while ((str <= tail) && next)
    {
        c = *tail;
        if ((c == ' ') || (c == '\t') || (c == '\r') || (c == '\n'))
        {
            --tail;
        }
        else
        {
            next = false;
        }
    }
    if (str >= tail)
    {
        str = nullptr;
    }
    return str;
}

char* HeaderFile::ClearRedundant()
{
    char* dest = strstr(_head, "virtual");
    if (dest == _head)
    {
        _head += 7;
    }
    dest = strstr(_head, "static");
    if (dest == _head)
    {
        _head += 6;
    }
    _head = TrimLeft(_head);
    return _head;
}

char* HeaderFile::ParseReturnType()
{
    //构造函数、析构函数、普通函数
    char* cur = _head;
    char* tail = _head + strlen(_head);
    while (cur < tail)
    {
        if ((*cur != ' ') && (*cur != '\t'))
        {
            ++cur;
        }
        else
        {
            return_type = _head;
            *cur = 0;
            break;
        }
    }
    return return_type;
}

char* HeaderFile::ParseFunction()
{
}
