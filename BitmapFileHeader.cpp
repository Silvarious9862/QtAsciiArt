#include "BitmapFileHeader.h"

BitmapFileHeader::BitmapFileHeader()
{
    bfType[0] = 0x42;    // BM
    bfType[1] = 0x4D;
    bfSize = 0x0000;
    bfReserved1 = 0x0000;  // always 0
    bfReserved2 = 0x0000;  // always 0
    bfOffBits = 0x36;    // always 54
}

void BitmapFileHeader::SetbfSize(BitmapInfoHeader& bi)
{
    bfSize = bfOffBits + sizeof(RGBtriple) * bi.GetHeight() * bi.GetWidth();
}

bool BitmapFileHeader::CheckBM()
{
    if (bfType[0] == 0x42 && bfType[1] == 0x4D) return true;
    else return false;
}

uint32_t BitmapFileHeader::GetbfSize() const { return bfSize; }

uint32_t BitmapFileHeader::GetbfOffBits() const { return bfOffBits; }

std::ostream& operator<< (std::ostream& outstream, const BitmapFileHeader& bf)
{
    outstream.write((char*)&bf.bfType, sizeof(bf.bfType));
    outstream.write((char*)&bf.bfSize, sizeof(bf.bfSize));
    outstream.write((char*)&bf.bfReserved1, sizeof(bf.bfReserved1));
    outstream.write((char*)&bf.bfReserved2, sizeof(bf.bfReserved2));
    outstream.write((char*)&bf.bfOffBits, sizeof(bf.bfOffBits));

    return outstream;
}

std::istream& operator>> (std::istream& instream, const BitmapFileHeader& bf)
{
    instream.read((char*)&bf.bfType, sizeof(bf.bfType));
    instream.read((char*)&bf.bfSize, sizeof(bf.bfSize));
    instream.read((char*)&bf.bfReserved1, sizeof(bf.bfReserved1));
    instream.read((char*)&bf.bfReserved2, sizeof(bf.bfReserved2));
    instream.read((char*)&bf.bfOffBits, sizeof(bf.bfOffBits));

    return instream;
}