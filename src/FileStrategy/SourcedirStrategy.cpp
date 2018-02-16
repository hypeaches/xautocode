#include <xautocode/FileStrategy/SourcedirStrategy.h>
#include <xautocode/CommandLine.h>
#include <boost/filesystem.hpp>

bool SourcedirStrategy::GetNextSourceFile(const std::string& header_file, std::string& source_file)
{
    source_file.clear();
    std::string relative = header_file.substr(_source_relative_path.size(), header_file.size() - _source_relative_path.size() - 2);
    source_file.append(CommandLine::source).append(relative).append(CommandLine::ext);
    bool ret = !boost::filesystem::exists(source_file);
    return ret;
}

void SourcedirStrategy::GetSourceRelativePath()
{
    if (CommandLine::tight)
    {
        GetTightSourceRelativePath();
    }
    else
    {
        _source_relative_path = CommandLine::header;
    }
}

void SourcedirStrategy::GetTightSourceRelativePath()
{
    _source_relative_path = CommandLine::header;
    bool next = true;
    std::string tmp;
    tmp.reserve(1024);
    while (next)
    {
        boost::filesystem::directory_iterator it(_source_relative_path);
        boost::filesystem::directory_iterator it_end;
        int count = 0;
        for (; it != it_end; ++it)
        {
            count++;
            tmp = it->path().string();
            if (boost::filesystem::is_regular_file(it->path()) && (it->path().extension().string() == ".h"))
            {
                next = false;
                break;
            }
        }
        if ((count == 1) && next)
        {
            _source_relative_path = tmp;
        }
    }
    if (!_source_relative_path.empty() && (_source_relative_path.back() != '/'))
    {
        _source_relative_path.append("/");
    }
}

