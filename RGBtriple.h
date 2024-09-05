#pragma once
#include <cstdint>
#include <iostream>

class RGBtriple
{
private:
    uint8_t rgbBlue;
    uint8_t rgbGreen;
    uint8_t rgbRed;

public:
    RGBtriple();
    void SetRGB(uint8_t red, uint8_t green, uint8_t blue);
    void SetBlue(uint8_t blue);
    void SetGreen(uint8_t green);
    void SetRed(uint8_t red);
    uint8_t GetBlue() const;
    uint8_t GetGreen() const;
    uint8_t GetRed() const;
    friend std::ostream& operator<< (std::ostream& outstream, const RGBtriple& rgb);
    friend std::istream& operator>> (std::istream& instream, const RGBtriple& rgb);
};

