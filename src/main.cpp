#include <cstdio>
#include <stdexcept>
#include <exception>
#include <xautocode/CommandLine.h>
#include <xautocode/FileStrategy/FileStrategy.h>

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

        std::string header_file, source_file;
        header_file.reserve(1024);
        source_file.reserve(1024);

        while (strategy->GetFile(header_file, source_file))
        {
            printf("header:%s\n"
               "source:%s\n"
               "======================\n",
               header_file.c_str(), source_file.c_str());
        }
        ret = 0;
    }
    catch (const std::logic_error& err)
    {
        fprintf(stderr, "%s\n", err.what());
    }
    return 0;
}
