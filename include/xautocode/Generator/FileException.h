#ifndef XAUTOCODE_GENERATOR_FILEEXCEPTION_H
#define XAUTOCODE_GENERATOR_FILEEXCEPTION_H

#include <exception>

class FileException
{
public:
    FileException(const char* file_name, const char* op);
    virtual const char* what() const throw();

private:
    char _buffer[2048];
};

#endif // XAUTOCODE_GENERATOR_FILEEXCEPTION_H
