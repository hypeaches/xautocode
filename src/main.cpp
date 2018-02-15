#include <cstdio>
#include <xautocode/CommandLine.h>
#include <xautocode/FileStrategy/FileStrategy.h>

int main(int argc, char* argv[])
{
    CommandLine::Parse(argc, argv);

    FileStrategy* strategy = FileStrategy::GetStrategy();
    if (!strategy)
    {
        fprintf(stderr, "file traverse failed\n");
        return 1;
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
    return 0;
}
