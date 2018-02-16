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

bool HeaderfileSourcefileStrategy::GetIncludeString(const std::string& header_file, std::string& include_string)
{
    include_string.clear();
    size_t ind = header_file.find_last_of('/');
    if ((ind == std::string::npos) || (ind >= header_file.size() - 1))
    {
        throw std::logic_error("parse include string failed");
    }
    include_string.append(header_file.substr(ind + 1));
    return true;
}
