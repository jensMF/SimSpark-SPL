/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: visionperceptor.h,v 1.3 2003/11/14 14:05:51 fruit Exp $

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
#ifndef KEROSIN_VISIONPERCEPTOR_H
#define KEROSIN_VISIONPERCEPTOR_H

/*!
        The VisionPerceptor class is used to filter visible visual aspects out
        of the scene graph.
*/

#include <oxygen/agentaspect/perceptor.h>

namespace kerosin
{

class VisionPerceptor : public oxygen::Perceptor
{
    //
    // functions
    //
public:
    /*
      Returns:
      "visibleObjects" as a TLeafList
    */
    virtual bool Percept(TDictionary &dictionary);
    /*
      Setup view direction
    */
    void SetViewDirection(const salt::Vector3f& dir)
    {
        mDir = dir;
    }
private:
    salt::Vector3f  mDir;
};

DECLARE_CLASS(VisionPerceptor);

}
#endif //KEROSIN_VISIONPERCEPTOR_H
