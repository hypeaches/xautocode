#ifndef XAUTOCODE_COMMANDLINE_H
#define XAUTOCODE_COMMANDLINE_H

class CommandLine
{
public:
    static void Parse(int argc, char* argv[]);
    /// 头文件名或头文件目录
    static const char* header;
    /// 源文件名或源文件目录
    static const char* source;
    /// 源文件后缀名，默认值：cpp
    static const char* ext;
    /// 换行符。Unix格式换行符LF(\n)或Windows格式换行符CRLF(\r\n)。默认值：LF
    static const char* newline;
    /// 左花括号的位置。与函数签名在同一行(0)或另起一行(1)。默认值：0
    static int   left_brace_pos;
};

#endif // XAUTOCODE_COMMANDLINE_H
