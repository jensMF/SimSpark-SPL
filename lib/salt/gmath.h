/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: gmath.h,v 1.9 2004/12/17 20:21:27 rollmark Exp $

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/* this file contains some templated math functions and constants
 * visible in the salt namespace
 */
#ifndef SALT_GMATH_H
#define SALT_GMATH_H

// #ifdef HAVE_CONFIG_H
// #include <config.h>
// #endif

#include "defines.h"
#include <cmath>

namespace salt
{
#if 0
}
#endif

// better directly use the cmath constants
static const double gPI          = M_PI;   // was ((float)3.1415926535);
static const double g2PI         = 2*M_PI; // was ((float)6.283185307);
static const double gHalfPI      = M_PI_2; // was ((float)1.570796326794895);

template <typename TYPE>
f_inline TYPE gSqrt(const TYPE &v)
{
    return (TYPE)sqrt(v);
}

template <class TYPE>
f_inline TYPE gClamp(TYPE &val, TYPE min, TYPE max)
{
    if (val<min) val=min; if (val>max) val=max; return val;
}

template <class TYPE>
f_inline TYPE gMin(TYPE a, TYPE b)
{
    if (a<b) return a; return b;
}

template <class TYPE>
f_inline TYPE gMax(TYPE a, TYPE b)
{
    if (a>b) return a; return b;
}

template <class TYPE>
f_inline TYPE gFloor(TYPE a)
{
    return (TYPE)floor(a);
}

template <class TYPE>
f_inline TYPE   gCeil(TYPE a)
{
    return ceil(a);
}

template <class TYPE>
f_inline TYPE   gAbs(TYPE a)
{
    return (TYPE)fabs(a);
}

template <class TYPE>
f_inline TYPE   gNeg(TYPE a)
{
    return -a;
}

template <class TYPE>
f_inline TYPE gCos(TYPE a)
{
    return (TYPE)cos(a);
}

template <class TYPE>
f_inline TYPE   gSin(TYPE a)
{
    return (TYPE)sin(a);
}

template <class TYPE>
f_inline TYPE   gArcCos(TYPE a)
{
    return acos(a);
}

template <class TYPE>
f_inline TYPE   gArcSin(TYPE a)
{
    return asin(a);
}

template <class TYPE>
f_inline TYPE   gArcTan(TYPE a)
{
    return atan(a);
}

template <class TYPE>
f_inline TYPE   gArcTan2(TYPE a, TYPE b)
{
    return atan2(a, b);
}

template <class TYPE>
f_inline TYPE   gPow(TYPE a, TYPE b)
{
    return pow(a, b);
}

template <class TYPE>
f_inline void gSwap(TYPE &a, TYPE &b)
{
    TYPE temp = a;
    a = b;
    b = temp;
}

template <class TYPE>
f_inline int gSign(TYPE a)
{
    return a > 0 ? 1 : a < 0 ? -1 : 0;
}

// some math conversion functions
template <class TYPE>
f_inline TYPE gDegToRad(TYPE deg)
{
    return (static_cast<double>(deg)) * (M_PI / 180.0);
}

template <class TYPE>
f_inline TYPE gRadToDeg(TYPE rad)
{
    return (static_cast<TYPE>(rad)) * (180.0 / M_PI);
}

template <class TYPE>
f_inline bool   gInRange(const TYPE& val, const TYPE& low, const TYPE& high)
{
    return ((val>=low) && (val<=high));
}

template <class TYPE>
f_inline double gNormalizeDeg(TYPE angle)
{
    while (angle > 180)
        {
            angle -= 360;
        }

    while (angle < -180)
        {
            angle += 360;
        }

    return angle;
}

template <class TYPE>
f_inline double gNormalizeRad(TYPE angle)
{
    while (angle > M_PI)
        {
            angle -= (2*M_PI);
        }

    while (angle < -M_PI)
        {
            angle += (2*M_PI);
        }

    return angle;
}


} //namespace salt

#endif //SALT_GMATH_H
