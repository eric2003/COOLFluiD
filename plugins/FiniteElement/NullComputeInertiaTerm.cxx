#include "NullComputeInertiaTerm.hh"
#include "Framework/MethodStrategyProvider.hh"
#include "FiniteElement/FiniteElement.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::Framework;
using namespace COOLFluiD::Common;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Numerics {

    namespace FiniteElement {

//////////////////////////////////////////////////////////////////////////////

MethodStrategyProvider<NullComputeInertiaTerm,
                       FiniteElementMethodData,
                       ComputeInertiaTerm,
                       FiniteElementModule>
nullInertiaTermStrategyProvider("NullInertiaTerm");

//////////////////////////////////////////////////////////////////////////////

NullComputeInertiaTerm::NullComputeInertiaTerm(const std::string& name) :
  ComputeInertiaTerm(name)
{
}

//////////////////////////////////////////////////////////////////////////////

NullComputeInertiaTerm::~NullComputeInertiaTerm()
{
}

//////////////////////////////////////////////////////////////////////////////

    } // namespace FiniteElement

  } // namespace Numerics

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

