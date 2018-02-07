#include  <xautocode/CommandLine.h>

#include <iostream>
#include <string>
#include <stdexcept>
#include <boost/program_options.hpp>

const char* CommandLine::header = nullptr;
const char* CommandLine::source = nullptr;
const char* CommandLine::ext    = nullptr;

namespace {
    boost::program_options::options_description desc("Options");
    std::string cmd_header;
    std::string cmd_source;
    std::string cmd_ext;
}

void InitCommandLine();

void CommandLine::Parse(int argc, char* argv[])
{
    desc.add_options()
        ("help", "帮助")
        ("header", boost::program_options::value<std::string>(), "指定头文件")
        ("source", boost::program_options::value<std::string>(), "指定源文件")
        ("ext", boost::program_options::value<std::string>(), "源文件后缀名，默认值为cpp");

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    if (vm.count("help") || (argc == 1))
    {
        std::cout<<desc<<std::endl;
        exit(0);
    }

    if (vm.count("header"))
    {
        cmd_header = vm["header"].as<std::string>();
    }
    if (vm.count("source"))
    {
        cmd_source = vm["source"].as<std::string>();
    }
    if (vm.count("ext"))
    {
        cmd_ext = vm["ext"].as<std::string>();
    }

    InitCommandLine();
}

void  InitCommandLine()
{
    CommandLine::header = cmd_header.c_str();
    CommandLine::source = cmd_source.c_str();
    CommandLine::ext = cmd_ext.c_str();
}
