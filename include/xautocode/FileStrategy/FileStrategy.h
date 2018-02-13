#ifndef XAUTOCODE_FILESTRATEGY_FILESTRATEGY_H
#define XAUTOCODE_FILESTRATEGY_FILESTRATEGY_H

#include <string>

class FileStrategy
{
public:
    virtual ~FileStrategy();
    void Work();

protected:
    virtual bool GetFile(std::string& header_file, std::string& source_file);
    virtual bool GetNextHeaderFile(std::string& header_file);
    virtual void GetHeaderFileRegularPath(const std::string& header_file, std::string& regular_path);
    virtual void GetSourceFile(const std::string& header_regular_path, const std::string& header_file_name, std::string& source_file);
};

#endif
