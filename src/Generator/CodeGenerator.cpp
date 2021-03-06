#include <xautocode/Generator/CodeGenerator.h>
#include <cstdio>
#include <xautocode/Generator/HeaderFile.h>
#include <xautocode/Generator/SourceFile.h>

namespace
{
    HeaderFile hf;
    SourceFile sf;
}

CodeGenerator::CodeGenerator()
{
    _header_file = &hf;
    _source_file = &sf;
}

CodeGenerator::~CodeGenerator()
{
}

void CodeGenerator::Work(const char* header_file_name, const char* source_file_name, const char* include_string)
{
    _header_file->Open(header_file_name);
    _source_file->Open(source_file_name);
    
    _header_file->ParseNamespace();
    _header_file->ParseClassName();

    char buf[1024];
    snprintf(buf, sizeof(buf), "include <%s>\n", include_string);
    _source_file->Write(buf);
    _source_file->WriteNamespace(_header_file->name_space);
    while(_header_file->ReadLine())
    {
        _source_file->Write(_header_file->return_type, _header_file->class_name, _header_file->function);
    }
    _source_file->Write(_header_file->name_space_end);

    _header_file->Close();
    _source_file->Close();
}
