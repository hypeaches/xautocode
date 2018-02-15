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

bool HeaderdirSourcedirRecursiveStrategy::GetNextSourceFile(const std::string& header_file, std::string& source_file)
{
    source_file.clear();
    std::string relative = header_file.substr(_source_relative_path.size(), header_file.size() - _source_relative_path.size() - 2);
    source_file.append(CommandLine::source).append(relative).append(CommandLine::ext);
    bool ret = !boost::filesystem::exists(source_file);
    return ret;
}

