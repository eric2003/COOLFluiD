// Copyright (C) 2012 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "NullSourceVarSet.hh"
#include "Environment/ObjectProvider.hh"
#include "Framework/Framework.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Framework {

//////////////////////////////////////////////////////////////////////////////

Environment::ObjectProvider<NullSourceVarSet,
               SourceVarSet,
               FrameworkLib,
               1>
nullSourceVarSetProvider("Null");

//////////////////////////////////////////////////////////////////////////////

NullSourceVarSet::NullSourceVarSet(const std::string& name) :
SourceVarSet(name)
{
}

//////////////////////////////////////////////////////////////////////////////

NullSourceVarSet::~NullSourceVarSet()
{
}

//////////////////////////////////////////////////////////////////////////////

void NullSourceVarSet::getLinearSourceCoefs(const Framework::State& state,
                                            const RealVector& normals,
                                            RealMatrix& coef)
{
}

//////////////////////////////////////////////////////////////////////////////

void NullSourceVarSet::getIndepSourceCoefs(const Framework::State& state,
                                           const RealVector& normals,
                                           RealVector& coef)
{
}

//////////////////////////////////////////////////////////////////////////////

void NullSourceVarSet::getLinearSourceCoefs(const Framework::State& state,
                                            RealMatrix& coef)
{
}

//////////////////////////////////////////////////////////////////////////////

void NullSourceVarSet::getIndepSourceCoefs(const Framework::State& state,
                                           RealVector& coef)
{
}

//////////////////////////////////////////////////////////////////////////////

} // namespace Framework
} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////
