/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-
   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2003 Koblenz University
   $Id: rendercontrol.h,v 1.1 2004/04/25 16:57:34 rollmark Exp $

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
#ifndef KEROSIN_RENDERCONTROL_H
#define KEROSIN_RENDERCONTROL_H

#include <oxygen/simulationserver/simcontrolnode.h>

namespace kerosin
{
    class RenderServer;
    class OpenGLServer;

/** \class RenderControl is a SimControlNode that renders the current
    scene and pumps the SDL event loop at the end of each simulation
    cycle, counting the total number of frames rendered
*/
class RenderControl : public oxygen::SimControlNode
{
public:
    RenderControl();
    virtual ~RenderControl();

    /** returns the total number of rendered frames */
    int GetFramesRendered();

    /** renders the scene at the end of each simulation cycle */
    virtual void EndCycle();

protected:
    virtual void OnLink();
    virtual void OnUnlink();

protected:
    /** cached reference to the RenderServer */
    boost::shared_ptr<kerosin::RenderServer> mRenderServer;

    /** cached reference to the OpenGLServer */
    boost::shared_ptr<kerosin::OpenGLServer> mOpenGLServer;

    /** total frames rendered */
    int mFramesRendered;
};

DECLARE_CLASS(RenderControl);

} // namespace kerosin

#endif // KEROSIN_RENDERCONTROL_H
