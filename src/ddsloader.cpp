#include "ddsloader.h"
#include "ddsfile.h"

#include <iostream>
#include <string>
#include <fstream>

std::unique_ptr<DdsFile> DdsLoader::load(const std::string & filePath) const
{
    std::ifstream file{filePath};

    if(file.is_open())
    {
        auto result = std::unique_ptr<DdsFile>(new DdsFile{filePath});
        return result;
    }

    return nullptr;
}