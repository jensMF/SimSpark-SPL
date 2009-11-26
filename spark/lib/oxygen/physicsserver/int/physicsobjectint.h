/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: space.h 102 2009-11-18 07:24:29Z a-held $

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

#ifndef OXYGEN_PHYSICSOBJECTINT_H
#define OXYGEN_PHYSICSOBJECTINT_H

#include <boost/smart_ptr/shared_ptr.hpp>
#include <oxygen/physicsserver/ode/odewrapper.h>
#include <oxygen/sceneserver/basenode.h>
#include <oxygen/oxygen_defines.h>

namespace oxygen
{
class World;
class Space;

class OXYGEN_API PhysicsObjectInt : public BaseNode
{

public:
    PhysicsObjectInt(){};
    virtual ~PhysicsObjectInt(){};
    
    virtual dWorldID GetWorldID() = 0;
    virtual dSpaceID FindSpaceID() = 0;
    virtual dSpaceID GetParentSpaceID() = 0;
    virtual void ConvertRotationMatrix(const salt::Matrix& rot, dMatrix3& matrix) = 0;
    virtual void ConvertRotationMatrix(const dReal* matrix, salt::Matrix& rot) const = 0;
    virtual void DestroyPhysicsObject() = 0;
    
    boost::shared_ptr<Scene> scene;
    boost::shared_ptr<Space> space;
    boost::shared_ptr<World> world;
};

} //namespace oxygen

#endif //OXYGEN_PHYSICSOBJECTINT_H
