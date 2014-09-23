// Copyright (C) 2012 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "Framework/NullMeshDataBuilder.hh"
#include "Environment/ObjectProvider.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::Common;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Framework {

//////////////////////////////////////////////////////////////////////////////

Environment::ObjectProvider<NullMeshDataBuilder,
			    MeshDataBuilder,
			    FrameworkLib, 
			    1>
nullMeshDataBuilderProvider("Null");

//////////////////////////////////////////////////////////////////////////////

NullMeshDataBuilder::NullMeshDataBuilder(const std::string& name) :
  MeshDataBuilder(name)
{
}

//////////////////////////////////////////////////////////////////////////////

NullMeshDataBuilder::~NullMeshDataBuilder()
{
}

//////////////////////////////////////////////////////////////////////////////

void NullMeshDataBuilder::releaseMemory()
{
  CFLog(VERBOSE, "NullMeshDataBuilder::releaseMemory()\n");
}

//////////////////////////////////////////////////////////////////////////////

void NullMeshDataBuilder::createTopologicalRegionSets()
{  
  CFLog(VERBOSE, "NullMeshDataBuilder::createTopologicalRegionSets()\n");
}

//////////////////////////////////////////////////////////////////////////////

void NullMeshDataBuilder::setMapGeoToTrs()
{
  CFLog(VERBOSE, "NullMeshDataBuilder::setMapGeoToTrs()\n");
}

//////////////////////////////////////////////////////////////////////////////

void NullMeshDataBuilder::setMaxNbStatesInCell()
{
  CFLog(VERBOSE, "NullMeshDataBuilder::setMaxNbStatesInCell()\n");
}

//////////////////////////////////////////////////////////////////////////////

void NullMeshDataBuilder::setMaxNbNodesInCell()
{
  CFLog(VERBOSE, "NullMeshDataBuilder::setMaxNbNodesInCell()\n");
}

//////////////////////////////////////////////////////////////////////////////

void NullMeshDataBuilder::setMaxNbFacesInCell()
{
  CFLog(VERBOSE, "NullMeshDataBuilder::setMaxNbFacesInCell()\n");
}

//////////////////////////////////////////////////////////////////////////////

} // namespace Framework

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

