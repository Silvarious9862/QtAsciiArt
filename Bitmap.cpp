#include "Bitmap.h"

Bitmap::Bitmap(const char*path)
{
    bf.SetbfSize(bi);
    pixels.SetSize(bi.GetWidth(), bi.GetHeight());
    this->path = path;
}

Bitmap::Bitmap(const Bitmap &image)
{
    bi = image.bi;
    bf = image.bf;
    pal = image.pal;
    rgb = image.rgb;
    pixels = image.pixels;
    path = image.path;

}

void Bitmap::SetMonoBitmap(char red, char green, char blue)
{
    bi.SetBitCount(24);
    rgb.SetRGB(red, green, blue);
    pixels.SetMonoArray(rgb);
}

void Bitmap::SaveAsBMP()
{
    std::fstream imageout("out.bmp", std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
    try
    {
        if (!imageout.is_open()) throw "Cannot create file";
        imageout << bf << bi << pixels;
        if (imageout.fail()) throw "Cannot print in file";
        imageout.close();
        std::cout << "Saved successfully" << std::endl;
    }
    catch (char const* errorline)
    {
        std::cout << errorline << std::endl;
        imageout.close();
    }
}

bool Bitmap::ReadBMP(std::string path)
{
    this->path = path;
    std::fstream imagein(this->path, std::ios_base::in | std::ios_base::binary);
    try {
        if (!imagein.is_open()) {
            throw "\x1B[31mCannot open to read file\033[0m\t\t";
        }
        
        imagein >> bf;
        if (!this->bf.CheckBM()) {
            throw "\x1B[31mFile is not a BMP or corrupted\033[0m\t\t";
        }

        imagein >> bi; 
        pixels.SetSize(bi.GetWidth(), bi.GetHeight());
        imagein >> pixels;

        imagein.close();
    }
    catch (char const* errorline)
    {
        std::cout << errorline << std::endl;
        imageout.close();
        return false;
    }
    return true;
}
