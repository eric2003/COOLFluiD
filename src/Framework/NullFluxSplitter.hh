// Copyright (C) 2012 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef COOLFluiD_Framework_NullFluxSplitter_hh
#define COOLFluiD_Framework_NullFluxSplitter_hh

//////////////////////////////////////////////////////////////////////////////

#include "Framework/FluxSplitter.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Framework {

//////////////////////////////////////////////////////////////////////////////

/// This class represents the a Null flux splitter
/// @author Andrea Lani
template < typename METHODDATA >
class NullFluxSplitter : public Framework::FluxSplitter<METHODDATA> {
public:

  /// Constructor
  NullFluxSplitter(const std::string& name);

  /// Default destructor
  ~NullFluxSplitter();

  /// Set the solution variable set
  void setSolutionVarSet(Common::SafePtr<Framework::ConvectiveVarSet> solutionVarSet)
  {
    CFout << "NullFluxSplitter::setSolutionVarSet() called!" << "\n";
  }

  /// Set the update variable set
  void setUpdateVarSet(Common::SafePtr<Framework::ConvectiveVarSet> updateVarSet)
  {
    CFout << "NullFluxSplitter::setUpdateVarSet() called!" << "\n";
  }

  /// Set the diffusive variable set
  void setDiffusiveVarSet(Common::SafePtr<Framework::DiffusiveVarSet> diffusiveVarSet)
  {
    CFout << "NullFluxSplitter::setDiffusiveVarSet() called!" << "\n";
  }

  /// Compute the flux in the current face
  void computeFlux(RealVector& result)
  {
    CFout << "NullFluxSplitter::computeFlux() called!" << "\n";
  }

}; // end of class NullFluxSplitter

//////////////////////////////////////////////////////////////////////////////

  } // namespace Framework

} // namespace COOLFluiD

#include "NullFluxSplitter.ci"

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_Framework_NullFluxSplitter_hh
