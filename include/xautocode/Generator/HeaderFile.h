#ifndef XAUTOCODE_GENERATOR_HEADERFILE_H
#define XAUTOCODE_GENERATOR_HEADERFILE_H

#include <cstdio>

class HeaderFile
{
public:
    const char* return_type;
    const char* function;
    const char* name_space;
    const char* name_space_end;
    const char* class_name;
    void Open(const char* file_name);
    void Close();
    char* ParseNamespace();
    char* ParseClassName();
    bool ReadLine();

private:
    enum FunctionType
    {
        ft_none,
        ft_constructor,
        ft_deconstructor,
        ft_normal
    };
    void ParseNamespaceEnd();
    bool DoReadLine();
    bool IsFunction();
    char* ParseFunctionType();
    char* Trim(char* str);
    char* TrimLeft(char* str);
    char* TrimRight(char* str);
    char* MoveToNextWord(char* str);
    FILE* _file;
    char* ClearRedundant();
    const char* ParseReturnType();
    const char* ParseFunction();
    char* _head;
    int _line_length;
    char _buffer[4 * 1024];
    char _class_name[32];
    char _name_space[32];
    char _name_space_end[32];
    FunctionType _function_type;
};

#endif // XAUTOCODE_GENERATOR_HEADERFILE_H
