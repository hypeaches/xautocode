
#ifndef XAUTOCODE_FILESTRATEGY_HEADERFILESOURCEDIRSTRATEGY_H
#define XAUTOCODE_FILESTRATEGY_HEADERFILESOURCEDIRSTRATEGY_H

#include <xautocode/FileStrategy/FileStrategy.h>

class HeaderfileSourcedirStrategy : public FileStrategy
{
public:
    virtual ~HeaderfileSourcedirStrategy();
    virtual void Work();

protected:
    virtual void GetFile(std::string& header_file, std::string& source_file);
};

#endif // XAUTOCODE_FILESTRATEGY_HEADERFILESOURCEDIRSTRATEGY_H
