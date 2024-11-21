#ifndef LIGHTNESSMATRIXCREATOR_H
#define LIGHTNESSMATRIXCREATOR_H

#include "Bitmap.h"
#include "ILightnessMatrixCreator.h"


class LightnessMatrixCreator : public ILightnessMatrixCreator
{
public:
    LightnessMatrixCreator(Bitmap image) :
        m_image(image)
    {
    }

    Matrix<double> create() override;
private:
    Bitmap m_image;
};

#endif // LIGHTNESSMATRIXCREATOR_H
