/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: gmath.h,v 1.7 2003/11/14 14:05:54 fruit Exp $

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

static const float gPI          = ((float)3.1415926535);
static const float g2PI         = ((float)6.283185307);
static const float gHalfPI      = ((float)1.570796326794895);

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

// some math conversion functions
template <class TYPE>
f_inline float gDegToRad(TYPE deg)
{
    return ((float)deg) * (gPI / 180.0f);
}

template <class TYPE>
f_inline float gRadToDeg(TYPE rad)
{
    return ((float)rad) * (180.0f/gPI);
}

template <class TYPE>
f_inline bool   gInRange(const TYPE& val, const TYPE& low, const TYPE& high)
{
    return ((val>=low) && (val<=high));
}

} //namespace salt

#endif //SALT_GMATH_H
