#include "ddsloader.h"
#include "ddsfile.h"

#include <iostream>
#include <string>
#include <fstream>

using dword = unsigned int;

const dword DDS_MAGIC = 0x20534444;
const dword DDPF_FOURCC = 0x4;

constexpr dword fourCcToInt32(const char *value)
{
    return value[0] + (value[1] << 8) + (value[2] << 16) + (value[3] << 24);
}

constexpr dword DXT1 = fourCcToInt32("DXT1");
constexpr dword DXT2 = fourCcToInt32("DXT2");
constexpr dword DXT3 = fourCcToInt32("DXT3");
constexpr dword DXT4 = fourCcToInt32("DXT4");
constexpr dword DXT5 = fourCcToInt32("DXT5");
constexpr dword DX10 = fourCcToInt32("DX10");

struct DdsPixelFormat {
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
        DdsHeader header;
        dword magic;

        read(file, magic);
        
        if(magic != DDS_MAGIC)
        {
            std::cout << "Wrong magic number, not a dds file?" << std::endl;
            return nullptr;
        }

        read(file, header);

        if((header.ddspf.dwFlags & DDPF_FOURCC) && header.ddspf.dwFourCC == DX10)
        {
            DdsHeaderDxt10 headerDxt10;
            read(file, headerDxt10);
        }

        return result;
    }

    return nullptr;
}