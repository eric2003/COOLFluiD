#ifndef COOLFluiD_Physics_MHD_MHD3DProjectionPrimToConsInRef_hh
#define COOLFluiD_Physics_MHD_MHD3DProjectionPrimToConsInRef_hh

//////////////////////////////////////////////////////////////////////////////

#include "Framework/VarSetMatrixTransformer.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Physics {

    namespace MHD {

      class MHDProjectionTerm;

//////////////////////////////////////////////////////////////////////////////

/**
 * This class represents a transformer of variables from primitive
 * to conservative variables in reference variables
 *
 * @author Andrea Lani
 * @author Radka Keslerova
 *
 */
class MHD3DProjectionPrimToConsInRef :
        public Framework::VarSetMatrixTransformer {
public:

  /**
   * Default constructor without arguments
   */
  MHD3DProjectionPrimToConsInRef(Common::SafePtr<Framework::PhysicalModelImpl> model);

  /**
   * Default destructor
   */
  ~MHD3DProjectionPrimToConsInRef();

  /**
   * Set the transformation matrix from reference values
   */
  void setMatrixFromRef();

private:

  /**
   * Set the flag telling if the transformation is an identity one
   * @pre this method must be called during set up
   */
  bool getIsIdentityTransformation() const
  {
    return false;
  }

private: // data

  // acquaitance of the PhysicalModel
  Common::SafePtr<MHDProjectionTerm> _model;
}; // end of class MHD3DProjectionPrimToConsInRef

//////////////////////////////////////////////////////////////////////////////

    } // namespace MHD

  } // namespace Physics

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_Physics_MHD_MHD3DProjectionPrimToConsInRef_hh
