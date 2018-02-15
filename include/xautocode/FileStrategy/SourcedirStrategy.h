#ifndef XAUTOCODE_FILESTRATEGY_SOURCEDIRSTRATEGY_H
#define XAUTOCODE_FILESTRATEGY_SOURCEDIRSTRATEGY_H

#include <string>

class SourcedirStrategy
{
protected:
    void GetSourceRelativePath();
    std::string _source_relative_path;

private:
    void GetTightSourceRelativePath();
};

#endif // XAUTOCODE_FILESTRATEGY_SOURCEDIRSTRATEGY_H
