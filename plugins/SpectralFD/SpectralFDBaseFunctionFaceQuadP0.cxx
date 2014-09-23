#include "SpectralFD/SpectralFDBaseFunctionFaceQuadP0.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace SpectralFD {

//////////////////////////////////////////////////////////////////////////////

CFuint SpectralFDBaseFunctionFaceQuadP0::_interpolatorID = 0;

//////////////////////////////////////////////////////////////////////////////

SpectralFDBaseFunctionFaceQuadP0::SpectralFDBaseFunctionFaceQuadP0()
{
}

//////////////////////////////////////////////////////////////////////////////

void SpectralFDBaseFunctionFaceQuadP0::computeFaceJacobianDeterminant(
        const std::vector<RealVector>& mappedCoord,
        const std::vector<Framework::Node*>& nodes,
        const Framework::IntegratorPattern& pattern,
              std::vector<RealVector>& faceJacobian)
{
    throw Common::ShouldNotBeHereException (FromHere(),"Spectral finite difference base functions should not be used as geometrical shape functions.");
}

//////////////////////////////////////////////////////////////////////////////

RealVector SpectralFDBaseFunctionFaceQuadP0::computeMappedCoordinates(const RealVector& coord,
                                    const std::vector<Framework::Node*>& nodes)
{
  throw Common::ShouldNotBeHereException (FromHere(),"Spectral finite difference base functions should not be used as geometrical shape functions.");
}

//////////////////////////////////////////////////////////////////////////////

RealVector SpectralFDBaseFunctionFaceQuadP0::computeMappedCoordinatesPlus1D(const RealVector& coord,
                                    const std::vector<Framework::Node*>& nodes)
{
  throw Common::ShouldNotBeHereException (FromHere(),"Spectral finite difference base functions should not be used as geometrical shape functions.");
}

//////////////////////////////////////////////////////////////////////////////

  } // namespace SpectralFD

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////
