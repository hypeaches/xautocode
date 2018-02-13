#ifndef XAUTOCODE_FILESTRATEGY_HEADERDIRSOURCEFILESTRATEGY_H
#define XAUTOCODE_FILESTRATEGY_HEADERDIRSOURCEFILESTRATEGY_H

#include <xautocode/FileStrategy/FileStrategy.h>

class HeaderdirSourcefileStrategy : public FileStrategy
{
public:
    virtual ~HeaderdirSourcefileStrategy();
    virtual void Work();

protected:
    virtual bool GetFile(std::string& header_file, std::string& source_file);
};

#endif // XAUTOCODE_FILESTRATEGY_HEADERDIRSOURCEFILESTRATEGY_H
