#ifndef XAUTOCODE_FILESTRATEGY_HEADERDIRSOURCEDIRSTRATEGY_H
#define XAUTOCODE_FILESTRATEGY_HEADERDIRSOURCEDIRSTRATEGY_H

#include <xautocode/FileStrategy/FileStrategy.h>

class HeaderdirSourcedirStrategy : public FileStrategy
{
public:
    virtual ~HeaderdirSourcedirStrategy();
    virtual void Work();

protected:
    virtual void GetFile(std::string& header_file, std::string& source_file);
};

#endif // XAUTOCODE_FILESTRATEGY_HEADERDIRSOURCEDIRSTRATEGY_H
