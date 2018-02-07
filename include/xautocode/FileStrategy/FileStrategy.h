#ifndef XAUTOCODE_FILESTRATEGY_FILESTRATEGY_H
#define XAUTOCODE_FILESTRATEGY_FILESTRATEGY_H

#include <string>

class FileStrategy
{
public:
    virtual ~FileStrategy();
    virtual void Work();

protected:
    virtual void GetFile(std::string& header_file, std::string& source_file);
};

#endif
