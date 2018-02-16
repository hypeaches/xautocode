#ifndef XAUTOCODE_FILESTRATEGY_HEADERDIRSOURCEDIRSTRATEGY_H
#define XAUTOCODE_FILESTRATEGY_HEADERDIRSOURCEDIRSTRATEGY_H

#include <boost/filesystem.hpp>
#include <xautocode/FileStrategy/FileStrategy.h>
#include <xautocode/FileStrategy/SourcedirStrategy.h>

class HeaderdirSourcedirStrategy : public FileStrategy, public SourcedirStrategy
{
public:
    virtual void Init();

protected:
    virtual bool GetNextHeaderFile(std::string& header_file);
    virtual bool GetNextSourceFile(const std::string& header_file, std::string& source_file);

private:
    boost::filesystem::directory_iterator _it;
    boost::filesystem::directory_iterator _it_end;
};

#endif // XAUTOCODE_FILESTRATEGY_HEADERDIRSOURCEDIRSTRATEGY_H
