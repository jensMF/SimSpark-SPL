/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: perceptor.h,v 1.7.10.1 2007/05/31 14:17:03 jboedeck Exp $

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
#ifndef OXYGEN_PERCEPTOR_H
#define OXYGEN_PERCEPTOR_H

#include <oxygen/sceneserver/basenode.h>
#include <oxygen/gamecontrolserver/baseparser.h>

namespace oxygen
{

class Perceptor : public oxygen::BaseNode
{
public:

    Perceptor();

    /*!  This is called by agents to trigger the percept event
      implemented by this perceptor. The perceptor can return data
      through the PredicateList which is passed as a parameter.
      \return true, if valid data is available and false otherwise.
    */
    virtual bool Percept(boost::shared_ptr<PredicateList> predList) = 0;

    //! set / change predicate name (for example for debugging purposes)
    void SetPredicateName(const std::string& my_name);

    /** get the interval cycle of the perceptor */
    unsigned int GetInterval() const;

    /** set the interval cycle of the perceptor */
    void SetInterval(unsigned int i);

protected:
    //! the predicate name
    std::string mPredicateName;

    //! the interval cycle of the perceptor
    unsigned int mInterval;
};

DECLARE_ABSTRACTCLASS(Perceptor);

} // namespace oxygen

#endif //OXYGEN_PERCEPTOR_H
