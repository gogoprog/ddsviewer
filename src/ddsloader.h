#pragma once

#include <string>
#include <memory>
#include "ddsfile.h"

class DdsLoader
{
public:
    DdsLoader() = default;
    ~DdsLoader() = default;

    std::unique_ptr<DdsFile> load(const std::string & filePath) const;
};