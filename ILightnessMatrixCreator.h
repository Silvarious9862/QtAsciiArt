#ifndef ILIGHTNESSMATRIXCREATOR_H
#define ILIGHTNESSMATRIXCREATOR_H

#include "mymatrix.h"

class ILightnessMatrixCreator
{
public:
    virtual ~ILightnessMatrixCreator() = default;
    virtual Matrix<double> create() = 0;
};

#endif // ILIGHTNESSMATRIXCREATOR_H
