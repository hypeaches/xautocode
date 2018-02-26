#include <xautocode/Generator/SourceFile.h>
#include <cstring>
#include <stdexcept>
#include <xautocode/Generator/FileException.h>

void SourceFile::Open(const char* file_name)
{
    _left_brace_count = 0;
    _file = fopen(file_name, "wa");
    if (!_file)
    {
        throw FileException(file_name, "open");
    }
}

int SourceFile::Write(const char* return_type, const char* class_name, const char* function)
{
    int len = fprintf(_file, "%s %s::%s\n{\n}\n\n", return_type, class_name, function);
    return len;
}

int SourceFile::WriteNamespace(const char* name_space)
{
    int len = strlen(name_space);
    if (len)
    {
        len = fprintf(_file, "%s\n\n", name_space);
        const char* left_brace = strchr(name_space, '{');
        while (left_brace)
        {
            _left_brace_count++;
            ++left_brace;
            left_brace = strchr(left_brace, '{');
        }
    }
    return len;
}

void SourceFile::Close()
{
    for (int i = 0; i < _left_brace_count; ++i)
    {
        fprintf(_file, "}");
    }
    fclose(_file);
}
