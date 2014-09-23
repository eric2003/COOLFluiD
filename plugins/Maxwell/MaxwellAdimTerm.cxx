#include "MaxwellAdimTerm.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace COOLFluiD::Framework;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Physics {

    namespace Maxwell {
      
//////////////////////////////////////////////////////////////////////////////

MaxwellAdimTerm::MaxwellAdimTerm(const std::string& name)
  : ConvMaxwellTerm(name)
{
}

//////////////////////////////////////////////////////////////////////////////

MaxwellAdimTerm::~MaxwellAdimTerm()
{
}

//////////////////////////////////////////////////////////////////////////////

void MaxwellAdimTerm::configure ( Config::ConfigArgs& args )
{
  ConvMaxwellTerm::configure(args);
}

//////////////////////////////////////////////////////////////////////////////

void MaxwellAdimTerm::setupPhysicalData()
{
  // resize the physical data
  cf_assert(getDataSize() > 0);

  resizePhysicalData(m_physicalData);
  resizePhysicalData(m_refPhysicalData);
}

//////////////////////////////////////////////////////////////////////////////

} // namespace Maxwell

} // namespace Physics

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////
