#include <xautocode/FileStrategy/FileStrategy.h>
#include <stdexcept>
#include <boost/filesystem.hpp>
#include <xautocode/CommandLine.h>
#include <xautocode/FileStrategy/HeaderdirSourcedirRecursiveStrategy.h>

namespace
{
HeaderdirSourcedirRecursiveStrategy headerdir_sourcedir_recursive_strategy;
}

FileStrategy::~FileStrategy()
{
}

FileStrategy* FileStrategy::GetStrategy()
{
    bool is_header_dir = boost::filesystem::is_directory(CommandLine::header);
    bool is_source_dir = boost::filesystem::is_directory(CommandLine::source);
    bool is_source_regular_file = boost::filesystem::is_regular_file(CommandLine::source);
    if (!is_source_dir && !is_source_regular_file)
    {
        throw std::logic_error("source is not a directory or a regular file");
    }

    FileStrategy* strategy = nullptr;
    if (is_header_dir && is_source_dir)
    {
        if (CommandLine::recursive)
        {
            strategy = &headerdir_sourcedir_recursive_strategy;
        }
        else
        {
        }
    }

    return strategy;
}

bool FileStrategy::GetFile(std::string& header_file, std::string& source_file)
{
    bool ret = false;
    header_file.clear();
    source_file.clear();
    while (!ret)
    {
        if (!GetNextHeaderFile(header_file))
        {
            break;
        }
        ret = GetNextSourceFile(header_file, source_file);
    }
    return ret;
}

void FileStrategy::Init()
{
}

bool FileStrategy::GetNextHeaderFile(std::string& header_file)
{
    return false;
}

bool FileStrategy::GetNextSourceFile(const std::string& header_file, std::string& source_file)
{
    return false;
}

