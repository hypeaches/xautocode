#include <xautocode/FileStrategy/HeaderdirSourcedirStrategy.h>
#include <xautocode/CommandLine.h>

void HeaderdirSourcedirStrategy::Init()
{
    _it = boost::filesystem::directory_iterator(CommandLine::header);
    _it_end = boost::filesystem::directory_iterator();
    GetSourceRelativePath();
}

bool HeaderdirSourcedirStrategy::GetNextHeaderFile(std::string& header_file)
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

