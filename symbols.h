#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <QImage>
#include <QPainter>

bool drawSymbol(QString symbol);
void setSymbols(std::string& symbols, std::vector<char>& symbolArray, std::vector<double>& symbolVolume);
void sortSymbols(std::vector<char>& symbolArray, std::vector<double>& symbolVolume);
void setLightnessSymbols(std::vector<char>& symbolArray, std::vector<double>& symbolVolume);
void configureSymbols(std::string& symbols, std::vector<char>& symbolArray, std::vector<double>& symbolVolume);

#endif // SYMBOLS_H
