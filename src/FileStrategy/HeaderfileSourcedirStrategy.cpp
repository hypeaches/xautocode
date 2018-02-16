#include <xautocode/FileStrategy/HeaderfileSourcedirStrategy.h>
#include <stdexcept>
#include <boost/filesystem.hpp>
#include <xautocode/CommandLine.h>

bool HeaderfileSourcedirStrategy::GetNextHeaderFile(std::string& header_file)
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

bool HeaderfileSourcedirStrategy::GetNextSourceFile(const std::string& header_file, std::string& source_file)
{
    size_t ind = header_file.find_last_of('/');
    if ((ind == std::string::npos) || (ind == header_file.size() - 1))
    {
        throw std::logic_error("parse source file name failed");
    }
    ind++;
    source_file.clear();
    source_file.append(CommandLine::source).append(header_file.substr(ind, header_file.size() - ind - 2)).append(CommandLine::ext);
    bool ret = !boost::filesystem::exists(source_file);
    return ret;
}

bool HeaderfileSourcedirStrategy::GetIncludeString(const std::string& header_file, std::string& include_string)
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

