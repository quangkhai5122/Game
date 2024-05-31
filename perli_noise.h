#pragma once

#include <cmath>
#include <random>

using vector2 = std::pair<float, float>;
class PerlinNoise
{
public:
    PerlinNoise();
    PerlinNoise(unsigned _seed);
    ~PerlinNoise();
    float GetPerlinNoise2D(float x, float y); // With fractal brownian motion
private:
    float DotProduct(const vector2& V1, const vector2& V2);
    vector2 RandomGradient(int ix, int iy);
    float Interpolate(float t, float a1, float a2);
    float GetRawPerlinNoise2D(float x, float y);
    unsigned seed;
};