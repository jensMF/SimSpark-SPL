/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: transform.h,v 1.4 2003/11/14 14:05:53 fruit Exp $

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

   Transform


        NOTE:

        HISTORY:
                05.11.02 - MK
                        - Initial version

        TODO:

        TOFIX:
*/
#ifndef OXYGEN_TRANSFORM_H
#define OXYGEN_TRANSFORM_H

#include "basenode.h"

namespace oxygen
{

/** Transform is used to do local transforms relative to a parent node. */
class Transform : public BaseNode
{
    //
    // Functions
    //
public:
    Transform();
    ~Transform();

    // transformation related

    /** returns the local transform of this node */
    virtual const salt::Matrix&     GetLocalTransform()     const;

    /** returns the world transform of this node */
    virtual const salt::Matrix&     GetWorldTransform()     const;

    /** sets the local transform of this node */
    virtual void SetLocalTransform(const salt::Matrix &transform);

    /** sets the world transform of this node */
    virtual void SetWorldTransform(const salt::Matrix &transform);

    /** sets the local position of this node */
    void SetLocalPos(float x, float y, float z);

    /** sets the local position of this node */
    void SetLocalPos(const salt::Vector3f &pos);

protected:
    /** upon linkage, we have to update our world transform */
    virtual void OnLink();

private:
    /** updates hierarchical date (position, bounding volumes, etc..) */
    virtual void UpdateHierarchyInternal();

private:
    /** local transformation relative to parent */
    salt::Matrix    mLocalTransform;

    /** world transform generated by multiplying the parent's world transform with the local transform */
    salt::Matrix    mWorldTransform;
};

DECLARE_CLASS(Transform);

} //namespace oxygen
#endif //OXYGEN_TRANSFORM_H
