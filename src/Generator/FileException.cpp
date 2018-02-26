#include <xautocode/Generator/FileException.h>
#include <cstdio>

FileException::FileException(const char* file_name, const char* op)
{
    snprintf(_buffer, sizeof(_buffer), "file operation failed, operation:%s, file:%s", op, file_name);
}

const char* FileException::what() const throw()
{
    return _buffer;
}
