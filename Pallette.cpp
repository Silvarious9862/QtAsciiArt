#include "Pallette.h"

Pallette::Pallette()
{
    for (int i = 0; i < 1024; i++)
    {
        palletteArray[i] = 0;
    }
}

std::ostream& operator<< (std::ostream& outstream, const Pallette& pal)
{
    return outstream << pal.palletteArray;
}