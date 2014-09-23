#ifndef COOLFluiD_Physics_NavierStokes_Euler2DPrim_hh
#define COOLFluiD_Physics_NavierStokes_Euler2DPrim_hh

//////////////////////////////////////////////////////////////////////////////

#include "Euler2DVarSet.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Physics {

    namespace NavierStokes {

//////////////////////////////////////////////////////////////////////////////

  /**
   * This class represents a Euler physical model 2D for primitive
   * variables
   *
   * @author Andrea Lani
   */
class Euler2DPrim : public Euler2DVarSet {
public: // classes

  /**
   * Constructor
   * @see Euler2D
   */
  Euler2DPrim(Common::SafePtr<Framework::BaseTerm> term);

  /**
   * Default destructor
   */
  virtual ~Euler2DPrim();

  /**
   * Gets the block separator for this variable set
   */
  virtual CFuint getBlockSeparator() const;

  /**
   * Set the jacobians
   */
  virtual void computeJacobians();
  
  /**
   * Split the jacobian
   */
  virtual void splitJacobian(RealMatrix& jacobPlus,
			     RealMatrix& jacobMin,
			     RealVector& eValues,
			     const RealVector& normal);
  
  /**
   * Set the matrix of the right eigenvectors and the matrix of the eigenvalues
   */
  virtual void computeEigenValuesVectors(RealMatrix& rightEv,
					 RealMatrix& leftEv,
					 RealVector& eValues,
					 const RealVector& normal);
  
  /**
   * Get the speed
   */
  virtual CFreal getSpeed(const Framework::State& state) const;
  
  /**
   * Give dimensional values to the adimensional state variables
   */
  virtual void setDimensionalValues(const Framework::State& state,
				    RealVector& result);
  
  /**
   * Give adimensional values to the dimensional state variables
   */
  virtual void setAdimensionalValues(const Framework::State& state,
				     RealVector& result);
  
  /**
   * Set the PhysicalData corresponding to the given State
   * @see EulerPhysicalModel
   */
  virtual void computePhysicalData(const Framework::State& state, RealVector& data);
  
  /**
   * Set a State starting from the given PhysicalData
   * @see EulerPhysicalModel
   */
  virtual void computeStateFromPhysicalData(const RealVector& data, Framework::State& state);
  
  /// Compute the perturbed physical data
  virtual void computePerturbedPhysicalData(const Framework::State& state,
					    const RealVector& pdataBkp,
					    RealVector& pdata,
					    CFuint iVar)
  {
    throw Common::NotImplementedException (FromHere(),"Euler2DPrim::computePerturbedPhysicalData()");
  }
  
  /// Set the IDs corresponding to the velocity components in a State
  virtual void setStateVelocityIDs (std::vector<CFuint>& velIDs)
  {
    velIDs.resize(2); velIDs[XX] = 1; velIDs[YY] = 2; 
  }
  
}; // end of class Euler2DPrim
      
//////////////////////////////////////////////////////////////////////////////

    } // namespace NavierStokes

  } // namespace Physics

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_Physics_NavierStokes_Euler2DPrim_hh
