#ifndef COOLFluiD_Numerics_FiniteElement_GalerkinStructMech2DDispDiffEntity_hh
#define COOLFluiD_Numerics_FiniteElement_GalerkinStructMech2DDispDiffEntity_hh

//////////////////////////////////////////////////////////////////////////////

#include "DiffusiveEntity.hh"
#include "Framework/State.hh"
#include "Framework/GeometricEntity.hh"
#include "MathTools/RealMatrix.hh"
#include "StructMech/StructMech2DDiffusiveDisp.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {
  namespace Numerics {
    namespace FiniteElement {

//////////////////////////////////////////////////////////////////////////////

  /**
   * This class represents a IntegrableEntity for a Galerkin Diffusive Term
   *
   * @author Thomas Wuilbaut
   */

class GalerkinStructMech2DDispDiffEntity : public DiffusiveEntity {

public:

  /// Default constructor without arguments
  GalerkinStructMech2DDispDiffEntity(const std::string& name);

  /// Default destructor
  ~GalerkinStructMech2DDispDiffEntity();

  /**
   * Setup the strategy
   */
  virtual void setup();

  /**
   * Overloading of operator()
   */
  virtual RealMatrix& operator()();

private: // helper functions

  /**
   * Modify the Stiffness for improving mesh movement
   */
  void modifyStiffness(Framework::GeometricEntity* const geo);

  /**
   * Resets the Stiffness coefs to their original value
   */
  void resetStiffness();

private:

  /// Variable Set
  Common::SafePtr<Physics::StructMech::StructMech2DDiffusiveDisp> _structDiffVarSet;

  /// Anisotropy Flag
  bool _isAnisotropic;

  /// Non Linear Flag
  bool _isNonLinear;

  /// StructMech is used for the movement of the mesh?
  bool _meshMovement;
  std::string _meshMovementMethod;

  /// constant of the constitutive matrix
  CFreal _c11;
  CFreal _c12;
  CFreal _c21;
  CFreal _c22;
  CFreal _c16;
  CFreal _c26;
  CFreal _c61;
  CFreal _c62;
  CFreal _c66;

  /// constant lame coefs
  CFreal _lambda;
  CFreal _mu;

  /// Stiffness matrix
  RealMatrix _stiffness;

}; // end of class GalerkinStructMech2DDispDiffEntity

//////////////////////////////////////////////////////////////////////////////

    } // namespace FiniteElement
  } // namespace Numerics
} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_Numerics_FiniteElement_GalerkinStructMech2DDispDiffEntity_hh
