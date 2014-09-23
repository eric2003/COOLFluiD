#ifndef COOLFluiD_Numerics_FluctSplit_STKT_NCSchemeSysquad_hh
#define COOLFluiD_Numerics_FluctSplit_STKT_NCSchemeSysquad_hh

//////////////////////////////////////////////////////////////////////////////

#include "STKT_SplitterSyshyb.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {



    namespace FluctSplit {

//////////////////////////////////////////////////////////////////////////////

/**
 * This class represents the SpaceTime N scheme for RDS space discretization
 * We consider it as the space-Time LDA + a dissipation. This approach is developped
 * In the thesis of Mario Ricchiuto (see pp 139)
 * @author Nadege Villedieu
 *
 */
class STKT_NCSchemeSysquad : public STKT_SplitterSyshyb {
public:

  /**
   * Default constructor.
   */
  STKT_NCSchemeSysquad(const std::string& name);

  /**
   * Default destructor
   */
  ~STKT_NCSchemeSysquad();

  /**
   * Set up
   */
  void setup();

  /**
   * Distribute the residual
   */
  void distribute(std::vector<RealVector>& residual);


  /**
   * Compute all the contributions for the Picard jacobian
   */
  void computePicardJacob(std::vector<RealMatrix*>& jacob);

private:


/// temporary data for computation ofthe sum of the positive part of the "space-time"upwind coeff
  RealMatrix m_sumKplus;

  RealMatrix _invK;

  RealVector m_uTemp;

  RealVector m_diss;

  RealVector m_sumKplusU;

  RealVector m_phiT;

}; // end of class STKT_NCSchemeSys

//////////////////////////////////////////////////////////////////////////////

    } // namespace FluctSplit



} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_Numerics__STKT_NCSchemeSys_hh
