// Copyright (C) 2012 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "LinearAdv/LinearAdv.hh"
#include "LinearAdv2DPrim.hh"
#include "Framework/State.hh"
#include "Framework/PhysicalModel.hh"
#include "Environment/ObjectProvider.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::Framework;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Physics {
namespace LinearAdv {

//////////////////////////////////////////////////////////////////////////////

Environment::ObjectProvider<LinearAdv2DPrim, ConvectiveVarSet, LinearAdvModule, 1>
linearAdv2DPrimProvider("LinearAdv2DPrim");

//////////////////////////////////////////////////////////////////////////////

LinearAdv2DPrim::LinearAdv2DPrim(Common::SafePtr<BaseTerm> term) :
  LinearAdv2DVarSet(term)
{
  vector<std::string> names(1);
  names[0] = "u";
  setVarNames(names);
}

//////////////////////////////////////////////////////////////////////////////

LinearAdv2DPrim::~LinearAdv2DPrim()
{
}

//////////////////////////////////////////////////////////////////////////////

void LinearAdv2DPrim::getAverageAdvectionVector(RealVector& vec, const CFuint iVar) const
{
  const RealVector& linearData = getModel()->getPhysicalData();

  cf_assert(vec.size() == DIM_2D);

  vec[XX] = linearData[LinearAdvTerm::VX];
  vec[YY] = linearData[LinearAdvTerm::VY];
}

//////////////////////////////////////////////////////////////////////////////

void LinearAdv2DPrim::computeJacobians()
{
  const RealVector& linearData = getModel()->getPhysicalData();

  vector<RealMatrix>* const jacobians =
    PhysicalModelStack::getActive()->getImplementor()->getJacobians();

  (*jacobians)[XX](0,0) = linearData[LinearAdvTerm::VX];
  (*jacobians)[YY](0,0) = linearData[LinearAdvTerm::VY];
}

//////////////////////////////////////////////////////////////////////////////

void LinearAdv2DPrim::computeEigenValuesVectors(RealMatrix& rightEv,
                                            RealMatrix& leftEv,
                                            RealVector& eValues,
                                            const RealVector& normal)
{
  const RealVector& linearData =
    getModel()->getPhysicalData();

  const CFreal avU   = linearData[LinearAdvTerm::VX];
  const CFreal avV   = linearData[LinearAdvTerm::VY];
  const CFreal nx = normal[XX];
  const CFreal ny = normal[YY];

  rightEv = 1.0;
  leftEv = 1.0;

  eValues[0] = avU * nx + avV * ny;
}

//////////////////////////////////////////////////////////////////////////////

void LinearAdv2DPrim::computeScalarJacobian(const RealVector& normal,
                                     RealVector& jacob)
{
  const RealVector& linearData = getModel()->getPhysicalData();

  jacob[0] = linearData[LinearAdvTerm::VX]*normal[XX] +
             linearData[LinearAdvTerm::VY]*normal[YY];
}

//////////////////////////////////////////////////////////////////////////////

void LinearAdv2DPrim::computePhysicalData(const State& state,
                                      RealVector& data)
{
  const RealVector& linearData =
    getModel()->getPhysicalData();
  
  data[LinearAdvTerm::u] = state[0];
  data[LinearAdvTerm::VX] = linearData[LinearAdvTerm::VX];
  data[LinearAdvTerm::VY] = linearData[LinearAdvTerm::VY];
}

//////////////////////////////////////////////////////////////////////////////

void LinearAdv2DPrim::computeStateFromPhysicalData(const RealVector& data,
					      State& state)
{
  state[0] = data[0];
}


//////////////////////////////////////////////////////////////////////////////

} // namespace LinearAdv
  }
} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////
