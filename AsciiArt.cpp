#include "AsciiArt.h"
#include "Bitmap.h"
#include "Luminance.h"
#include "MatrixIterator.h"
#include "symbols.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define SYMBOL_QUALITY 15

class BitmapFileHeader;
class BitmapInfoHeader;
class Pallette;
class RGBtriple;
class PixMap;
class Bitmap;




void PrintMatrixAscii(std::vector<std::vector <char>> const& matrix)
{
    int row_number = 1;
    for (int i = 0; i < matrix.size(); ) {
        for (int j = 0; j < matrix[i].size(); ) {
            std::cout << std::setw(2) << matrix[i][j];
            j++;
        }
        //std::cout << "\t\x1B[36mR\033[0m" << row_number << "\n";
        std::printf("\t\x1B[36mR%d\033[0m\n", row_number);
        row_number++; i++;
    }
};

std::vector<std::vector<double>> CreateLightnessMatrix(Bitmap& image, std::vector<std::vector<double>>& matrix)
{
    for (int row = 0; row < matrix.size(); ++row)           // for rows
    {
        for (int col = 0; col < matrix[row].size(); col++)  // for elements
        {
            const auto& pixel = image.GetPixel(row, col);    // get pixel
            const auto lightness = FindPerceivedLightness(pixel.GetRed(),    // find lightness of pixel
                pixel.GetGreen(),
                pixel.GetBlue());
            matrix.at(row).at(col) = lightness;             // set matrix of lightnesses
        }
    }
    return matrix;
}

std::vector<std::vector<double>> ChooseQuality(std::vector<std::vector<double>>& matrix_in, std::vector<std::vector<double>>& matrix_out, int quality = 5)
{
    if (quality == SYMBOL_QUALITY) {

    }
    else if (quality < 1 || quality > 10) {
        throw std::exception("\x1B[36mQuality must be from 0 to 10\033[0m\t\t\n\x1B[33mCritical error\033[0m\t\t");
    }

    std::vector<double> row_one;
    double avg_lightness = 0;

    for (MatrixIterator mi(matrix_in, quality); !mi.CheckFullDone(); ) {
        avg_lightness = mi.CountAvg();
        row_one.emplace_back(avg_lightness);

        mi++;

        if (mi.CheckRowDone()) {
            matrix_out.emplace_back(row_one);
            row_one.clear();
            mi.UnsetRowDone();
        }
    }
    return matrix_out;
}

void setSymbols(std::string& symbols, std::vector<char>& symbolArray, std::vector<double>& symbolVolume)
{
    for (auto symbol : symbols)
    {
        QChar qsymbol = symbol;
        QString character(qsymbol);
        drawSymbol(character);

        Bitmap symbolImage;

        if (!symbolImage.ReadBMP("symbol.bmp")) {    // read image from file.bmp
            throw std::exception("\xB[32mCannot read symbol\033[0m\t\t\n\x1B[33mCritical error\033[0m\t\t");
        }
        const auto& symbolBi = symbolImage.GetBitmapInfo();

        std::vector<std::vector<double>> symbolLightnessMatrix(symbolBi.GetHeight(), std::vector<double>(symbolBi.GetWidth(), 0));
        symbolLightnessMatrix = CreateLightnessMatrix(symbolImage, symbolLightnessMatrix);

        std::vector<std::vector<double>> symbolAvgLM(0, std::vector<double>(0,0));
        symbolAvgLM = ChooseQuality(symbolLightnessMatrix, symbolAvgLM, SYMBOL_QUALITY);

        symbolArray.push_back(symbol);
        symbolVolume.push_back(symbolAvgLM[0][0]);
        remove("symbol.bmp");
    }
    symbolArray.shrink_to_fit();
    symbolVolume.shrink_to_fit();
}

void sortSymbols(std::vector<char>& symbolArray, std::vector<double>& symbolVolume)
{
    for(int startIndex = 0; startIndex < symbolVolume.size()-1 ; ++startIndex) {
        int smallestIndex = startIndex;
        for(int currentIndex = startIndex + 1; currentIndex < symbolVolume.size(); ++currentIndex ) {
            if (symbolVolume[currentIndex] < symbolVolume[smallestIndex]) {
                smallestIndex = currentIndex;
            }
        }
        std::swap(symbolArray[startIndex], symbolArray[smallestIndex]);
        std::swap(symbolVolume[startIndex], symbolVolume[smallestIndex]);
    }
}

void setLightnessSymbols(std::vector<char>& symbolArray, std::vector<double>& symbolVolume)
{
    // distribute brightness evenly
    double volumeStep = 100.0/symbolVolume.size();
    double volumeCurrent = volumeStep;
    for (auto& i : symbolVolume) {
        i = volumeCurrent;
        volumeCurrent += volumeStep;
    }
    symbolVolume.at(0) = 0;
    auto& endpoint = symbolVolume.back();
    endpoint = 100;
}

void configureSymbols(std::string& symbols, std::vector<char>& symbolArray, std::vector<double>& symbolVolume)
{
    setSymbols(symbols, symbolArray,symbolVolume);
    sortSymbols(symbolArray, symbolVolume);
    setLightnessSymbols(symbolArray, symbolVolume);
}

std::vector<std::vector<char>>LightnessToAscii(std::vector<std::vector<double>>&matrix, std::vector<char>& symbolArray, std::vector<double>& symbolVolume)
{
    // output matrix
    std::vector<std::vector<char>> matrix_ascii(0, std::vector<char>(0, 0));

    for (int row = 0; row < matrix.size(); row++)   // for rows
    {
        std::vector<char> row_one_ascii;
        double current_pixel;
        for (int col = 0, pos = 0; col < matrix[row].size(); col++, pos = 0)    // for elems
        {
            current_pixel = matrix.at(row).at(col);       // normalization from 0..100 to 0..1
            while(current_pixel>symbolVolume[pos]) pos++;
            row_one_ascii.emplace_back(symbolArray[pos]);      // add character to row
        }
        row_one_ascii.emplace_back('\n');
        row_one_ascii.shrink_to_fit();  // remove unused space in row
        matrix_ascii.emplace_back(row_one_ascii);   // add row to output matrix
    }
    return matrix_ascii;
}

std::string printResult(std::vector<std::vector<char>>& matrix_ascii)
{
    std::string output_str;
    for(auto& i : matrix_ascii){
        for(auto& j : i) {
            //output_str += ' ';
            output_str += j;

        }
    }
    return output_str;
}


std::string MakeAsciiArt(std::string path, int quality, std::string symbols)
{
//    std::cout << "START" << quality << std::endl;
    Bitmap image;           // create object of image
    std::string result = "";

    try {
        if (!image.ReadBMP(path)) {    // read image from file.bmp
            throw std::exception("\x1B[33mCritical error\033[0m\t\t");
        }

        const auto& bitmapInfo = image.GetBitmapInfo(); // check for 24bits bmp, if not - reject
        if (bitmapInfo.GetBitcount() != 24) {
            throw std::exception("\x1B[31mIT'S NOT A 24-bit IMAGE!\033[0m\t\t\n\x1B[33mCritical error\033[0m\t\t");
        }


        // ------------- counting lightness -----------
        std::vector<std::vector<double>> matrix(bitmapInfo.GetHeight(), std::vector<double>(bitmapInfo.GetWidth(), 0));
        matrix = CreateLightnessMatrix(image, matrix);


        // ------------- average lightness by squares -------------
        std::vector<std::vector<double>> matrix_avg(0, std::vector<double>(0, 0));
        matrix_avg = ChooseQuality(matrix, matrix_avg, quality);

        // ------------- character selection --------------
        std::sort(symbols.begin(), symbols.end());

        std::vector<char> symbolArray{};
        std::vector<double> symbolVolume{};
        configureSymbols(symbols, symbolArray, symbolVolume);

        // ---------------- Change lightness to ascii ----------
        std::vector<std::vector<char>> matrix_ascii(0, std::vector<char>(0, 0));
        matrix_ascii = LightnessToAscii(matrix_avg, symbolArray, symbolVolume);
        
        result = printResult(matrix_ascii);

    }
    catch (std::out_of_range& e) 
    {
        std::cerr << "out_of_range: " << e.what() << '\n';
    }
    catch (std::exception& errtext)
    {
        std::cerr << errtext.what() << "\n";
    } 
    catch (const char* text) 
    {
        std::cerr << text << '\n';
    }
    catch (...) 
    {
        std::cerr << "unknown exception\n";
    }


    return result;
}
