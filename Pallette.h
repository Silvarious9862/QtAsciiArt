#pragma once
#include <iostream>

class Pallette
{
private:
    char palletteArray[1024];

public:
    Pallette();
    friend std::ostream& operator<< (std::ostream& outstream, const Pallette& pal);
};

