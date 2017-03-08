#pragma once

#include <string>
#include <fstream>

class DdsFile
{
public:
    DdsFile(const std::string & filePath)
    :
    itHasSucceeded(false)
    {
        std::ifstream file(filePath);

        if(file.is_open())
        {
            std::cout << "file opened!" << std::endl;
        }
    }

    ~DdsFile()
    {

    }

    bool hasSucceeded() const { return itHasSucceeded; }

private:
    bool itHasSucceeded;
};