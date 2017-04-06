#include "ddsloader.h"
#include "ddsfile.h"

#include <iostream>
#include <string>
#include <fstream>

const DdsFile & DdsLoader::load(const std::string & filePath) const
{
    DdsFile *result = new DdsFile(filePath);

    std::ifstream file(filePath);

    if(file.is_open())
    {
        std::cout << "file opened!" << std::endl;
    }

    return *result;
}