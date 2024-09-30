#ifndef ASCIIART_H
#define ASCIIART_H
#include <vector>
#include "Bitmap.h"
#include "mymatrix.h"
#include <exception>


void PrintMatrixAscii(std::vector<std::vector <char>> const& matrix);
Matrix<double> CreateLightnessMatrix(Bitmap& image, Matrix<double>& matrix);
Matrix<double> ChooseQuality(Matrix<double>& matrix_in, int quality = 5);
void setSymbols(std::string& symbols, std::vector<char>& symbolArray, std::vector<double>& symbolVolume);
void sortSymbols(std::vector<char>& symbolArray, std::vector<double>& symbolVolume);
void setLightnessSymbols(std::vector<char>& symbolArray, std::vector<double>& symbolVolume);
void configureSymbols(std::string& symbols, std::vector<char>& symbolArray, std::vector<double>& symbolVolume);
Matrix<char> LightnessToAscii(Matrix<double>& matrix, std::vector<char>& symbolArray, std::vector<double>& symbolVolume);
std::string MakeAsciiArt(std::string path, int quality, std::string symbols);
std::string printResult(std::vector<std::vector<char>>& matrix_ascii, int quality);
#endif // ASCIIART_H
