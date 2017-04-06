#pragma once

#include <string>
#include <vector>

class DdsFile
{
    friend class DdsLoader;

public:
    DdsFile(const std::string & _filePath)
        :
        itHasSucceeded(false),
        filePath(_filePath)
    {
    }

    ~DdsFile() = default;

    bool hasSucceeded() const { return itHasSucceeded; }

private:
    bool itHasSucceeded;
    std::string filePath;
    std::vector<std::vector<char>> data;
};