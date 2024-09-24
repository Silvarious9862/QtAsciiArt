#pragma once
#include <iostream>

double FindPerceivedLightness(uint8_t red, uint8_t green, uint8_t blue);
inline double LumiToLstar(double luminance);
inline double ColorLinear(double color);
