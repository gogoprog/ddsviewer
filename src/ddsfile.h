#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics/Texture.hpp>

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

    const auto & getTexture() const { return texture; }
    const auto & getFilePath() const { return filePath; }

private:
    std::string filePath;
    sf::Texture texture;
};