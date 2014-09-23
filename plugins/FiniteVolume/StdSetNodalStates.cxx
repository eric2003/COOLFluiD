#include "FiniteVolume/FiniteVolume.hh"
#include "StdSetNodalStates.hh"
#include "Framework/MethodCommandProvider.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::Framework;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Numerics {

    namespace FiniteVolume {

//////////////////////////////////////////////////////////////////////////////

MethodCommandProvider<StdSetNodalStates,
                      CellCenterFVMData,
                      FiniteVolumeModule>
stdSetNodalStatesProvider("StdSetNodalStates");

//////////////////////////////////////////////////////////////////////////////

StdSetNodalStates::StdSetNodalStates(const std::string& name) :
  CellCenterFVMCom(name)
{
}

//////////////////////////////////////////////////////////////////////////////

StdSetNodalStates::~StdSetNodalStates()
{
}

//////////////////////////////////////////////////////////////////////////////

void StdSetNodalStates::execute()
{
   CFAUTOTRACE;

   getMethodData().getNodalStatesExtrapolator()->extrapolateInAllNodes();
}

//////////////////////////////////////////////////////////////////////////////

    } // namespace FiniteVolume

  } // namespace Numerics

} // namespace COOLFluiD
