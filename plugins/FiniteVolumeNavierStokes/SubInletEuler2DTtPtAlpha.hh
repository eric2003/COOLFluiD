#ifndef COOLFluiD_Numerics_FiniteVolume_SubInletEuler2DTtPtAlpha_hh
#define COOLFluiD_Numerics_FiniteVolume_SubInletEuler2DTtPtAlpha_hh

//////////////////////////////////////////////////////////////////////////////

#include "FiniteVolume/FVMCC_BC.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Physics {
    namespace NavierStokes {
      class Euler2DVarSet;
    }
  }

  namespace Numerics {

    namespace FiniteVolume {

//////////////////////////////////////////////////////////////////////////////

  /**
   * This class represents a subsonic inlet command with the initial conditions given for tTotal, pTotal and alpha
   *
   * @author Mehmet Sarp Yalim
   * @author Andrea Lani
   *
   */
class SubInletEuler2DTtPtAlpha : public FVMCC_BC {
public:

  /**
   * Defines the Config Option's of this class
   * @param options a OptionList where to add the Option's
   */
  static void defineConfigOptions(Config::OptionList& options);

  /**
   * Constructor
   */
  SubInletEuler2DTtPtAlpha(const std::string& name);

  /**
   * Default destructor
   */
  ~SubInletEuler2DTtPtAlpha();

  /**
   * Set up private data and data of the aggregated classes
   * in this command before processing phase
   */
  void setup();

  /**
   * Apply boundary condition on the given face
   */
  void setGhostState(Framework::GeometricEntity *const face);

 private: // data

  /// physical model var set
  Common::SafePtr<Physics::NavierStokes::Euler2DVarSet> _varSet;

  /// physical model data
  RealVector _dataInnerState;

  /// physical model data
  RealVector _dataGhostState;

  /// total temperature
  CFreal     _tTotal;

  /// total pressure
  CFreal     _pTotal;

  /// alpha
  CFreal     _alpha;

}; // end of class SubInletEuler2DTtPtAlpha

//////////////////////////////////////////////////////////////////////////////

 } // namespace FiniteVolume

  } // namespace Numerics

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_Numerics_FiniteVolume_SubInletEuler2DTtPtAlpha_hh
