#ifndef COOLFluiD_Numerics_SubSystemCoupler_SolidSolidHeatVariableTransformer_hh
#define COOLFluiD_Numerics_SubSystemCoupler_SolidSolidHeatVariableTransformer_hh

//////////////////////////////////////////////////////////////////////////////

#include "PostVariableTransformer.hh"
#include "Framework/GeometricEntity.hh"
#include "Heat/HeatPhysicalModel.hh"
#include "Framework/DataSocketSink.hh"
#include "Common/Trio.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Numerics {

    namespace SubSystemCoupler {

//////////////////////////////////////////////////////////////////////////////

/**
 * This class represents a SolidSolidHeat transformer of variables
 *
 * @author Thomas Wuilbaut
 *
 */

class SolidSolidHeatVariableTransformer : public PostVariableTransformer {
public:

 /**
   * Defines the Config Option's of this class
   * @param options a OptionList where to add the Option's
   */
  static void defineConfigOptions(Config::OptionList& options);

  /**
   * Default constructor without arguments
   */
  SolidSolidHeatVariableTransformer(const std::string& name);

  /**
   * Default destructor
   */
  ~SolidSolidHeatVariableTransformer();

  /**
   * Configuration
   */
  virtual void configure ( Config::ConfigArgs& args )
  {
    PostVariableTransformer::configure(args);
  }

  /**
   * Returns the DataSocket's that this strategy needs as sinks
   * @return a vector of SafePtr with the DataSockets
   */
  std::vector<Common::SafePtr<Framework::BaseDataSocketSink> > needsSockets();

  /**
   * Sets Up the object
   */
  virtual void setup();

 /**
   * Transform a vector into another one
   */
  virtual RealVector* transform(const std::vector<GeoEntityIdx>& faces,
                                const RealVector& coord,
                                const RealVector& original,
                                const RealVector& pastTransformedVector);

  /**
   * Transform a vector into another one (in the case of nodal values)
   */
  virtual RealVector* transform(const std::vector<GeoEntityIdx>& faces,
                                const RealVector& coord,
                                const RealVector& currentState,
                                const RealVector& original,
                                const RealVector& pastTransformedVector);

  /**
   * Return the size of the transformed vector
   */
  CFuint getTransformedSize(const CFuint size)
  {
    cf_assert(size == 2);
    return 1;
  }

private:

  ///Link to the Heat Physical Model
  Common::SafePtr<Physics::Heat::HeatPhysicalModel> _model;


  /// handle to the neighbor cell
  Framework::DataSocketSink<
  	Common::Trio<CFuint, CFuint, Common::SafePtr<Framework::TopologicalRegionSet> > >
        socket_faceNeighCell;

  //gradients of temperature
  RealVector _gradientsT;

  //normal to the face
  RealVector _normal;

  //coordinate
  std::vector<RealVector> _coords;


  //Value of the conductivity of the coupled subdomain
  CFreal _otherConductivity;


}; // end of class SolidSolidHeatVariableTransformer

//////////////////////////////////////////////////////////////////////////////

    } // namespace SubSystemCoupler

  } // namespace Physics

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_Numerics_SubSystemCoupler_SolidSolidHeatVariableTransformer_hh
