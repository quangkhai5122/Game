// Credit: wikipedia

#include "perli_noise.h"
#include <ctime>

PerlinNoise::PerlinNoise()
{
    srand(time(NULL));
    seed = rand();
}
PerlinNoise::PerlinNoise(unsigned _seed)
{
    seed = _seed;
}
PerlinNoise::~PerlinNoise() {}

float PerlinNoise::DotProduct(const vector2& V1, const vector2& V2)
{
    return V1.first * V2.first + V1.second * V2.second;
}


vector2 PerlinNoise::RandomGradient(int ix, int iy) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; // rotation width
    unsigned a = ix * seed, b = iy * seed;
    a *= 3284157443; b ^= a << s | a >> w - s;
    b *= 1911520717; a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
    vector2 v;
    v.first = cos(random);
    v.second = sin(random);
    return v;
}


float PerlinNoise::Interpolate(float w, float a0, float a1)
{
    // return a0 + (a1 - a0) * w;

    // Use this cubic interpolation [[Smoothstep]] instead, for a smooth appearance:
    // return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;

    // Use [[Smootherstep]] for an even smoother result with a second derivative equal to zero on boundaries:
    return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
}

float PerlinNoise::GetRawPerlinNoise2D(float x, float y)
{
    int X = ((int)floor(x));
    int Y = ((int)floor(y));

    float xf = x - (float)X;
    float yf = y - (float)Y;

    vector2 topRight = std::make_pair(xf - 1.0, yf - 1.0);
    vector2 topLeft = std::make_pair(xf, yf - 1.0);
    vector2 bottomRight = std::make_pair(xf - 1.0, yf);
    vector2 bottomLeft = std::make_pair(xf, yf);

    float dotTopRight = DotProduct(topRight, RandomGradient(X + 1, Y + 1));
    float dotTopLeft = DotProduct(topLeft, RandomGradient(X, Y + 1));
    float dotBottomRight = DotProduct(bottomRight, RandomGradient(X, Y + 1));
    float dotBottomLeft = DotProduct(bottomLeft, RandomGradient(X, Y));

    float u = xf;
    float v = yf;

    return Interpolate(u,
        Interpolate(v, dotBottomLeft, dotTopLeft),
        Interpolate(v, dotBottomRight, dotTopRight));
    // return value approximately in [-1.0, 1.0]
    // due to float imprecision
}

float PerlinNoise::GetPerlinNoise2D(float x, float y)
{
    float ret = 0;
    float magnitude = 2;
    float frequency = 0.08;
    // With fractal brownian motion - only 2 here - increase for terrain complexity
    for (int o = 0; o < 2; o++)
    {
        float tmp = magnitude * GetRawPerlinNoise2D(x * frequency, y * frequency);
        ret += tmp;
        magnitude /= 2;
        frequency += frequency;
    }

    // scale from [-1, 1] to [0, 1]
    // Just approximately in that range (due to float imprecision)
    ret += 1.0;
    ret /= 2;

    return ret;
}