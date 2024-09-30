#include "Luminance.h"
#include <math.h>

// https://stackoverflow.com/questions/596216/formula-to-determine-perceived-brightness-of-rgb-color
// 17.08.2024
// Answer of Myndex, "The Accepted answer is incorrect"

double FindPerceivedLightness(uint8_t red, uint8_t green, uint8_t blue)
{
    double colorRed = red / 255.0, colorGreen = green / 255.0, colorBlue = blue / 255.0;
    return LumiToLstar(ColorLinear(colorRed) * 0.2126 + ColorLinear(colorGreen) * 0.7152 + ColorLinear(colorBlue) * 0.0722);
}

inline double LumiToLstar(double luminance)
{
    if (luminance <= 216 / 24389) return luminance * 903.3;
    else return pow(luminance, (1.0 / 3.0)) * 116.0 - 16.0;
}

inline double ColorLinear(double color)
{

    if (color <= 0.4045) return color / 12.92;
    else return pow(((color + 0.055) / 1.055), 2.4);
}
