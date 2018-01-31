#include <cstdio>
#include <xautocode/CommandLine.h>

int main(int argc, char* argv[])
{
    CommandLine::Parse(argc, argv);
    printf("header:%s\n", CommandLine::header);
    return 0;
}
