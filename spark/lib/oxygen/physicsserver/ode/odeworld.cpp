/* -*- mode: c++ -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2003 Koblenz University
   $Id: world.cpp 3 2008-11-21 02:38:08Z hedayat $

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

#include <oxygen/physicsserver/ode/odeworld.h>
#include <oxygen/physicsserver/space.h>
#include <oxygen/sceneserver/scene.h>

using namespace boost;
using namespace oxygen;
using namespace salt;

ODEWorld::ODEWorld() : WorldInt()
{
}

long ODEWorld::GetWorldID() const
{
  return mWorldID;
}

void ODEWorld::SetGravity(const Vector3f& gravity)
{
  dWorldSetGravity((dWorldID) mWorldID,
                   gravity.x(),
                   gravity.y(),
                   gravity.z()
                   );
}

salt::Vector3f ODEWorld::GetGravity() const
{
  dVector3 dGravity;
  dWorldGetGravity((dWorldID) mWorldID,dGravity);
  return Vector3f(dGravity[0],dGravity[1],dGravity[2]);
}

void ODEWorld::SetERP(float erp)
{
  dWorldSetERP((dWorldID) mWorldID, erp);
}

float ODEWorld::GetERP() const
{
  return dWorldGetERP((dWorldID) mWorldID);
}

void ODEWorld::SetCFM(float cfm)
{
  dWorldSetCFM((dWorldID) mWorldID, cfm);
}

float ODEWorld::GetCFM() const
{
  return dWorldGetCFM((dWorldID) mWorldID);
}

void ODEWorld::Step(float deltaTime)
{
  dWorldStep((dWorldID) mWorldID, deltaTime);
}

bool ODEWorld::GetAutoDisableFlag() const
{
  return (dWorldGetAutoDisableFlag((dWorldID) mWorldID) == 1);
}

void ODEWorld::SetAutoDisableFlag(bool flag)
{
  dWorldSetAutoDisableFlag((dWorldID) mWorldID, static_cast<int>(flag));
}

void ODEWorld::SetContactSurfaceLayer(float depth)
{
  dWorldSetContactSurfaceLayer((dWorldID) mWorldID, depth);
}

float ODEWorld::GetContactSurfaceLayer() const
{
  return dWorldGetContactSurfaceLayer((dWorldID) mWorldID);
}

void ODEWorld::CreateWorld()
{
  mWorldID = (long) dWorldCreate();
}

void ODEWorld::DestroyWorld()
{
  dWorldDestroy((dWorldID) mWorldID);
  mWorldID = 0;
}
