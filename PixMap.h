#pragma once
#include "RGBtriple.h"
#include <cstdint>
#include <iostream>
#include <vector>

class PixMap
{
public:

    void SetSize(int width, int height);
    void SetMonoArray(RGBtriple triple);
    void SetConcretePixel(int i, RGBtriple triple);
    void SetConcretePixel(int i, char blue, char green, char red);
    RGBtriple GetConcretePixel(int i);
    const RGBtriple& GetPixel(int i, int j);

    friend std::ostream& operator<< (std::ostream& outstream, PixMap& pixels);
    friend std::istream& operator>> (std::istream& instream, PixMap& pixels);

private:
    std::vector<RGBtriple> pixelArray;
    int m_rowCount;
    int m_colCount;
};

