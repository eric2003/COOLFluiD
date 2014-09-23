#include "Framework/ComputeFaceNormalsTetraP1.hh"
#include "Framework/MeshData.hh"
#include "Framework/GeometricEntity.hh"
#include "Environment/ObjectProvider.hh"
#include "Framework/TrsGeoWithNodesBuilder.hh"
#include "Framework/GeometricEntityPool.hh"
#include "Framework/Framework.hh"
#include "Framework/PhysicalModel.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::MathTools;
using namespace COOLFluiD::Common;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Framework {

//////////////////////////////////////////////////////////////////////////////

Environment::ObjectProvider<ComputeFaceNormalsTetraP1,
			    ComputeNormals,
			    FrameworkLib>
computeFaceNormalsTetraP1Provider("FaceTetraP1");

//////////////////////////////////////////////////////////////////////////////

void ComputeFaceNormalsTetraP1::operator() (const CFuint& iFirstElem,
					    const CFuint& iLastElem,
					    const CFuint& iType)
{
  SafePtr<TopologicalRegionSet> cells =
    MeshDataStack::getActive()->getTrs("InnerCells");

  SafePtr<ConnectivityTable<CFuint> > cellFaces =
    MeshDataStack::getActive()->getConnectivity("cellFaces");

  DataHandle<CFreal> normals = socket_normals->getDataHandle();
  DataHandle<CFint> isOutward = socket_isOutward->getDataHandle();

  const CFuint dim = PhysicalModelStack::getActive()->getDim();

  GeometricEntityPool<TrsGeoWithNodesBuilder> geoBuilder;
  geoBuilder.setup();

  TrsGeoWithNodesBuilder::GeoData& geoData = geoBuilder.getDataGE();
  geoData.trs = cells;

  RealVector v1(dim);
  RealVector v2(dim);
  RealVector v3(dim);

  for (CFuint iElem = iFirstElem; iElem < iLastElem; ++iElem) {
    geoData.idx = iElem;
    GeometricEntity& cell = *geoBuilder.buildGE();
    const vector<Node*> *const nodes = cell.getNodes();

    CFuint faceID = (*cellFaces)(iElem, 0);
    CFuint faceCompID = faceID*dim;

    if (isOutward[faceID] == -1) {
      v1 = (*(*nodes)[1]) - (*(*nodes)[0]);
      v2 = (*(*nodes)[2]) - (*(*nodes)[0]);
      MathFunctions::crossProd(v1, v2, v3);

      for (CFuint i = 0; i < dim; ++i) {
	normals[faceCompID + i] = -0.5*v3[i];
      }

      isOutward[faceID] = iElem;
    }

    faceID = (*cellFaces)(iElem, 1);
    faceCompID = faceID*dim;

    if (isOutward[faceID] == -1) {
      v1 = (*(*nodes)[3]) - (*(*nodes)[0]);
      v2 = (*(*nodes)[1]) - (*(*nodes)[0]);
      MathFunctions::crossProd(v1, v2, v3);

      for (CFuint i = 0; i < dim; ++i) {
	normals[faceCompID + i] = -0.5*v3[i];
      }

      isOutward[faceID] = iElem;
    }

    faceID = (*cellFaces)(iElem, 2);
    faceCompID = faceID*dim;

    if (isOutward[faceID] == -1) {
      v1 = (*(*nodes)[3]) - (*(*nodes)[1]);
      v2 = (*(*nodes)[2]) - (*(*nodes)[1]);
      MathFunctions::crossProd(v1, v2, v3);

      for (CFuint i = 0; i < dim; ++i) {
	normals[faceCompID + i] = -0.5*v3[i];
      }

      isOutward[faceID] = iElem;
    }

    faceID = (*cellFaces)(iElem, 3);
    faceCompID = faceID*dim;

    if (isOutward[faceID] == -1) {
      v1 = (*(*nodes)[2]) - (*(*nodes)[0]);
      v2 = (*(*nodes)[3]) - (*(*nodes)[0]);
      MathFunctions::crossProd(v1, v2, v3);

      for (CFuint i = 0; i < dim; ++i) {
	normals[faceCompID + i] = -0.5*v3[i];
      }

      isOutward[faceID] = iElem;
    }

    geoBuilder.releaseGE();
  }
}

//////////////////////////////////////////////////////////////////////////////

    } // namespace Framework

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////
