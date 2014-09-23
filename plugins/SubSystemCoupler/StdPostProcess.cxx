#include "SubSystemCoupler/SubSystemCoupler.hh"
#include "StdPostProcess.hh"
#include "Framework/MethodCommandProvider.hh"
#include "Framework/SubSystemStatus.hh"
#include "Framework/MeshData.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace COOLFluiD::Framework;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Numerics {

    namespace SubSystemCoupler {

//////////////////////////////////////////////////////////////////////////////

MethodCommandProvider<StdPostProcess, SubSysCouplerData, SubSystemCouplerModule> stdPostProcessProvider("StdPostProcess");

//////////////////////////////////////////////////////////////////////////////

void StdPostProcess::executeOnTrs()
{
}

//////////////////////////////////////////////////////////////////////////////

    } // namespace SubSystemCoupler

  } // namespace Numerics

} // namespace COOLFluiD
