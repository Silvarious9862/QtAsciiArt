#pragma once
#include <cstdint>
#include <iostream>
#include "BitmapInfoHeader.h"
#include "RGBtriple.h"

class BitmapFileHeader;
class BitmapInfoHeader;
class Pallette;
class RGBtriple;
class PixMap;
class Bitmap;

class BitmapFileHeader
{
private:
    uint8_t bfType[2];
    uint32_t bfSize;
    uint16_t bfReserved1, bfReserved2;
    uint32_t bfOffBits;

public:
    BitmapFileHeader();
    void SetbfSize(BitmapInfoHeader& bi);
    bool CheckBM();
    uint32_t GetbfSize() const;
    uint32_t GetbfOffBits() const;
    friend std::ostream& operator<< (std::ostream& outstream, const BitmapFileHeader& bf);
    friend std::istream& operator>> (std::istream& instream, const BitmapFileHeader& bf);
};

