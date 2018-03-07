#include <cstdio>
#include <stdexcept>
#include <exception>
#include <xautocode/CommandLine.h>
#include <xautocode/FileStrategy/FileStrategy.h>
#include <xautocode/Generator/CodeGenerator.h>
#include <xautocode/Generator/FileException.h>

int main(int argc, char* argv[])
{
    int ret = 1;
    try
    {
        CommandLine::Parse(argc, argv);

        FileStrategy* strategy = FileStrategy::GetStrategy();
        if (!strategy)
        {
            throw std::logic_error("file traverse failed");
        }
        strategy->Init();

        std::string header_file, source_file, include_string;
        header_file.reserve(1024);
        source_file.reserve(1024);
        include_string.reserve(1024);

        CodeGenerator cd;
        while (strategy->GetFile(header_file, source_file, include_string))
        {
            printf("header:%s\n"
               "source:%s\n"
               "include:%s\n"
               "======================\n",
               header_file.c_str(), source_file.c_str(), include_string.c_str());
            cd.Work(header_file.c_str(), source_file.c_str(), include_string.c_str());
        }
        ret = 0;
    }
    catch (const std::logic_error& err)
    {
        fprintf(stderr, "%s", err.what());
    }
    catch (const FileException& err)
    {
        fprintf(stderr, "%s", err.what());
    }
    catch (const std::exception& err)
    {
        fprintf(stderr, "%s", err.what());
    }
    return 0;
}
