#include "StructMech/StructMechTerm.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::Framework;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Physics {

    namespace StructMech {

//////////////////////////////////////////////////////////////////////////////

void StructMechTerm::defineConfigOptions(Config::OptionList& options)
{
}

//////////////////////////////////////////////////////////////////////////////

StructMechTerm::StructMechTerm(const std::string& name) : BaseTerm(name)
{
   addConfigOptionsTo(this);
}

//////////////////////////////////////////////////////////////////////////////

StructMechTerm::~StructMechTerm()
{
}

//////////////////////////////////////////////////////////////////////////////

void StructMechTerm::configure ( Config::ConfigArgs& args )
{
  BaseTerm::configure(args);
}

//////////////////////////////////////////////////////////////////////////////

void StructMechTerm::setupPhysicalData()
{
  cf_assert(getDataSize() > 0);

  resizePhysicalData(m_physicalData);
  resizePhysicalData(m_refPhysicalData);
}

//////////////////////////////////////////////////////////////////////////////

} // namespace StructMech

} // namespace Physics

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////
