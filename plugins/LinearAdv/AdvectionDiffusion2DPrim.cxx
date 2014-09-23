// Copyright (C) 2012 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "LinearAdv/LinearAdv.hh"
#include "AdvectionDiffusion2DPrim.hh"
#include "Environment/ObjectProvider.hh"
#include "LinearAdv/LinearAdvTerm.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::Framework;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {
  namespace Physics {
namespace LinearAdv {

//////////////////////////////////////////////////////////////////////////////

Environment::ObjectProvider<AdvectionDiffusion2DPrim, DiffusiveVarSet,
	       LinearAdvModule, 2>
ad2DPrimProvider("AdvectionDiffusion2DPrim");

//////////////////////////////////////////////////////////////////////////////

AdvectionDiffusion2DPrim::AdvectionDiffusion2DPrim
(const std::string& name, Common::SafePtr<Framework::PhysicalModelImpl> model) :
  AdvectionDiffusion2DVarSet(name, model),
  _linearadvModel(model->getConvectiveTerm().d_castTo<LinearAdvTerm>())
{
}

//////////////////////////////////////////////////////////////////////////////

AdvectionDiffusion2DPrim::~AdvectionDiffusion2DPrim()
{
}

//////////////////////////////////////////////////////////////////////////////

void AdvectionDiffusion2DPrim::setGradientVars(const vector<RealVector*>& states,
					 const vector<RealVector*>& values,
					 const CFuint stateSize)
{
  const CFuint nbStates = stateSize;

   RealVector& u = *values[0];
  for (CFuint i = 0; i < nbStates; ++i) {
    const RealVector& state = *states[i];
    u[i] = state[0];
  }
}

//////////////////////////////////////////////////////////////////////////////

void AdvectionDiffusion2DPrim::setGradientState(const RealVector& state)
{
}
//////////////////////////////////////////////////////////////////////////////

} // namespace LinearAdv
  }
} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////
