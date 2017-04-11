#include "ddsloader.h"
#include "ddsfile.h"

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <SFML/OpenGL.hpp>

using dword = unsigned int;

const dword DDS_MAGIC = 0x20534444;
const dword DDPF_FOURCC = 0x4;
const dword DDPF_RGB = 0x40;

constexpr dword fourCcToDword(const char *value)
{
    return value[0] + (value[1] << 8) + (value[2] << 16) + (value[3] << 24);
}

constexpr dword DXT1 = fourCcToDword("DXT1");
constexpr dword DXT2 = fourCcToDword("DXT2");
constexpr dword DXT3 = fourCcToDword("DXT3");
constexpr dword DXT4 = fourCcToDword("DXT4");
constexpr dword DXT5 = fourCcToDword("DXT5");
constexpr dword DX10 = fourCcToDword("DX10");

struct DdsPixelFormat
{
    dword dwSize;
    dword dwFlags;
    dword dwFourCC;
    dword dwRGBBitCount;
    dword dwRBitMask;
    dword dwGBitMask;
    dword dwBBitMask;
    dword dwABitMask;
};

struct DdsHeader
{
    dword dwSize;
    dword dwFlags;
    dword dwHeight;
    dword dwWidth;
    dword dwPitchOrLinearSize;
    dword dwDepth;
    dword dwMipMapCount;
    dword dwReserved1[11];
    DdsPixelFormat ddspf;
    dword dwCaps;
    dword dwCaps2;
    dword dwCaps3;
    dword dwCaps4;
    dword dwReserved2;
};

struct DdsHeaderDxt10
{
    int dxgiFormat;
    int resourceDimension;
    unsigned int miscFlag;
    unsigned int arraySize;
    unsigned int miscFlags2;
};

template<typename Struct>
void read(std::ifstream & file, Struct & output)
{
    file.read(reinterpret_cast<char*>(&output), sizeof(Struct));
}

std::unique_ptr<DdsFile> DdsLoader::load(const std::string & filePath)
{
    std::ifstream file{filePath};

    if(file.is_open())
    {
        auto result = std::unique_ptr<DdsFile>(new DdsFile{filePath});
        std::vector<char> data;
        DdsHeader header;
        dword magic;

        read(file, magic);
        
        if(magic != DDS_MAGIC)
        {
            std::cout << "Wrong magic number, not a dds file?" << std::endl;
            return nullptr;
        }

        read(file, header);

        std::cout << "Dimensions: " << header.dwWidth << "x" << header.dwHeight << std::endl;
        std::cout << "Mipmap count:" << header.dwMipMapCount << std::endl;

        int width = header.dwWidth;
        int height = header.dwHeight;

        if(header.ddspf.dwFlags & DDPF_FOURCC) 
        {
            int blocSize;
            GLenum glFormat;

            switch(header.ddspf.dwFourCC)
            {
                case DXT1:
                {
                    blocSize = 8;
                    glFormat = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
                }
                break;

                case DXT2:
                {
                    blocSize = 16;
                }
                break;

                case DXT3:
                {
                    blocSize = 16;
                    glFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
                }
                break;

                case DXT4:
                {
                    blocSize = 16;
                }
                break;

                case DXT5:
                {
                    blocSize = 16;
                    glFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                }
                break;

                case DX10:
                {
                    DdsHeaderDxt10 headerDxt10;
                    read(file, headerDxt10);
                    std::cout << "DX10" << std::endl;
                }
                break;
            }

            int totalSize = std::max(1, ( (width + 3) / 4 ) ) * std::max(1, ( (height + 3) / 4 ) ) * blocSize;

            data.resize(totalSize);

            file.read(&data[0], totalSize);

            result->texture.create(width, height);

            sf::Texture::bind(&result->texture);

            glCompressedTexImage2D(
                GL_TEXTURE_2D,
                0,
                glFormat,
                width,
                height,
                0,
                totalSize,
                &data[0]
                );

            GLenum error = glGetError();

            if (error) 
            {
                std::cout << std::hex << "Error: " << error << std::endl;
                return nullptr;
            }
        }

        return result;
    }

    return nullptr;
}