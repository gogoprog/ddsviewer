#pragma once

#include <string>
#include <vector>

class DdsFile
{
    friend class DdsLoader;

public:
    DdsFile(const std::string & _filePath)
        :
        filePath(_filePath)
    {
    }

    ~DdsFile() = default;

private:
    std::string filePath;
    std::vector<std::vector<char>> data;
};