#include <xautocode/FileStrategy/HeaderdirSourcedirRecursiveStrategy.h>
#include <xautocode/CommandLine.h>

void HeaderdirSourcedirRecursiveStrategy::Init()
{
    _it = boost::filesystem::recursive_directory_iterator(CommandLine::header);
    _it_end = boost::filesystem::recursive_directory_iterator();
    GetSourceRelativePath();
}

bool HeaderdirSourcedirRecursiveStrategy::GetNextHeaderFile(std::string& header_file)
{
    bool ret = false;
    header_file.clear();
    for (; !ret && (_it != _it_end); ++_it)
    {
        boost::filesystem::path p = _it->path();
        if (!boost::filesystem::is_regular_file(p))
        {
            continue;
        }
        if (p.extension().string() != ".h") 
        {
            continue;
        }
        header_file = p.string();
        ret = true;
    }
    return ret;
}

bool HeaderdirSourcedirRecursiveStrategy::GetIncludeString(const std::string& header_file, std::string& include_string)
{
    include_string.clear();
    include_string.append(header_file.substr(strlen(CommandLine::header)));
    return true;
}

