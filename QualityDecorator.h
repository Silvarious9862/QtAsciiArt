#ifndef QUALITYDECORATOR_H
#define QUALITYDECORATOR_H

#include "ILightnessMatrixCreator.h"

class QualityDecorator : public ILightnessMatrixCreator
{
public:
    QualityDecorator(ILightnessMatrixCreator &creator, int quality) :
        m_creator(creator), m_quality(quality)
    {
    }
    Matrix<double> create() override;

private:
    ILightnessMatrixCreator &m_creator;
    int m_quality;
};

#endif // QUALITYDECORATOR_H
