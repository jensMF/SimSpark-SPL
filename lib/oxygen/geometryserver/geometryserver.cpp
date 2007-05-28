/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: geometryserver.cpp,v 1.2 2007/05/28 16:13:39 jboedeck Exp $

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
#include "geometryserver.h"
#include "meshimporter.h"
#include <zeitgeist/logserver/logserver.h>

using namespace oxygen;
using namespace zeitgeist;
using namespace salt;
using namespace std;
using namespace boost;

GeometryServer::GeometryServer() : Node()
{
}

GeometryServer::~GeometryServer()
{
}

void GeometryServer::OnLink()
{
    if (mChildren.size() == 0)
        {
            InitMeshImporter("oxygen/StdMeshImporter");
        }
}

bool GeometryServer::InitMeshImporter(const string& importerName)
{
    shared_ptr<MeshImporter> importer
        = shared_dynamic_cast<MeshImporter>(GetCore()->New(importerName));

    if (importer.get() == 0)
        {
            GetLog()->Error() << "(GeometryServer) ERROR: "
                              << "unable to create '" << importerName << "'\n";
            return false;
        }

    importer->SetName(importerName);
    AddChildReference(importer);

    GetLog()->Normal()
        << "(GeometryServer) MeshImporter '" << importerName << "' registered\n";

    return true;
}

shared_ptr<TriMesh> GeometryServer::GetMesh
(const string& name, const::ParameterList& parameter)
{
    // try a direct match
    string meshName = name;
    TMeshMap::iterator meshIter = mMeshMap.find(meshName);

    if (meshIter != mMeshMap.end())
        {
            return (*meshIter).second;
        }

    TLeafList importer;
    ListChildrenSupportingClass<MeshImporter>(importer);

    if (importer.size() == 0)
        {
            GetLog()->Error()
                << "(GeometryServer) Warning: no MeshImporter registered\n";

            return shared_ptr<TriMesh>();
        }

    // try to mangle the name
    for (
         TLeafList::iterator iter = importer.begin();
         iter != importer.end();
         ++iter
         )
        {
            shared_ptr<MeshImporter> importer =
                shared_static_cast<MeshImporter>(*iter);

            string str = importer->MangleName(name, parameter);

            if (str != meshName)
                {
                    meshName = str;
                    meshIter = mMeshMap.find(meshName);
                    if (meshIter != mMeshMap.end())
                        {
                            return (*meshIter).second;
                        }
                }
        }

    // try to import the mesh
    for (
         TLeafList::iterator iter = importer.begin();
         iter != importer.end();
         ++iter
         )
        {
            shared_ptr<MeshImporter> importer =
                shared_static_cast<MeshImporter>(*iter);

            shared_ptr<TriMesh> mesh = importer->ImportMesh(name,parameter);

            if (mesh.get() == 0 || mesh->GetVertexCount() == 0)
                {
                    continue;
                }

            string meshName = mesh->GetName();
            if (meshName == "")
                {
                    mesh->SetName(name);
                    meshName = name;
                }

            GetLog()->Normal()
                << "(GeometryServer) imported mesh '"
                << meshName << " with '"
                << importer->GetName() << "'\n";

            mMeshMap[meshName] = mesh;
            return mesh;
        }

    GetLog()->Error() << "(GeometryServer) ERROR: cannot import mesh '"
                      << name << "'\n";

    return shared_ptr<TriMesh>();
}

