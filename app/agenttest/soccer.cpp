/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: soccer.cpp,v 1.1.2.1 2004/02/07 16:30:58 rollmark Exp $

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
#include "soccer.h"
#include <sstream>

using namespace zeitgeist;
using namespace std;
using namespace boost;
using namespace oxygen;
using namespace salt;

Soccer::Soccer() : Behavior()
{
  mTeamName = "unnamed";
  mSensationCount = 0;
}

Soccer::~Soccer()
{
}

void Soccer::InitAgent()
{
  GetLog()->Debug() << "sending init command\n";

  stringstream ss;
  ss << "A(init (unum " << getpid() << ") (teamname " << mTeamName << "))";

  mComm->PutOutput(ss.str().c_str());
}

void Soccer::CreateAgent()
{
  // use the create effector to setup the Sensors and Effectors
  GetLog()->Debug() << "creating agent\n";

  mComm->PutOutput("A(create)");
}

void Soccer::Kick(const float angle, const float power)
{
  GetLog()->Debug()
    << "kicking Ball"
    << " angle=" << angle
    << " power=" << power
    << "\n";

  stringstream ss;
  ss << "A(kick " << angle << " " << power << ")";

  mComm->PutOutput(ss.str());
}

void Soccer::Dash(const salt::Vector3f& dashVec)
{
  GetLog()->Debug()
    << "dashing ["
    << dashVec[0] << " "
    << dashVec[1] << " "
    << dashVec[2]
    << "]\n";

  stringstream ss;
  ss << "A(dash"
     << " " << dashVec[0]
     << " " << dashVec[1]
     << "  " << dashVec[2]
     << ")";

  mComm->PutOutput(ss.str());
}

void Soccer::CalcDashVec(const WorldModel::VisionSense& vision,
                         Vector3f& dashVec)
{
  dashVec[0] = 15 * vision.distance * gCos(gDegToRad(vision.theta)) *
    gSin(gDegToRad(90.0 - vision.phi));
  dashVec[1] = 15 * vision.distance * gSin(gDegToRad(vision.theta)) *
    gSin(gDegToRad(90.0 - vision.phi));
  dashVec[2] = 15 * vision.distance * gCos(gDegToRad(90.0 - vision.phi));
}

void Soccer::Think()
{
  GetLog()->Debug()
    << "received sensation " << mSensationCount << "\n";

  switch (mSensationCount)
    {
    case 0:
      CreateAgent();
      break;

    case 1:
      InitAgent();
      break;

    default:
      Behave();
    }

  ++mSensationCount;

  mComm->PutOutput(DoneThinkingMessage());
}
