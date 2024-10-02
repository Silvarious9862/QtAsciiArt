#include "PixMap.h"


void PixMap::SetSize(int width, int height)
{
    RGBtriple rgb_null;
    pixelArray.resize(static_cast<size_t>(width) * height, rgb_null);
    m_colCount = width;
    m_rowCount = height;
    //std::cout << std::format("m_colCount: {}; m_rowCount: {}\n", m_colCount, m_rowCount);
}

void PixMap::SetMonoArray(RGBtriple triple)
{
    for (int i = 0; i < pixelArray.size(); i++)
    {
        pixelArray.at(i) = triple;
    }
    pixelArray.shrink_to_fit();
}

void PixMap::SetConcretePixel(int i, RGBtriple triple)
{
    pixelArray[i] = triple;
}

void PixMap::SetConcretePixel(int i, char blue, char green, char red)
{
    pixelArray[i].SetRGB(red, green, blue);
    RGBtriple triple = GetConcretePixel(i);
    pixelArray.at(i) = triple;
}

RGBtriple PixMap::GetConcretePixel(int i)
{
    return pixelArray.at(i);
}

const RGBtriple& PixMap::GetPixel(int row, int col)
{
    if (col >= m_colCount || row >= m_rowCount) {
        throw std::out_of_range("Pixel out of range");
    }

    const auto effectiveRow = m_rowCount - row - 1;
    return pixelArray.at(effectiveRow * m_colCount + col);
}

std::ostream& operator<< (std::ostream& outstream, PixMap& pixels)
{
    for (int i = 0; i < pixels.pixelArray.size(); i++)
    {
        outstream << pixels.GetConcretePixel(i);
    }
    return outstream;
}

std::istream& operator>> (std::istream& instream, PixMap& pixels)
{
    char tmpblue{}, tmpgreen{}, tmpred{};
    for (int i = 0; i < pixels.pixelArray.size(); i++)
    {
        instream.read((char*)&tmpblue, sizeof(tmpblue));
        pixels.pixelArray[i].SetBlue(tmpblue);
        instream.read((char*)&tmpgreen, sizeof(tmpgreen));
        pixels.pixelArray[i].SetGreen(tmpgreen);
        instream.read((char*)&tmpred, sizeof(tmpred));
        pixels.pixelArray[i].SetRed(tmpred);
    }
    return instream;
}
