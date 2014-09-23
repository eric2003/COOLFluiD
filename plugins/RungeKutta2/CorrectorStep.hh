// Copyright (C) 2012 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef COOLFluiD_Numerics_RungeKutta2_CorrectorStep_hh
#define COOLFluiD_Numerics_RungeKutta2_CorrectorStep_hh

//////////////////////////////////////////////////////////////////////////////

#include "RK2Data.hh"
#include "Framework/DataSocketSink.hh"
#include "MathTools/RealVector.hh"
#include "Framework/State.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Numerics {

    namespace RungeKutta2 {

//////////////////////////////////////////////////////////////////////////////

  /// This class represents a NumericalCommand action to be
  /// sent to Domain to be executed in order to setup the MeshData.
class CorrectorStep : public RK2Com {
public:

  /// Constructor.
  explicit CorrectorStep(const std::string& name) :
    RK2Com(name),
    socket_rhs("rhs"),
    socket_u0("u0"),
    socket_updateCoeff("updateCoeff"),
    socket_upCoeff0("upCoeff0"),
    socket_states("states"),
    socket_volumes("volumes",false)
  {
  }

  /// Destructor.
  ~CorrectorStep()
  {
  }

  /// Execute Processing actions
  void execute();

  /// Returns the DataSocket's that this command needs as sinks
  /// @return a vector of SafePtr with the DataSockets
  virtual std::vector<Common::SafePtr<Framework::BaseDataSocketSink> > needsSockets();

protected:

  /// socket for Rhs
  Framework::DataSocketSink<
      CFreal> socket_rhs;

  /// socket for backup solution
  Framework::DataSocketSink<
      RealVector> socket_u0;

  /// socket for updateCoeff
  /// denominators of the coefficients for the update
  Framework::DataSocketSink<
      CFreal> socket_updateCoeff;

  /// socket for temporary storage of u
  Framework::DataSocketSink<
      CFreal> socket_upCoeff0;

  // handle to states
  Framework::DataSocketSink < Framework::State* , Framework::GLOBAL > socket_states;

  // handle to volumes
  Framework::DataSocketSink<CFreal> socket_volumes;

}; // class Setup

//////////////////////////////////////////////////////////////////////////////

    } // namespace RungeKutta2

  } // namespace Numerics

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_Numerics_RungeKutta2_CorrectorStep_hh

