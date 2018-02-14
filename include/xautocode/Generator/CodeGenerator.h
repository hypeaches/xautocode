#ifndef XAUTOCODE_GENERATOR_CODEGENERATOR_H
#define XAUTOCODE_GENERATOR_CODEGENERATOR_H

class HeaderFile;
class SourceFile;

class CodeGenerator
{
public:
    CodeGenerator();
    ~CodeGenerator();
    void Work(const char* header_file_name, const char* source_file_name);

private:
    HeaderFile* _header_file;
    SourceFile* _source_file;
};

#endif // XAUTOCODE_GENERATOR_CODEGENERATOR_H
