#ifndef COOLFluiD_Framework_ComputeFaceNormalsPrismP1_hh
#define COOLFluiD_Framework_ComputeFaceNormalsPrismP1_hh

//////////////////////////////////////////////////////////////////////////////

#include "Framework/ComputeFaceNormalsFVMCC.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Framework {

//////////////////////////////////////////////////////////////////////////////

    /**
     * This class is a functor tha computes the face (outward) normals
     *
     * @author Thomas Wuilbaut
     */

class Framework_API ComputeFaceNormalsPrismP1 : public ComputeFaceNormalsFVMCC {
public:

  /**
   * Constructor
   */
  ComputeFaceNormalsPrismP1() : ComputeFaceNormalsFVMCC()
  {
  }

  /**
   * Destructor
   */
  ~ComputeFaceNormalsPrismP1()
  {
  }

  /**
   * Overloading of the operator () to make this class act as a
   * functor
   */
  void operator() (const CFuint& iFirstElem,
                   const CFuint& iLastElem,
                   const CFuint& iType);

}; // end of class ComputeFaceNormalsPrismP1

//////////////////////////////////////////////////////////////////////////////

    } // namespace Framework

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_Framework_ComputeFaceNormalsPrismP1_hh
