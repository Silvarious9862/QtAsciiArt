#include "symbols.h"
#include <iostream>
#include "Bitmap.h"
#include "LightnessMatrixCreator.h"
#include "QualityDecorator.h"

bool drawSymbol(QString symbol)
{
    try {
        QImage img(15, 15, QImage::Format_RGB666);  // create an image
        img.setColorCount(24);  // set bitcount
        img.fill(Qt::black);    // fill black
        QPainter painter(&img);       // painter obj

        QFont font("Consolas", 25);
        painter.setFont(font);  // using font consolas 10

        QRectF rectangle;
        rectangle.setCoords(0,0,15,15);

        painter.setPen(Qt::white);  // color of symbol - white on black background
        painter.drawText(rectangle, Qt::AlignCenter, symbol);

        QString filename = "symbol.bmp";
        img.save(filename);
    }
    catch(std::exception& ex)
    {
        std::cerr << ex.what() << "\n";
        return false;
    }
    return true;
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

        LightnessMatrixCreator symbolDefaultCreator(symbolImage);
        QualityDecorator symbolQualityDecorator(symbolDefaultCreator, symbolImage.GetBitmapInfo().GetHeight());
        ILightnessMatrixCreator* symbolCreator = &symbolQualityDecorator;


        symbolArray.push_back(symbol);
        symbolVolume.push_back(symbolCreator->create()(0,0));
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
