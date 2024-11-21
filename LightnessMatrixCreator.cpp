#include "LightnessMatrixCreator.h"
#include "Luminance.h"
#include "mymatrix.h"

Matrix<double> LightnessMatrixCreator::create()
{
    const auto& bitmapInfo = m_image.GetBitmapInfo();
    Matrix<double> matrix(bitmapInfo.GetHeight(), bitmapInfo.GetWidth());
    for (int row = 0; row < matrix.getRows(); ++row)           // for rows
    {
        for (int col = 0; col < matrix.getCols(); col++)  // for elements
        {
            const auto& pixel = m_image.GetPixel(row, col);    // get pixel
            const auto lightness = FindPerceivedLightness(pixel.GetRed(),    // find lightness of pixel
                                                          pixel.GetGreen(),
                                                          pixel.GetBlue());
            matrix(row, col) = lightness;             // set matrix of lightnesses
        }
    }
    return matrix;
}
