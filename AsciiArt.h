#ifndef ASCIIART_H
#define ASCIIART_H
#include <vector>
#include "Bitmap.h"
#include <exception>
#include <chrono>

void PrintMatrixAscii(std::vector<std::vector <char>> const& matrix);
std::vector<std::vector<double>> CreateLightnessMatrix(Bitmap& image, std::vector<std::vector<double>>& matrix);
std::vector<std::vector<double>> ChooseQuality(std::vector<std::vector<double>>& matrix_in, std::vector<std::vector<double>>& matrix_out, int quality);
void setSymbols(std::string& symbols, std::vector<char>& symbolArray, std::vector<double>& symbolVolume);
void sortSymbols(std::vector<char>& symbolArray, std::vector<double>& symbolVolume);
void setLightnessSymbols(std::vector<char>& symbolArray, std::vector<double>& symbolVolume);
void configureSymbols(std::string& symbols, std::vector<char>& symbolArray, std::vector<double>& symbolVolume);
std::vector<std::vector<char>>   LightnessToAscii(std::vector<std::vector<double>>& matrix, std::vector<char> &symbolArray, std::vector<double> &symbolVolume);
std::string MakeAsciiArt(std::string path, int quality, std::string symbols);
std::string printResult(std::vector<std::vector<char>>& matrix_ascii);
#endif // ASCIIART_H
