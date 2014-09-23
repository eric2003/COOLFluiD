// Copyright (C) 2012 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "Petsc/ShellPreconditioner.hh"
#include "Petsc/PetscLSSData.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::Framework;
using namespace COOLFluiD::Common;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Petsc {
      
//////////////////////////////////////////////////////////////////////////////

ShellPreconditioner::ShellPreconditioner(const std::string& name) :
  Framework::MethodStrategy<PetscLSSData>(name)
{
}
    
//////////////////////////////////////////////////////////////////////////////

ShellPreconditioner::~ShellPreconditioner()
{
}

//////////////////////////////////////////////////////////////////////////////

    } // namespace Petsc

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////
