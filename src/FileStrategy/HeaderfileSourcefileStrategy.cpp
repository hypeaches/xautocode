#include <xautocode/FileStrategy/HeaderfileSourcefileStrategy.h>
#include <xautocode/CommandLine.h>
#include <boost/filesystem.hpp>

bool HeaderfileSourcefileStrategy::GetNextHeaderFile(std::string& header_file)
{
    static int ret = 0;
    if (ret == 0)
    {
        header_file = CommandLine::header;
        if (!header_file.empty() && (header_file.back() == '/'))
        {
            header_file.pop_back();
        }
    }
    ret++;
    return (ret == 1);
}

bool HeaderfileSourcefileStrategy::GetNextSourceFile(const std::string& header_file, std::string& source_file)
{
    source_file = CommandLine::source;
    bool ret = !boost::filesystem::exists(source_file);
    return ret;
}
