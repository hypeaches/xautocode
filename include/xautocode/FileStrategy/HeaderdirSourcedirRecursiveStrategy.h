#ifndef XAUTOCODE_FILESTRATEGY_HEADERDIRSOURCEDIRRECURSIVESTRATEGY_H
#define XAUTOCODE_FILESTRATEGY_HEADERDIRSOURCEDIRRECURSIVESTRATEGY_H

#include <boost/filesystem.hpp>
#include <xautocode/FileStrategy/SourcedirStrategy.h>

class HeaderdirSourcedirRecursiveStrategy : public SourcedirStrategy
{
public:
    virtual void Init();

protected:
    virtual bool GetNextHeaderFile(std::string& header_file);

private:
    boost::filesystem::recursive_directory_iterator _it;
    boost::filesystem::recursive_directory_iterator _it_end;
};

#endif // XAUTOCODE_FILESTRATEGY_HEADERDIRSOURCEDIRRECURSIVESTRATEGY_H
