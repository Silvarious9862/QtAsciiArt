#include "BitmapInfoHeader.h"

BitmapInfoHeader::BitmapInfoHeader()
{
    biSize          = 40;
    biWidth         = 200;
    biHeight        = 200;
    biPlanes        = 0x1;  // planes of image always 1   
    biBitCount      = 0x18; // default bitcount = 24   
    biCompression   = 0x0;  // default compress = 0   
    biSizeImage     = 0x0;  // no compression = always 0
    biXPelsPerMeter = 0x0;  // always 0
    biYPelsPerMeter = 0x0;  // always 0
    biClrUsed       = 0x0;  // always 0
    biClrImportant  = 0x0;  // always 0
}

uint32_t BitmapInfoHeader::GetWidth() const { return this->biWidth; }
uint32_t BitmapInfoHeader::GetHeight() const { return this->biHeight; }
uint16_t BitmapInfoHeader::GetBitcount() const { return this->biBitCount; }
void BitmapInfoHeader::SetBitCount(int bitCount) { biBitCount = bitCount; }

std::ostream& operator<< (std::ostream& outstream, const BitmapInfoHeader& bi)
{
    outstream.write((char*)&bi.biSize, sizeof(bi.biSize));
    outstream.write((char*)&bi.biWidth, sizeof(bi.biWidth));
    outstream.write((char*)&bi.biHeight, sizeof(bi.biHeight));
    outstream.write((char*)&bi.biPlanes, sizeof(bi.biPlanes));
    outstream.write((char*)&bi.biBitCount, sizeof(bi.biBitCount));
    outstream.write((char*)&bi.biCompression, sizeof(bi.biCompression));
    outstream.write((char*)&bi.biSizeImage, sizeof(bi.biSizeImage));
    outstream.write((char*)&bi.biXPelsPerMeter, sizeof(bi.biXPelsPerMeter));
    outstream.write((char*)&bi.biYPelsPerMeter, sizeof(bi.biYPelsPerMeter));
    outstream.write((char*)&bi.biClrUsed, sizeof(bi.biClrUsed));
    outstream.write((char*)&bi.biClrImportant, sizeof(bi.biClrImportant));
    return outstream;
}
std::istream& operator>> (std::istream& instream, BitmapInfoHeader& bi)
{
    instream.read((char*)&bi.biSize, sizeof(bi.biSize));
    instream.read((char*)&bi.biWidth, sizeof(bi.biWidth));
    instream.read((char*)&bi.biHeight, sizeof(bi.biHeight));
    instream.read((char*)&bi.biPlanes, sizeof(bi.biPlanes));
    instream.read((char*)&bi.biBitCount, sizeof(bi.biBitCount));
    instream.read((char*)&bi.biCompression, sizeof(bi.biCompression));
    instream.read((char*)&bi.biSizeImage, sizeof(bi.biSizeImage));
    instream.read((char*)&bi.biXPelsPerMeter, sizeof(bi.biXPelsPerMeter));
    instream.read((char*)&bi.biYPelsPerMeter, sizeof(bi.biYPelsPerMeter));
    instream.read((char*)&bi.biClrUsed, sizeof(bi.biClrUsed));
    instream.read((char*)&bi.biClrImportant, sizeof(bi.biClrImportant));
    return instream;
}