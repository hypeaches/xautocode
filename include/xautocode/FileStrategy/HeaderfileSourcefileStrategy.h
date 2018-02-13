
#ifndef XAUTOCODE_FILESTRATEGY_HEADERFILESOURCEFILESTRATEGY_H
#define XAUTOCODE_FILESTRATEGY_HEADERFILESOURCEFILESTRATEGY_H

#include <xautocode/FileStrategy/FileStrategy.h>

class HeaderfileSourcefileStrategy : public FileStrategy
{
public:
    virtual ~HeaderfileSourcefileStrategy();
    virtual void Work();

protected:
    virtual bool GetFile(std::string& header_file, std::string& source_file);
};

#endif // XAUTOCODE_FILESTRATEGY_HEADERFILESOURCEFILESTRATEGY_H
