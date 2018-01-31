#include  <xautocode/CommandLine.h>

#include <gflags/gflags.h>

DEFINE_string(header, ".", "头文件或头文件所在目录");

const char* CommandLine::header = nullptr;

void CommandLine::Parse(int argc, char* argv[])
{
    std::string usage;
    google::SetUsageMessage(usage);
    google::ParseCommandLineFlags(&argc, &argv, true);

    CommandLine::header = FLAGS_header.c_str();
}
