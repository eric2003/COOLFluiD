#include "Framework/MethodCommandProvider.hh"

#include "SpectralFD/SpectralFD.hh"
#include "SpectralFD/NullCommandSpectralFD.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace COOLFluiD::Framework;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace SpectralFD {

//////////////////////////////////////////////////////////////////////////////

MethodCommandProvider<NullCommandSpectralFD, SpectralFDMethodData, SpectralFDModule> NullCommandSpectralFDProvider("NullCommand");

//////////////////////////////////////////////////////////////////////////////

NullCommandSpectralFD::NullCommandSpectralFD(const std::string& name) :
  SpectralFDMethodCom(name)
{
}

//////////////////////////////////////////////////////////////////////////////

NullCommandSpectralFD::~NullCommandSpectralFD()
{
}

//////////////////////////////////////////////////////////////////////////////

  } // namespace SpectralFD

} // namespace COOLFluiD
