#ifndef COOLFluiD_Numerics_AeroCoefSpectralFD_hh
#define COOLFluiD_Numerics_AeroCoefSpectralFD_hh

//////////////////////////////////////////////////////////////////////////////

#include "Environment/ModuleRegister.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

    /// The classes that implement computation of aerodynamic coefficients
    /// with bindings to spectral difference methods
  namespace AeroCoef {

//////////////////////////////////////////////////////////////////////////////

/**
 * This class defines the Module AeroCoefSpectralFD
 */
class AeroCoefSpectralFDModule : public Environment::ModuleRegister<AeroCoefSpectralFDModule> {
public:

  /**
   * Static function that returns the module name.
   * Must be implemented for the ModuleRegister template
   * @return name of the module
   */
  static std::string getModuleName()
  {
    return "AeroCoefSpectralFD";
  }

  /**
   * Static function that returns the description of the module.
   * Must be implemented for the ModuleRegister template
   * @return descripton of the module
   */
  static std::string getModuleDescription()
  {
    return "This module implements computation of aerodynamic coefficients with bindings to spectral difference methods.";
  }

}; // end AeroCoefSpectralFDModule

//////////////////////////////////////////////////////////////////////////////

    } // namespace AeroCoef

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFLUID_Numerics_AeroCoefSpectralFD_hh

