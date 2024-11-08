#include "AsciiArt.h"
#include "Bitmap.h"
#include "Luminance.h"
#include "symbols.h"
#include "mymatrix.h"
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
}

Matrix<double> CreateLightnessMatrix(Bitmap& image, Matrix<double>& matrix)
{
    for (int row = 0; row < matrix.getRows(); ++row)           // for rows
    {
        for (int col = 0; col < matrix.getCols(); col++)  // for elements
        {
            const auto& pixel = image.GetPixel(row, col);    // get pixel
            const auto lightness = FindPerceivedLightness(pixel.GetRed(),    // find lightness of pixel
                pixel.GetGreen(),
                pixel.GetBlue());
            matrix(row, col) = std::max(lightness, 0.0);             // set matrix of lightnesses
        }
    }
    return matrix;
}

Matrix<double> ChooseQuality(Matrix<double>& matrix_in, int quality)
{
    if (quality == SYMBOL_QUALITY) {}
    else if (quality < 1 || quality > 10) {
        throw std::exception("\x1B[36mQuality must be from 1 to 10\033[0m\t\t\n\x1B[33mCritical error\033[0m\t\t");
    }

    Matrix<double> matrix_out;
    unsigned row = 0, col = 0;
    double avg_lightness = 0;

    for (Matrix<double>::iterator mi(matrix_in, quality); !mi.checkFullDone(); ) {

        avg_lightness = matrix_in.countAvg(mi);
        matrix_out.push(row, col, avg_lightness);
        mi++;
        col++;
        if (mi.checkRowDone()) {
            col = 0;
            row++;
            mi.unsetRowDone();
        }
    }
    return matrix_out;
}

void setSymbols(std::string& symbols, std::vector<char>& symbolArray, std::vector<double>& symbolVolume)
{
    for (auto symbol : symbols)
    {
        auto check = std::find(symbolArray.begin(), symbolArray.end(), symbol) ;
        if (check != symbolArray.end()) continue;
        QChar qsymbol = symbol;
        QString character(qsymbol);
        drawSymbol(character);

        Bitmap symbolImage;

        if (!symbolImage.ReadBMP("symbol.bmp")) {    // read image from file.bmp
            throw std::exception("\xB[32mCannot read symbol\033[0m\t\t\n\x1B[33mCritical error\033[0m\t\t");
        }
        const auto& symbolBi = symbolImage.GetBitmapInfo();

        Matrix<double> symbolLightnessMatrix(symbolBi.GetHeight(), symbolBi.GetWidth());
        symbolLightnessMatrix = CreateLightnessMatrix(symbolImage, symbolLightnessMatrix);

        Matrix<double> symbolAvgLM = ChooseQuality(symbolLightnessMatrix, SYMBOL_QUALITY);

        symbolArray.push_back(symbol);
        symbolVolume.push_back(symbolAvgLM(0,0));
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
    double volumeCurrent = 100;
    for (auto& i : symbolVolume) {
        i = volumeCurrent;
        volumeCurrent -= volumeStep;
    }
    symbolVolume.at(0) = 100;
    auto& endpoint = symbolVolume.back();
    endpoint = 0;
}

void configureSymbols(std::string& symbols, std::vector<char>& symbolArray, std::vector<double>& symbolVolume)
{
    setSymbols(symbols, symbolArray,symbolVolume);
    sortSymbols(symbolArray, symbolVolume);
    setLightnessSymbols(symbolArray, symbolVolume);
}

Matrix<char> LightnessToAscii(Matrix<double>& matrix, std::vector<char>& symbolArray, std::vector<double>& symbolVolume)
{
    // output matrix
    Matrix<char> matrix_ascii;

    for (int row = 0; row < matrix.getRows(); row++)   // for rows
    {
        double current_pixel;
        double correction = 0;
        for (int col = 0, pos = symbolVolume.size() - 1; col < matrix.getCols(); col++, pos = symbolVolume.size() - 1)    // for elems
        {
            current_pixel = matrix(row, col) + correction;
            while(current_pixel>symbolVolume[pos])
                pos--;
            matrix_ascii.push(row, col, symbolArray[pos]);      // add character to row
            correction = current_pixel - symbolVolume[pos];
        }
    }
    return matrix_ascii;
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
        //std::vector<std::vector<double>> matrix(bitmapInfo.GetHeight(), std::vector<double>(bitmapInfo.GetWidth(), 0));
        //matrix = CreateLightnessMatrix(image, matrix);

        Matrix<double> matrix(bitmapInfo.GetHeight(), bitmapInfo.GetWidth());
        matrix = CreateLightnessMatrix(image, matrix);


        // ------------- average lightness by squares -------------
        Matrix<double> matrix_avg = ChooseQuality(matrix, quality);

        // ------------- character selection --------------
       // std::sort(symbols.begin(), symbols.end());

        std::vector<char> symbolArray{};
        std::vector<double> symbolVolume{};
        configureSymbols(symbols, symbolArray, symbolVolume);

        // ---------------- Change lightness to ascii ----------
        Matrix<char> matrix_ascii;
        matrix_ascii = LightnessToAscii(matrix_avg, symbolArray, symbolVolume);
        
        result = matrix_ascii.toString();
        //matrix_ascii.print();

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
