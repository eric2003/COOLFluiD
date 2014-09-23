#ifndef COOLFluiD_Numerics_FluctSplit_HOCRDP3_SplitStrategy_hh
#define COOLFluiD_Numerics_FluctSplit_HOCRDP3_SplitStrategy_hh

//////////////////////////////////////////////////////////////////////////////

#include "MathTools/CFMat.hh"
#include "Framework/StdTrsGeoBuilder.hh"
#include "FluctSplit/FluctuationSplitStrategy.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {



    namespace FluctSplit {

//////////////////////////////////////////////////////////////////////////////

/// This class represent a fluctuation splitting strategy of higher order
/// elements (P3 elements) which residual is computed with a contour integral.
/// @author Nadege Villedieu
class HOCRDP3_SplitStrategy : public FluctuationSplitStrategy {
public: // methods

  /// Constructor.
  HOCRDP3_SplitStrategy(const std::string& name);

  /// Destructor.
  virtual ~HOCRDP3_SplitStrategy();

  /// Configure the object
  virtual void configure ( Config::ConfigArgs& args )
  {
    FluctuationSplitStrategy::configure(args);
  }

  /// Set up private data
  virtual void setup();

  /// Unsetup private data
  virtual void unsetup();

  /// Returns the DataSocket's that this numerical strategy needs as sinks
  /// @return a vector of SafePtr with the DataSockets
  virtual std::vector<Common::SafePtr<Framework::BaseDataSocketSink> > needsSockets();

  /// Compute the fluctuation
  /// @param residual the residual for each variable to distribute in each state
  virtual void computeFluctuation(std::vector<RealVector>& residual);

protected: // methods
  /// Compute the integral of the fluxes
  void computeHOP3Fluctuation();

protected: // data

  /// The sockets for the update coefficients
  Framework::DataSocketSink<CFreal> socket_updateCoeff;

  /// solution variable set
  Common::SafePtr<Framework::ConvectiveVarSet> m_solutionVar;



  /// update variable set
  Common::SafePtr<Framework::ConvectiveVarSet> m_updateVar;

  /// matrix storing the unit sized face normals
  std::vector<RealVector> m_unitFaceNormals;

  /// states that compose each sub element
  std::vector<Framework::State*> substates;

  /// residuals for each sub element
  std::vector<RealVector> subresidual;

  /// fluctuation on each sub element
  std::vector<RealVector*> m_phisubT;

  /// faces that compose each sub element
  MathTools::CFMat<CFuint> subelemtable;

  /// direction of the faces
  MathTools::CFMat<CFreal> subelemfacedir;

  /// states that compose each sub face
  MathTools::CFMat<CFuint> subfacetable;

  /// fluxes on each sub face
  std::vector<RealVector> faceflux;

  /// quadrature points per face
  RealVector qd0;
  RealVector qd1;
  RealVector wqd;

  /// states at quadrature points
  std::vector<Framework::State*> qdstates;

  /// coordinates of these states
  std::vector<Framework::Node*> qdnodes;

  /// extra values at quadrature points
  std::vector<RealVector*> m_qdExtraVars;

  /// temporary face normal
  RealVector facenormal;

/// temporary residual pointer after transformation
  RealVector * m_phi;
private :

/// the single splitter
  Common::SafePtr<Splitter> m_splitter;
}; //end class HOCRDP3_SplitStrategy

    } //end namespace FluctSplit
} // end COOLFluid

#endif// COOLFluiD_Numerics_FluctSplit_HOCRDP3_SplitStrategy_hh
