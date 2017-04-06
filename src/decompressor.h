#pragma once

#include <vector>

class Decompressor
{
public:
    Decompressor() = delete;
    ~Decompressor() = delete;

    static void decompressDxt1(std::vector<char> & output, const std::vector<char> & input);
};
