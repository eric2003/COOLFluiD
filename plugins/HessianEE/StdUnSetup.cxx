#include "HessianEE/HessianEE.hh"
#include "StdUnSetup.hh"
#include "Framework/MethodCommandProvider.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace COOLFluiD::Framework;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Numerics {

    namespace HessianEE {

//////////////////////////////////////////////////////////////////////////////

MethodCommandProvider<StdUnSetup, HessEEData, HessianEEModule> stdUnSetupProvider("StdUnSetup");

//////////////////////////////////////////////////////////////////////////////

void StdUnSetup::execute()
{
  CFAUTOTRACE;
}

//////////////////////////////////////////////////////////////////////////////

    } // namespace HessianEE

  } // namespace Numerics

} // namespace COOLFluiD
