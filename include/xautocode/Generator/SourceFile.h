#ifndef XAUTOCODE_GENERATOR_SOURCEFILE_H
#define XAUTOCODE_GENERATOR_SOURCEFILE_H

#include <cstdio>

class SourceFile
{
public:
    FILE* file()
    {
        return _file;
    }
    bool Exist(const char* file_name);
    bool Open(const char* file_name);
    void Close();

private:
    FILE* _file;
};

#endif // XAUTOCODE_GENERATOR_SOURCEFILE_H
