/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: odewrapper.h,v 1.3 2007/06/20 00:46:22 fruit Exp $

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
#ifndef OXYGEN_ODEWRAPPER_H
#define OXYGEN_ODEWRAPPER_H

#undef EXTERN
#undef HAVE_VPRINTF
#undef PACKAGE
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#undef PREFIX
#undef VERSION

#ifdef WIN32 

#ifdef copysignf
#undef copysignf
#endif

#ifdef copysign
#undef copysign
#endif

#endif // WIN32

#include <ode/ode.h>

#undef EXTERN
#undef HAVE_VPRINTF
#undef PACKAGE
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#undef PREFIX
#undef VERSION

#ifdef HAVE_CONFIG_H
#include <sparkconfig.h>
#endif

#endif // OXYGEN_ODEWRAPPER
