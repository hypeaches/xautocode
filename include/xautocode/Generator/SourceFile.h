#ifndef XAUTOCODE_GENERATOR_SOURCEFILE_H
#define XAUTOCODE_GENERATOR_SOURCEFILE_H

#include <cstdio>

class SourceFile
{
public:
    void Open(const char* file_name);
    int  Write(const char* return_type, const char* class_name, const char* function);
    int  WriteNamespace(const char* name_space);
    void Close();

private:
    FILE* _file;
    int _left_brace_count;
};

#endif // XAUTOCODE_GENERATOR_SOURCEFILE_H
