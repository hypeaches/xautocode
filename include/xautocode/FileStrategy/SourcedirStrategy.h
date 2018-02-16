#ifndef XAUTOCODE_FILESTRATEGY_SOURCEDIRSTRATEGY_H
#define XAUTOCODE_FILESTRATEGY_SOURCEDIRSTRATEGY_H

#include <xautocode/FileStrategy/FileStrategy.h>

class SourcedirStrategy : public FileStrategy
{
protected:
    virtual bool GetNextSourceFile(const std::string& header_file, std::string& source_file);
    void GetSourceRelativePath();
    std::string _source_relative_path;

private:
    void GetTightSourceRelativePath();
};

#endif // XAUTOCODE_FILESTRATEGY_SOURCEDIRSTRATEGY_H
