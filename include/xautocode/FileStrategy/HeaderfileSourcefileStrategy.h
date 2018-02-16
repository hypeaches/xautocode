
#ifndef XAUTOCODE_FILESTRATEGY_HEADERFILESOURCEFILESTRATEGY_H
#define XAUTOCODE_FILESTRATEGY_HEADERFILESOURCEFILESTRATEGY_H

#include <xautocode/FileStrategy/FileStrategy.h>

class HeaderfileSourcefileStrategy : public FileStrategy
{
protected:
    virtual bool GetNextHeaderFile(std::string& header_file);
    virtual bool GetNextSourceFile(const std::string& header_file, std::string& source_file);
    virtual bool GetIncludeString(const std::string& header_file, std::string& include_string);
};

#endif // XAUTOCODE_FILESTRATEGY_HEADERFILESOURCEFILESTRATEGY_H
