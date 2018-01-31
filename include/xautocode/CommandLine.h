#ifndef XAUTOCODE_COMMANDLINE_H
#define XAUTOCODE_COMMANDLINE_H

class CommandLine
{
public:
    static void Parse(int argc, char* argv[]);
    static const char* header;
};

#endif // XAUTOCODE_COMMANDLINE_H
