#pragma once

#include <string>
#include <memory>
#include "ddsfile.h"

class DdsLoader
{
public:
    DdsLoader() = delete;
    ~DdsLoader() = delete;

    static std::unique_ptr<DdsFile> load(const std::string & filePath);
};