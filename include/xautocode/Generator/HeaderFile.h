#ifndef XAUTOCODE_GENERATOR_HEADERFILE_H
#define XAUTOCODE_GENERATOR_HEADERFILE_H

#include <cstdio>

class HeaderFile
{
public:
    char* return_type;
    char* function;
    char* name_space;
    char* class_name;
    void Open(const char* file_name);
    void Close();
    char* ParseNamespace();
    char* ParseClassName();
    bool ReadLine();

private:
    bool DoReadLine();
    bool IsFunction();
    void Trim();
    void TrimLeft();
    void TrimRight();
    FILE* _file;
    char* ParseReturnType();
    char* ParseFunction();
    char* _head;
    int _line_length;
    char* _buffer[4 * 1024];
    char _class_name[32];
    char _name_space[32];
    char _name_space_end[32];
};

#endif // XAUTOCODE_GENERATOR_HEADERFILE_H
