/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: spherecollider.h,v 1.5 2003/11/14 14:05:53 fruit Exp $

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
#ifndef OXYGEN_SPHERECOLLIDER_H
#define OXYGEN_SPHERECOLLIDER_H

#include "collider.h"

namespace oxygen
{

/** SphereCollider encapsulates an ODE sphere geometry object.
 */
class SphereCollider : public Collider
{
    //
    // Functions
    //
public:
    SphereCollider();

    /** sets the radius of the managed ODE sphere geom */
    void SetRadius(float r);

protected:
    /** constructs a default sphere with a radius of 1 */
    virtual bool ConstructInternal();
};

DECLARE_CLASS(SphereCollider);

} //namespace oxygen

#endif //OXYGEN_SPHERECOLLIDER_H
