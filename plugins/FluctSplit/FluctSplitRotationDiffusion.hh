#ifndef COOLFluiD_Numerics_Fluctsplit_FluctSplitRotationDiffusion_hh
#define COOLFluiD_Numerics_Fluctsplit_FluctSplitRotationDiffusion_hh

//////////////////////////////////////////////////////////////////////////////

#include "Environment/ModuleRegister.hh"
#include "Common/ExportAPI.hh"

//////////////////////////////////////////////////////////////////////////////

/// Define the macro FluctSplitRotationDiffusion_API
/// @note build system defines FluctSplitRotationDiffusion_EXPORTS
#ifdef FluctSplitRotationDiffusion_EXPORTS
#   define FluctSplitRotationDiffusion_API CF_EXPORT_API
#else
#   define FluctSplitRotationDiffusion_API CF_IMPORT_API
#endif

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

    /// The classes that implement Fluctuation Splitting space method.
    namespace FluctSplit {

//////////////////////////////////////////////////////////////////////////////

/// This class defines the Module FluctSplitScalarDiffusion
class FluctSplitRotationDiffusionModule : public Environment::ModuleRegister<FluctSplitRotationDiffusionModule> {
public:

  /// Static function that returns the module name.
  /// Must be implemented for the ModuleRegister template
  /// @return name of the module
  static std::string getModuleName()
  {
    return "FluctSplitRotationDiffusion";
  }

  /// Static function that returns the description of the module.
  /// Must be implemented for the ModuleRegister template
  /// @return descripton of the module
  static std::string getModuleDescription()
  {
    return "This module implementes Rotation Diffusion model bindings to the Fluctuation Splitting space discretization method.";
  }

}; // end FluctSplitNavierStokesModule

//////////////////////////////////////////////////////////////////////////////

    }   // namespace FluctSplit



} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_Numerics_Fluctsplit_FluctSplitNavierStokes_hh
