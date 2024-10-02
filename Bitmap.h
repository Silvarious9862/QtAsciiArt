#pragma once
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"
#include "Pallette.h"
#include "PixMap.h"
#include <fstream>
#include <string>
#include <iostream>

class Bitmap
{
public:

    Bitmap(const char*path = "tmp.bmp");           
    void SetMonoBitmap(char red, char green, char blue);    // create a bitmap with one color fill
    void SaveAsBMP();       // save bitmap locally
    const BitmapInfoHeader& GetBitmapInfo() const { return bi; }
    const RGBtriple& GetPixel(int row, int col) { 
        return pixels.GetPixel(row, col); 
    }

    bool ReadBMP(std::string path); // read bmp from path 
    
private:
    BitmapInfoHeader bi;
    BitmapFileHeader bf;
    Pallette pal;
    RGBtriple rgb;
    PixMap pixels;
    std::fstream imageout;
    std::string path;

};

