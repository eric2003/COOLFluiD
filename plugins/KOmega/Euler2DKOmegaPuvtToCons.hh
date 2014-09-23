#ifndef COOLFluiD_Physics_KOmega_Euler2DKOmegaPuvtToCons_hh
#define COOLFluiD_Physics_KOmega_Euler2DKOmegaPuvtToCons_hh

//////////////////////////////////////////////////////////////////////////////

#include "Framework/VarSetTransformer.hh"
#include "Framework/MultiScalarTerm.hh"
#include "NavierStokes/EulerTerm.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Physics {

    namespace KOmega {

//////////////////////////////////////////////////////////////////////////////

/**
 * This class represents a transformer of variables from primitive
 * [p u v T K Omega] to conservative variables [rho rhoU rhoV rhoE rhoK rhoOmega]
 *
 * @author Thomas Wuilbaut
 *
 */
class Euler2DKOmegaPuvtToCons : public Framework::VarSetTransformer {
public:

  typedef Framework::MultiScalarTerm<Physics::NavierStokes::EulerTerm> EulerKOmegaTerm;

  /**
   * Constructor
   */
  Euler2DKOmegaPuvtToCons(Common::SafePtr<Framework::PhysicalModelImpl> model);

  /**
   * Default destructor
   */
  ~Euler2DKOmegaPuvtToCons();
  
  /**
   * Transform a state into another one
   */
  void transform(const Framework::State& state, Framework::State& result);
  
  /**
   * Transform a state into another one from reference precomputed
   * values (physical data)associated to the given state
   */
  void transformFromRef(const RealVector& data, Framework::State& result);
  
private:

  /// acquaintance of the PhysicalModel
  Common::SafePtr<EulerKOmegaTerm> _model;

}; // end of class Euler2DKOmegaPuvtToCons

//////////////////////////////////////////////////////////////////////////////

    } // namespace KOmega

  } // namespace Physics

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_Physics_KOmega_Euler2DKOmegaPuvtToCons_hh
