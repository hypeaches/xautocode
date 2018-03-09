#include <xautocode/Generator/SourceFile.h>
#include <cstring>
#include <stdexcept>
#include <xautocode/CommandLine.h>
#include <xautocode/Generator/FileException.h>
#include <boost/filesystem.hpp>

void SourceFile::Open(const char* file_name)
{
    CreateParentDirectory(file_name);
    _left_brace_count = 0;
    _file = fopen(file_name, "wa");
    if (!_file)
    {
        throw FileException(file_name, "open");
    }
}

int SourceFile::Write(const char* str)
{
    int len = fprintf(_file, "%s\n\n", str);
    return len;
}

int SourceFile::Write(const char* return_type, const char* class_name, const char* function)
{
    int len = 0;
    if (CommandLine::left_brace_pos)
    {
        fprintf(_file, "%s %s::%s\n{\n}\n\n", return_type, class_name, function);
    }
    else
    {
        fprintf(_file, "%s %s::%s {\n}\n\n", return_type, class_name, function);
    }
    return len;
}

int SourceFile::WriteNamespace(const char* name_space)
{
    int len = 0;
    if (!name_space || ((len = strlen(name_space)) == 0))
    {
        return 0;
    }
    const char& c = name_space[len - 1];
    if (c == '{')
    {
        len = fprintf(_file, "%s\n\n", name_space);
    }
    else
    {
        if (CommandLine::left_brace_pos)
        {
            len = fprintf(_file, "%s\n{\n\n", name_space);
        }
        else
        {
            len = fprintf(_file, "%s {\n\n", name_space);
        }
    }
    return len;
}

void SourceFile::Close()
{
    fclose(_file);
}

void SourceFile::CreateParentDirectory(const char* file_name)
{
    boost::filesystem::path file(file_name);
    boost::filesystem::path parent = file.parent_path();
    if (!boost::filesystem::exists(parent))
    {
        boost::filesystem::create_directories(parent);
    }
}
