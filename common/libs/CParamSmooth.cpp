//
//  CParamSmooth.cpp
//
//  Author: alexirae@gmail.com
//  from musicdsp.org archives
//
#include "CParamSmooth.h"
#include <math.h>

#define c_twoPi 6.283185307179586476925286766559f

CParamSmooth::CParamSmooth()
{
    a = exp(-c_twoPi / (5 * 0.001f * 44100));
    b = 1.0f - a;
    z = 0.0f;
}

CParamSmooth::CParamSmooth(float smoothingTimeInMs, float sampleRate)
{
    a = exp(-c_twoPi / (smoothingTimeInMs * 0.001f * sampleRate));
    b = 1.0f - a;
    z = 0.0f;
}

void CParamSmooth::init(float smoothingTimeInMs, float sampleRate)
{
    a = exp(-c_twoPi / (smoothingTimeInMs * 0.001f * sampleRate));
    b = 1.0f - a;
    z = 0.0f;
}

double CParamSmooth::process(double in)
{
    z = (in * b) + (z * a);
    return z;
}
    
