#ifndef XAUTOCODE_FILESTRATEGY_FILESTRATEGY_H
#define XAUTOCODE_FILESTRATEGY_FILESTRATEGY_H

#include <string>

class FileStrategy
{
public:
    virtual ~FileStrategy();
    static FileStrategy* GetStrategy();
    bool GetFile(std::string& header_file, std::string& source_file, std::string& include_string);
    virtual void Init();

protected:
    virtual bool GetNextHeaderFile(std::string& header_file);
    virtual bool GetNextSourceFile(const std::string& header_file, std::string& source_file);
    virtual bool GetIncludeString(const std::string& header_file, std::string& include_string);
};

#endif
