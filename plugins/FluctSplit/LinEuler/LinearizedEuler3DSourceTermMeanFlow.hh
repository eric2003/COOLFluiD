#ifndef COOLFluiD_Numerics_FluctSplit_LinearizedEuler3DSourceTermMeanFlow_hh
#define COOLFluiD_Numerics_FluctSplit_LinearizedEuler3DSourceTermMeanFlow_hh

//////////////////////////////////////////////////////////////////////////////

#include "FluctSplit/ComputeSourceTermFSM.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD { 

  namespace Framework {

    class State; 
  }

  namespace Physics {

    namespace  LinearizedEuler{

      class LinEuler3DVarSet;
   }
  }


    namespace FluctSplit {

      class InwardNormalsData;

//////////////////////////////////////////////////////////////////////////////

/**
 * This class represents a source term for LinearizedEuler3D unhomogeneous mean flow
 * 
 * @author Lilla Koloszar
 */
class LinearizedEuler3DSourceTermMeanFlow : public ComputeSourceTermFSM {
public:

  /**
   * Constructor
   * @see LinEuler3D
   */
  LinearizedEuler3DSourceTermMeanFlow(const std::string& name);
  
  /**
   * Default destructor
   */
  ~LinearizedEuler3DSourceTermMeanFlow();
  
  /**
   * Set up private data and data of the aggregated classes 
   * in this command before processing phase
   */
  void setup();
  
  /**
   * Compute the source term
   */ 
  virtual void computeSourceFSM(Framework::GeometricEntity *const cell,
        RealVector& source,
        const FluctSplit::InwardNormalsData& normalsData);

 /**
   * Returns the DataSocket's that this command needs as sinks
   * @return a vector of SafePtr with the DataSockets
   */
  virtual std::vector<Common::SafePtr<Framework::BaseDataSocketSink> > needsSockets();


private: // data

  /// the socket stores the data of the mean flow
  Framework::DataSocketSink<RealVector> socket_meanflow;

  /// The sockets for the update coefficients
  Framework::DataSocketSink<CFreal> socket_volumes;

  /// vector to store temporary result
  RealVector _temp;

  /// corresponding variable set
  Common::SafePtr<Physics::LinearizedEuler::LinEuler3DVarSet> _varSet;

 }; // end of class LinEuler3DSourceTerm

//////////////////////////////////////////////////////////////////////////////

    } // namespace FluctSplit
  


} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_Numerics_FluctSplit_LinearizedEuler3DSourceTermMeanFlow_hh
