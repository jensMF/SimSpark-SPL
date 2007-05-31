/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: createeffector.h,v 1.3.12.1 2007/05/31 14:17:04 jboedeck Exp $

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
#ifndef CREATEEFFECTOR_H
#define CREATEEFFECTOR_H

#include <oxygen/agentaspect/effector.h>

class CreateEffector : public oxygen::Effector
{
 public:
    CreateEffector();
    virtual ~CreateEffector() {};

    /** returns the name of the predicate this effector implements. */
    virtual std::string GetPredicate() { return "create"; }

    /** constructs an Actionobject, describing a predicate */
    virtual boost::shared_ptr<oxygen::ActionObject>
    GetActionObject(const oxygen::Predicate& predicate);

protected:
    /** realizes the action described by the ActionObject */
    virtual void PrePhysicsUpdateInternal(float deltaTime);
};

DECLARE_CLASS(CreateEffector);

#endif // CREATEEFFECTOR_H

