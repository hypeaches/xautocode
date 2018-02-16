#include <xautocode/FileStrategy/FileStrategy.h>
#include <stdexcept>
#include <boost/filesystem.hpp>
#include <xautocode/CommandLine.h>
#include <xautocode/FileStrategy/HeaderdirSourcedirStrategy.h>
#include <xautocode/FileStrategy/HeaderdirSourcedirRecursiveStrategy.h>
#include <xautocode/FileStrategy/HeaderdirSourcefileStrategy.h>
#include <xautocode/FileStrategy/HeaderfileSourcedirStrategy.h>
#include <xautocode/FileStrategy/HeaderfileSourcefileStrategy.h>

namespace
{
HeaderdirSourcedirStrategy          headerdir_sourcedir_strategy;
HeaderdirSourcedirRecursiveStrategy headerdir_sourcedir_recursive_strategy;
HeaderdirSourcefileStrategy         headerdir_sourcefile_strategy;
HeaderfileSourcedirStrategy         headerfile_sourcedir_strategy;
HeaderfileSourcefileStrategy        headerfile_sourcefile_strategy;
}

FileStrategy::~FileStrategy()
{
}

FileStrategy* FileStrategy::GetStrategy()
{
    bool is_header_dir = boost::filesystem::is_directory(CommandLine::header);
    bool is_header_regualr_file = boost::filesystem::is_regular_file(CommandLine::header);
    bool is_source_dir = boost::filesystem::is_directory(CommandLine::source);
    bool is_source_regular_file = boost::filesystem::is_regular_file(CommandLine::source);
    //if (!is_source_dir && !is_source_regular_file)
    //{
    //    throw std::logic_error("source is not a directory or a regular file");
    //}
    //if (!is_header_dir && !is_header_regualr_file)
    //{
    //    throw std::logic_error("header is not a directory or a regualr file");
    //}

    FileStrategy* strategy = nullptr;
    if (is_header_dir && is_source_dir)
    {
        if (CommandLine::recursive)
        {
            strategy = &headerdir_sourcedir_recursive_strategy;
        }
        else
        {
            strategy = &headerdir_sourcedir_strategy;
        }
    }
    else if (is_header_dir && is_source_regular_file)
    {
        strategy = &headerdir_sourcefile_strategy;
    }
    else if (is_header_regualr_file && is_source_dir)
    {
        strategy = &headerfile_sourcedir_strategy;
    }
    else if (is_header_regualr_file && !is_source_dir)
    {
        strategy = &headerfile_sourcefile_strategy;
    }

    return strategy;
}

bool FileStrategy::GetFile(std::string& header_file, std::string& source_file, std::string& include_string)
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
        if (!ret)
        {
            break;
        }
        ret = GetIncludeString(header_file, include_string);
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

bool FileStrategy::GetIncludeString(const std::string& header_file, std::string& include_string)
{
    return false;
}
