#include <xautocode/Generator/HeaderFile.h>
#include <cstring>
#include <regex>
#include <string>
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
    name_space = _name_space;
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
    if (!next_line)
    {
        _file = freopen(NULL, "r", _file);
        if (!_file)
        {
            throw FileException("\treopen", "open");
        }
    }
    return _name_space;
}

void HeaderFile::ParseNamespaceEnd()
{
    name_space_end = _name_space_end;
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

void HeaderFile::RemoveRight()
{
    int len = strlen(_name_space);
    if (len > 0)
    {
        --len;
    }
    char* tail = _name_space + len;
    for (; (tail > _name_space) && ((*tail == '\n' || *tail == '\r')); --tail)
    {
        *tail = 0;
    }
}

char* HeaderFile::ParseClassName()
{
    _class_name[0] = 0;
    class_name = _class_name;
    char* dest = nullptr;
    bool next = DoReadLine();
    std::cmatch m;
    std::regex r("(class|struct)\\s+\\S+\\s*;\\s*\\n");
    while (next)
    {
        if (!std::regex_match(_head, r))
        {
	        if (!!(dest = strstr(_head, "class")))
	        {
	            break;
	        }
	        else if (!!(dest = strstr(_head, "struct")))
	        {
	            break;
	        }
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
            ParseFunctionType();
            ParseReturnType();
            ParseFunction();
            break;
        }
    }
    return ret;
}

bool HeaderFile::DoReadLine()
{
    _buffer[0] = 0;
    _head = _buffer;
    if (feof(_file) || ferror(_file))
    {
        return false;
    }
    fgets(_buffer, sizeof(_buffer), _file);
    _line_length = strlen(_buffer);
    RemoveRight();
    return true;
}

bool HeaderFile::IsFunction()
{
    bool ret = false;
    if (!_head || (_head[0] == '/'))
    {
        ret = false;
    }
    else if (_head && strchr(_head, '(') && strchr(_head, ')') && !strstr(_head, "typedef") && !strstr(_head, "using"))
    {
        ret = true;
    }
    return ret;
}

char* HeaderFile::ParseFunctionType()
{
    _function_type = HeaderFile::ft_none;
    char* cur = _head;
    if (!cur || strlen(cur) == 0)
    {
        return nullptr;
    }

    if (cur[0] == '~')
    {
        _function_type = HeaderFile::ft_deconstructor;
        return _head;
    }
    if (cur && class_name && strstr(cur, class_name) == cur)
    {
        cur += strlen(class_name);
        cur = TrimLeft(cur);
        if (cur && (strlen(cur) != 0) && (cur[0] == '('))
        {
            _function_type = HeaderFile::ft_constructor;
        }
        return _head;
    }
    _function_type = HeaderFile::ft_normal;
    return _head;
}

char* HeaderFile::Trim(char* str)
{
    str = TrimLeft(str);
    str = TrimRight(str);
    return str;
}

char* HeaderFile::TrimLeft(char* str)
{
    bool next = true;
    char* tail = str + strlen(str);
    while ((str < tail) && next)
    {
        if ((*str == ' ') || (*str == '\t') || (*str == '\r') || (*str == '\n'))
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
    if (!str || !strlen(str))
    {
        return str;
    }
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

char* HeaderFile::MoveToNextWord(char* str)
{
    bool next = true;
    char* tail = str + strlen(str);
    while ((str < tail) && next)
    {
        if ((*str == ' ') || (*str == '\t') || (*str == '\n'))
        {
            next = false;
            *str = 0;
        }
        ++str;
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

namespace
{
    std::string empty_string;
}

const char* HeaderFile::ParseReturnType()
{
    switch (_function_type)
    {
        case ft_none:
            return_type = nullptr;
            break;
        case ft_constructor:
        case ft_deconstructor:
            return_type = empty_string.c_str();
            break;
        case ft_normal:
            return_type = _head;
            break;
    }
    return return_type;
}

const char* HeaderFile::ParseFunction()
{
    switch (_function_type)
    {
    case ft_none:
        function = nullptr;
        break;
    case ft_constructor:
    case ft_deconstructor:
        function = _head;
        break;
    case ft_normal:
        function = MoveToNextWord(_head);
        break;
    }
    _head = const_cast<char*>(function);
    if (_head)
    {
        _head = strrchr(_head, ';');
    }
    if (_head)
    {
        *_head = 0;
    }
    return function;
}
