#include <xautocode/FileStrategy/HeaderdirSourcefileStrategy.h>
#include <stdexcept>

void HeaderdirSourcefileStrategy::Init()
{
    throw std::logic_error("header is a directory, source is a file, invalid operation");
}
