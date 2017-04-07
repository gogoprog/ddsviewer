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

    const sf::Texture & getTexture() const { return texture; }

private:
    std::string filePath;
    sf::Texture texture;
};