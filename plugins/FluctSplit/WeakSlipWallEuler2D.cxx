#include "FluctSplit/FluctSplitNavierStokes.hh"
#include "WeakSlipWallEuler2D.hh"
#include "InwardNormalsData.hh"
#include "Framework/CFL.hh"
#include "Framework/PhysicalModel.hh"
#include "Framework/MethodCommandProvider.hh"
#include "NavierStokes/Euler2DVarSet.hh"
#include "Framework/MeshData.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::MathTools;
using namespace COOLFluiD::Common;
using namespace COOLFluiD::Framework;
using namespace COOLFluiD::Physics::NavierStokes;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {



    namespace FluctSplit {

//////////////////////////////////////////////////////////////////////////////

MethodCommandProvider<WeakSlipWallEuler2D,
		      FluctuationSplitData,
		      FluctSplitNavierStokesModule>
weakSlipWallEuler2DProvider("WeakSlipWallEuler2D");

//////////////////////////////////////////////////////////////////////////////

void WeakSlipWallEuler2D::defineConfigOptions(Config::OptionList& options)
{
   options.addConfigOption< CFreal >("alpha","distribution coefficient");
}

//////////////////////////////////////////////////////////////////////////////

WeakSlipWallEuler2D::WeakSlipWallEuler2D(const std::string& name) :
  FluctuationSplitCom(name),
  socket_rhs("rhs"),
  socket_states("states"),
  socket_isUpdated("isUpdated"),
  socket_normals("normals"),
  socket_faceNeighCell("faceNeighCell"),
  _flagState(),
  _varSet(CFNULL),
  _physicalData(),
  _tmpFlux()
{
   addConfigOptionsTo(this);
  _alpha = 1.0;
   setParameter("alpha",&_alpha);
}

//////////////////////////////////////////////////////////////////////////////

WeakSlipWallEuler2D::~WeakSlipWallEuler2D()
{
}

//////////////////////////////////////////////////////////////////////////////

std::vector<Common::SafePtr<BaseDataSocketSink> >
WeakSlipWallEuler2D::needsSockets()
{

  std::vector<Common::SafePtr<BaseDataSocketSink> > result;

  result.push_back(&socket_rhs);
  result.push_back(&socket_states);
  result.push_back(&socket_isUpdated);
  result.push_back(&socket_normals);
  result.push_back(&socket_faceNeighCell);

  return result;
}

//////////////////////////////////////////////////////////////////////////////

void WeakSlipWallEuler2D::setup()
{
  _varSet = getMethodData().getUpdateVar().d_castTo<Euler2DVarSet>();

  // get the data handle for the states
  DataHandle < Framework::State*, Framework::GLOBAL > states = socket_states.getDataHandle();
  _flagState.resize(states.size());
  _flagState = false;

  // set up the physical data
  _varSet->getModel()->resizePhysicalData(_physicalData);

  _tmpFlux.resize(PhysicalModelStack::getActive()->getNbEq());
 CFuint max_nb_states = 0;
 Common::SafePtr<GeometricEntityPool<StdTrsGeoBuilder> >
  geoBuilder = getMethodData().getStdTrsGeoBuilder();

  StdTrsGeoBuilder::GeoData& geoData = geoBuilder->getDataGE();

  std::vector< Common::SafePtr<TopologicalRegionSet> >& trss = getTrsList();

  std::vector< SafePtr<TopologicalRegionSet> >::iterator itrs = trss.begin();


  for (; itrs != trss.end(); ++itrs)
  {
    SafePtr<TopologicalRegionSet> faces = *itrs;

    geoData.trs = faces;

    const CFuint nbFaces = faces->getLocalNbGeoEnts();

    for (CFuint iFace = 0; iFace < nbFaces; ++iFace)
    {
      // build the GeometricEntity
      geoData.idx = iFace;

      GeometricEntity& currFace = *geoBuilder->buildGE();

      const CFuint nb_state = currFace.nbStates();

      max_nb_states = std::max(max_nb_states, nb_state);

    // release the face
    geoBuilder->releaseGE();
    }
  }

// vector of fluxes of each state
    m_flux.resize(max_nb_states);
const CFuint nbEqs = PhysicalModelStack::getActive()->getNbEq();
   for ( CFuint iState = 0; iState < max_nb_states; ++iState)
      m_flux[iState].resize(nbEqs);
  // vector of states of the face
    m_states.resize(max_nb_states);
}

//////////////////////////////////////////////////////////////////////////////

void WeakSlipWallEuler2D::executeOnTrs()
{
  CFAUTOTRACE;
  DataHandle<bool> isUpdated = socket_isUpdated.getDataHandle();
  DataHandle<CFreal> rhs = socket_rhs.getDataHandle();

  const CFuint nbEqs = PhysicalModelStack::getActive()->getNbEq();
  const CFuint dim = PhysicalModelStack::getActive()->getDim();

  RealVector normal(0.0, dim);
  const CFreal oEminusAlpha = 1. - _alpha;


 Common::SafePtr<GeometricEntityPool<StdTrsGeoBuilder> >
    geoBuilder = getMethodData().getStdTrsGeoBuilder();

  StdTrsGeoBuilder::GeoData& geoData = geoBuilder->getDataGE();
  geoData.trs = getCurrentTRS();

  const CFuint nbFaces = getCurrentTRS()->getLocalNbGeoEnts();
  for (CFuint iFace = 0; iFace < nbFaces; ++iFace) {

    geoData.idx = iFace;
    GeometricEntity& face = *geoBuilder->buildGE();

    // set number of states on one face
    const CFuint nb_state = face.nbStates();
    const CFreal inv_nb_state = 1.0/nb_state;

    // set the face normal
    setFaceNormal(face.getID(), normal);

  m_states = *face.getStates();

    // compute the normal fluxes corrections for both the states
    // of this cell
    for (CFuint iState = 0; iState < nb_state; ++iState){
         computeNormalFlux(*m_states[iState], normal, m_flux[iState]);

}

    // distribute contributions to the two nodes
    for (CFuint iEq = 0; iEq < nbEqs; ++iEq) {

       for (CFuint iState = 0; iState < nb_state ; ++iState) {

            if (!isUpdated[m_states[iState]->getLocalID()])
                {
                  CFreal sum_flux_not_iState = 0.0;

	          for (CFuint jState = 0; jState < nb_state ; ++jState){
                       if (jState != iState)
                           sum_flux_not_iState += m_flux[jState][iEq];
                  }
                  rhs(m_states[iState]->getLocalID(), iEq, nbEqs) -=
                    inv_nb_state*(_alpha*m_flux[iState][iEq] + oEminusAlpha*sum_flux_not_iState);

                 _flagState[m_states[iState]->getLocalID()] = true;
                 }
       }


    }
   geoBuilder->releaseGE();
  }

  ///@todo this could be done in a more efficient way ...
  const CFuint nbStates = _flagState.size();
  for (CFuint i = 0; i < nbStates; ++i) {
    if (_flagState[i] == true) {
      isUpdated[i] = true;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////

void WeakSlipWallEuler2D::computeNormalFlux(const State& state,
                                            const RealVector& normal,
                                            RealVector& flux)
{
  State& ss = *(const_cast<State*>(&state));
  _varSet->computePhysicalData(ss, _physicalData);

  const CFreal un = _physicalData[EulerTerm::VX]*normal[XX] +
    _physicalData[EulerTerm::VY]*normal[YY];

  const CFreal rho = _physicalData[EulerTerm::RHO];

  if (!getMethodData().isResidualTransformationNeeded()) {
    flux[0] = rho*un;
    flux[1] = un*rho*_physicalData[EulerTerm::VX];
    flux[2] = un*rho*_physicalData[EulerTerm::VY];
    flux[3] = un*rho*_physicalData[EulerTerm::H];
  }
  else {
    _tmpFlux[0] = rho*un;
    _tmpFlux[1] = un*rho*_physicalData[EulerTerm::VX];
    _tmpFlux[2] = un*rho*_physicalData[EulerTerm::VY];
    _tmpFlux[3] = un*rho*_physicalData[EulerTerm::H];
    
    // set the transformation from update to solution in update
    SafePtr<VarSetMatrixTransformer> solToUpdateInUpdate =
      getMethodData().getSolToUpdateInUpdateMatTrans();
    
    solToUpdateInUpdate->setMatrix(state);
    const RealMatrix& tMatrix = *solToUpdateInUpdate->getMatrix();
    flux = tMatrix*_tmpFlux;
  }
}

//////////////////////////////////////////////////////////////////////////////

void WeakSlipWallEuler2D::setFaceNormal(const CFuint faceID,
                                        RealVector& normal)
{

  // get the data handle for the states
  DataHandle< InwardNormalsData*> normals = socket_normals.getDataHandle();
  DataHandle<Common::Trio<CFuint, CFuint, Common::SafePtr<Framework::TopologicalRegionSet> > >
    faceNeighCell = socket_faceNeighCell.getDataHandle();

  const CFuint cellTrsID = faceNeighCell[faceID].first;
  const CFuint iFaceLocal = faceNeighCell[faceID].second;
  Common::SafePtr<TopologicalRegionSet> cellTrs = faceNeighCell[faceID].third;
  const CFuint cellLocalID = cellTrs->getLocalGeoID(cellTrsID);

  normal[XX] = -normals[cellLocalID]->getFaceNormComp(iFaceLocal, XX);
  normal[YY] = -normals[cellLocalID]->getFaceNormComp(iFaceLocal, YY);
}

//////////////////////////////////////////////////////////////////////////////

} // namespace FluctSplit



} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////
