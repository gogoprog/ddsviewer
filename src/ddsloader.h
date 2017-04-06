#pragma once

#include <string>
#include "ddsfile.h"

class DdsLoader
{
public:
    DdsLoader() = default;
    ~DdsLoader() = default;

    const DdsFile & load(const std::string & filePath) const;
};