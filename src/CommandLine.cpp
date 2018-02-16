#include  <xautocode/CommandLine.h>

#include <iostream>
#include <string>
#include <stdexcept>
#include <boost/program_options.hpp>

bool        CommandLine::recursive      = false;
bool        CommandLine::tight          = true;
const char* CommandLine::include_prefix = NULL;
const char* CommandLine::header         = NULL;
const char* CommandLine::source         = NULL;
const char* CommandLine::ext            = NULL;
const char* CommandLine::newline        = NULL;
int         CommandLine::left_brace_pos = 0;

namespace {
    boost::program_options::options_description desc("Options");
    bool        cmd_recursive = false;
    bool        cmd_tight     = true;
    std::string cmd_include_prefix("");
    std::string cmd_header("");
    std::string cmd_source("");
    std::string cmd_ext(".cpp");
    std::string cmd_newline("\n");
    int         cmd_left_brace_pos = 0;
}

void InitCommandLine();

void CommandLine::Parse(int argc, char* argv[])
{
    desc.add_options()
        ("help", "帮助")
        ("recursive,r", boost::program_options::value<bool>(), "是否递归遍历header，默认值：false")
        ("tight,t", boost::program_options::value<bool>(), "紧凑型，默认值：true")
        ("include-prefix", boost::program_options::value<std::string>(), "头文件相对目录，默认值：空")
        ("header", boost::program_options::value<std::string>(), "指定头文件")
        ("source", boost::program_options::value<std::string>(), "指定源文件")
        ("ext", boost::program_options::value<std::string>(), "源文件后缀名，默认值：.cpp")
        ("newline",boost::program_options::value<std::string>(), "换行符LF(\\n)或CRFL(\\r\\n)，默认值：LF")
        ("left-brace-pos",boost::program_options::value<int>(), "左花括号位置，与函数签名在同一行(0)或另起一行(1)，默认值：0");

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    if (vm.count("help") || (argc == 1))
    {
        std::cout<<desc<<std::endl;
        exit(0);
    }

    if (vm.count("recursive"))
    {
        cmd_recursive = vm["recursive"].as<bool>();
    }
    else if (vm.count("r"))
    {
        cmd_recursive = vm["r"].as<bool>();
    }
    if (vm.count("tight"))
    {
        cmd_tight = vm["tight"].as<bool>();
    }
    else if (vm.count("t"))
    {
        cmd_tight = vm["t"].as<bool>();
    }
    if (vm.count("include-prefix"))
    {
        cmd_include_prefix = vm["include-prefix"].as<std::string>();
        if (!cmd_include_prefix.empty() && (cmd_include_prefix.back() != '/'))
        {
            cmd_include_prefix.append("/");
        }
    }
    if (vm.count("header"))
    {
        cmd_header = vm["header"].as<std::string>();
        if ((cmd_header.find_last_of('.') != (cmd_header.size() - 2)) && !cmd_header.empty() && (cmd_header.back() != '/'))
        {
            cmd_header.append("/");
        }
    }
    if (vm.count("source"))
    {
        cmd_source = vm["source"].as<std::string>();
        if ((cmd_source.find_last_of('.') != (cmd_source.size() - 2)) && !cmd_source.empty() && (cmd_source.back() != '/'))
        {
            cmd_source.append("/");
        }
    }
    if (vm.count("ext"))
    {
        cmd_ext = vm["ext"].as<std::string>();
        if (!cmd_ext.empty() && (cmd_ext[0] != '.'))
        {
            cmd_ext = "." + cmd_ext;
        }
    }
    if (vm.count("newline"))
    {
        cmd_newline = vm["newline"].as<std::string>();
    }
    if (vm.count("left-brace-pos"))
    {
        cmd_left_brace_pos = vm["left-brace-pos"].as<int>();
    }

    InitCommandLine();
}

void  InitCommandLine()
{
    CommandLine::recursive = cmd_recursive;
    CommandLine::tight     = cmd_tight;
    CommandLine::include_prefix = cmd_include_prefix.c_str();
    CommandLine::header = cmd_header.c_str();
    CommandLine::source = cmd_source.c_str();
    CommandLine::ext = cmd_ext.c_str();
    CommandLine::newline = cmd_newline.c_str();
    CommandLine::left_brace_pos = cmd_left_brace_pos;
}
