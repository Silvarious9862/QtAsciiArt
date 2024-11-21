#include "QualityDecorator.h"

Matrix<double> QualityDecorator::create()
{
    Matrix<double> matrixStd = m_creator.create();
    Matrix<double> matrixOut;
    unsigned row = 0, col = 0;
    double avg_lightness = 0;

    for (Matrix<double>::iterator mi(matrixStd, m_quality); !mi.checkFullDone(); ) {

        avg_lightness = matrixStd.countAvg(mi);
        matrixOut.push(row, col, avg_lightness);
        mi++;
        col++;
        if (mi.checkRowDone()) {
            col = 0;
            row++;
            mi.unsetRowDone();
        }
    }
    return matrixOut;
}
