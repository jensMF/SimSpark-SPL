/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: contactjointhandler.cpp,v 1.2.2.1 2004/03/27 11:40:31 rollmark Exp $

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
#include "contactjointhandler.h"
#include "collider.h"
#include "world.h"
#include "space.h"

#include <zeitgeist/logserver/logserver.h>

using namespace oxygen;
using namespace boost;

ContactJointHandler::ContactJointHandler() : CollisionHandler()
{
  // set up default contact surface parameters
  mSurfaceParameter.mode = dContactBounce;
  mSurfaceParameter.mu = dInfinity;
  mSurfaceParameter.bounce = 0.8f;
  mSurfaceParameter.bounce_vel = 2.0f;
}

ContactJointHandler::~ContactJointHandler()
{
}

void
ContactJointHandler::HandleCollision(shared_ptr<Collider> collidee, dContact& contact)
{
  if (
      (mCollider.get() == 0) ||
      (mWorld.get() == 0) ||
      (mSpace.get() == 0)
      )
      {
          return;
      }

  // check if the collidee has a ContactJointHandler registered to it
  if (collidee->FindChildSupportingClass<ContactJointHandler>().get() == 0)
      {
          return;
      }

  dBodyID myBody = dGeomGetBody(mCollider->GetODEGeom());
  dBodyID collideeBody = dGeomGetBody(collidee->GetODEGeom());

  // to create a contact joint it we must have at least one body to
  // attach it to.
  if (
      (myBody == 0) &&
      (collideeBody == 0)
      )
    {
      return;
    }

  // fill in the surface parameters
  contact.surface = mSurfaceParameter;

  // create the contact joint and attach it to the body
  dJointID joint = dJointCreateContact
    (mWorld->GetODEWorld(), mSpace->GetODEJointGroup(), &contact);

  dJointAttach (joint, myBody, collideeBody);
 }

void
ContactJointHandler::SetSurfaceParameter(const dSurfaceParameters& surface)
{
  mSurfaceParameter = surface;
}
