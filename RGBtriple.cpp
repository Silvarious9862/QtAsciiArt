#include "RGBtriple.h"

RGBtriple::RGBtriple() { rgbBlue = 0; rgbGreen = 0; rgbRed = 0; };

void RGBtriple::SetRGB(uint8_t red, uint8_t green, uint8_t blue)
{
    rgbBlue = blue;
    rgbGreen = green;
    rgbRed = red;
}

void RGBtriple::SetBlue(uint8_t blue) { rgbBlue = blue; }
void RGBtriple::SetGreen(uint8_t green) { rgbGreen = green; }
void RGBtriple::SetRed(uint8_t red) { rgbRed = red; }
uint8_t RGBtriple::GetBlue() const { return rgbBlue; }
uint8_t RGBtriple::GetGreen() const { return rgbGreen; }
uint8_t RGBtriple::GetRed() const { return rgbRed; }

std::ostream& operator<< (std::ostream& outstream, const RGBtriple& rgb)
{
    return outstream << rgb.rgbBlue << rgb.rgbGreen << rgb.rgbRed;
}
std::istream& operator>> (std::istream& instream, const RGBtriple& rgb)
{
    instream.read((char*)rgb.rgbBlue, sizeof(rgb.rgbBlue));
    instream.read((char*)rgb.rgbGreen, sizeof(rgb.rgbGreen));
    instream.read((char*)rgb.rgbRed, sizeof(rgb.rgbRed));
    return instream;
}