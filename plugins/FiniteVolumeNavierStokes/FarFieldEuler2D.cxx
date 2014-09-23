#include "FiniteVolumeNavierStokes/FiniteVolumeNavierStokes.hh"
#include "FiniteVolumeNavierStokes/FarFieldEuler2D.hh"
#include "Framework/MethodCommandProvider.hh"
#include "NavierStokes/EulerVarSet.hh"
#include "Framework/MeshData.hh"
#include "Framework/NamespaceSwitcher.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::Framework;
using namespace COOLFluiD::Common;
using namespace COOLFluiD::Physics::NavierStokes;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Numerics {

    namespace FiniteVolume {

//////////////////////////////////////////////////////////////////////////////

MethodCommandProvider<FarFieldEuler2D, CellCenterFVMData, FiniteVolumeNavierStokesModule> 
farFieldEuler2DFVMCCProvider("FarFieldEuler2DFVMCC");

//////////////////////////////////////////////////////////////////////////////

void FarFieldEuler2D::defineConfigOptions(Config::OptionList& options)
{
   options.addConfigOption< CFreal >("Uinf","x velocity");
   options.addConfigOption< CFreal >("Vinf","y velocity");
   options.addConfigOption< CFreal >("Pinf","static pressure");
   options.addConfigOption< CFreal >("Tinf","static temperature");
   options.addConfigOption< std::vector<std::string> >("Vars","Definition of the Variables.");
   options.addConfigOption< std::vector<std::string> >("Def","Definition of the Functions.");
   options.addConfigOption< std::string >("InputVar","Input variables.");

}

//////////////////////////////////////////////////////////////////////////////

FarFieldEuler2D::FarFieldEuler2D(const std::string& name) :
  FVMCC_BC(name),
  _varSet(CFNULL),
  _dataInnerState(),
  _dataGhostState(),
  _PuvT(4),
  _useFunction(false),
  _bCoord(),
  _inputToUpdateVar(),
  _input()
{
   addConfigOptionsTo(this);
  _temperature = 0.0;
   setParameter("Tinf",&_temperature);

  _pressure = 0.0;
   setParameter("Pinf",&_pressure);

  _uInf = 0.0;
   setParameter("Uinf",&_uInf);

  _vInf = 0.0;
   setParameter("Vinf",&_vInf);

  _functions = std::vector<std::string>();
   setParameter("Def",&_functions);

  _vars = std::vector<std::string>();
   setParameter("Vars",&_vars);

   _inputVarStr = "Null";
   setParameter("InputVar",&_inputVarStr);


}

//////////////////////////////////////////////////////////////////////////////

FarFieldEuler2D::~FarFieldEuler2D()
{
}

//////////////////////////////////////////////////////////////////////////////

void FarFieldEuler2D::configure ( Config::ConfigArgs& args )
{
  FVMCC_BC::configure(args);


  const std::string name = getMethodData().getNamespace();

  Common::SafePtr<Namespace> nsp =
    NamespaceSwitcher::getInstance().getNamespace(name);

  Common::SafePtr<PhysicalModel> physModel =
    PhysicalModelStack::getInstance().getEntryByNamespace(nsp);

  /// @todo Remove this !!!
  _updateVarStr = "PuvT";

  // create the transformer from input to update variables
  if (_inputVarStr == "Null") {
    _inputVarStr = _updateVarStr;
  }

  const std::string provider = VarSetTransformer::getProviderName
    (physModel->getConvectiveName(), _inputVarStr, _updateVarStr);

  _inputToUpdateVar =
    Environment::Factory<VarSetTransformer>::getInstance().getProvider(provider)->
    create(physModel->getImplementor());

  cf_assert(_inputToUpdateVar.isNotNull());

  if(!_functions.empty())
  {
    _vFunction.setFunctions(_functions);
    _vFunction.setVariables(_vars);
    try {
      _vFunction.parse();
      _useFunction = true;
    }
    catch (Common::ParserException& e) {
      CFout << e.what() << "\n";
      throw; // retrow the exception to signal the error to the user
    }
  }
}

//////////////////////////////////////////////////////////////////////////////

void FarFieldEuler2D::setup()
{

  FVMCC_BC::setup();

  _input = new State();

  const CFuint maxNbStatesInCell = MeshDataStack::getActive()->Statistics().getMaxNbStatesInCell();
  _inputToUpdateVar->setup(maxNbStatesInCell);

  _varSet = getMethodData().getUpdateVar().d_castTo<EulerVarSet>();
  _varSet->getModel()->resizePhysicalData(_dataInnerState);
  _varSet->getModel()->resizePhysicalData(_dataGhostState);

  _pressure/=_varSet->getModel()->getPressRef();
  _temperature/=_varSet->getModel()->getTempRef();
  _uInf /= _varSet->getModel()->getVelRef();
  _vInf /= _varSet->getModel()->getVelRef();
}

//////////////////////////////////////////////////////////////////////////////

void FarFieldEuler2D::setGhostState(GeometricEntity *const face)
 {

   State *const innerState = face->getState(0);
   State *const ghostState = face->getState(1);

   if(_useFunction)
   {
	 std::cout << "Don't want to use function\n Aborting!\n"; abort();
     // coordinate of the boundary point
     _bCoord = (innerState->getCoordinates() +
               ghostState->getCoordinates());
     _bCoord *= 0.5;

     // (*ghostState) = 2*bcState - (*innerState)
     _vFunction.evaluate(_bCoord, *_input);
      _PuvT = *_inputToUpdateVar->transform(_input);

     _pressure = _PuvT[0] / _varSet->getModel()->getPressRef();
     _uInf = _PuvT[1] / _varSet->getModel()->getVelRef();
     _vInf = _PuvT[2] / _varSet->getModel()->getVelRef();
     _temperature = _PuvT[3] / _varSet->getModel()->getTempRef();
   }

   const CFreal gamma = _varSet->getModel()->getGamma();
   const CFreal gammaDivGammaMinus1 = gamma/(gamma -1.0);
   const CFreal R = _varSet->getModel()->getR();

   const CFuint faceID = face->getID();
   const CFuint startID = faceID*PhysicalModelStack::getActive()->getDim();

   DataHandle<CFreal> normals = socket_normals.getDataHandle();

   CFreal nx = normals[startID];
   CFreal ny = normals[startID + 1];
   const CFreal invFaceLength = 1./sqrt(nx*nx + ny*ny);
   nx *= invFaceLength;
   ny *= invFaceLength;

   // set the physical data starting from the inner state
   _varSet->computePhysicalData(*innerState, _dataInnerState);

   const CFreal u = _dataInnerState[EulerTerm::VX];
   const CFreal v = _dataInnerState[EulerTerm::VY];
   const CFreal rho = _dataInnerState[EulerTerm::RHO];
   const CFreal vn = u*nx + v*ny;
   const CFreal pInnerState = _dataInnerState[EulerTerm::P];
   const CFreal aInnerState = _dataInnerState[EulerTerm::A];
   const CFreal machInner = vn / aInnerState;

//   std::cout << "*innerState = " << *innerState<< "\n";
//   std::cout << "u = " << u << "\n";
//   std::cout << "v = " << v << "\n";
//   std::cout << "rho = " << rho << "\n";
//   std::cout << "pInnerState = " << pInnerState << "\n";
//   std::cout << "machInner = " << machInner << "\n";
//   std::cout << "TInner = " << aInnerState*aInnerState/(1.4*R) << "\n" ; 

   // depending on the sign and magnitude of the local Mach number,
   // number of variables to be specified are determined

   // supersonic outlet case
   if (machInner >= 1.0) {
     (*ghostState)[0] = (*innerState)[0];
     (*ghostState)[1] = (*innerState)[1];
     (*ghostState)[2] = (*innerState)[2];
     (*ghostState)[3] = (*innerState)[3];
   }

   // supersonic inlet case
   if (machInner <= -1.0) {
     const CFreal rhoInf = _pressure/(R*_temperature);

     // set all the physical data corresponding to the ghost state
     _dataGhostState[EulerTerm::RHO] = 2.0*rhoInf - rho;
     _dataGhostState[EulerTerm::VX] = 2.0*_uInf - u;
     _dataGhostState[EulerTerm::VY] = 2.0*_vInf - v;
     _dataGhostState[EulerTerm::P] = 2.0*_pressure - pInnerState;
     _dataGhostState[EulerTerm::A] = sqrt(gamma*_dataGhostState[EulerTerm::P]/
					  _dataGhostState[EulerTerm::RHO]);
     _dataGhostState[EulerTerm::V] = sqrt(_dataGhostState[EulerTerm::VX]*
					  _dataGhostState[EulerTerm::VX] +
					  _dataGhostState[EulerTerm::VY]*
					  _dataGhostState[EulerTerm::VY]);

     _dataGhostState[EulerTerm::H] = (gammaDivGammaMinus1*_dataGhostState[EulerTerm::P]
				      + 0.5*_dataGhostState[EulerTerm::RHO]*
				      _dataGhostState[EulerTerm::V]*
				      _dataGhostState[EulerTerm::V])/
       _dataGhostState[EulerTerm::RHO];

     // set the ghost state starting from the physical data
     _varSet->computeStateFromPhysicalData(_dataGhostState, *ghostState);
   }

   // subsonic outlet case
   if ((machInner < 1.0) && (machInner >= 0.0))  {

     _dataGhostState[EulerTerm::RHO] = _dataInnerState[EulerTerm::RHO];
     _dataGhostState[EulerTerm::VX] = _dataInnerState[EulerTerm::VX];
     _dataGhostState[EulerTerm::VY] = _dataInnerState[EulerTerm::VY];
     _dataGhostState[EulerTerm::V] = _dataInnerState[EulerTerm::V];
     _dataGhostState[EulerTerm::P] = 2.0*_pressure - pInnerState;
     _dataGhostState[EulerTerm::H] = (gammaDivGammaMinus1*_dataGhostState[EulerTerm::P]
				      + 0.5*_dataGhostState[EulerTerm::RHO]*
				      _dataGhostState[EulerTerm::V]*
				      _dataGhostState[EulerTerm::V])/
       _dataGhostState[EulerTerm::RHO];
     _dataGhostState[EulerTerm::A] = sqrt(gamma*_dataGhostState[EulerTerm::P]/
					  _dataGhostState[EulerTerm::RHO]);

     _varSet->computeStateFromPhysicalData(_dataGhostState, *ghostState);
// std::cout <<"Sub Outlet: _dataGhostState" << _dataGhostState << std::endl;
// std::cout <<"Sub Outlet: *ghostState" << *ghostState << std::endl;
   }

   // subsonic inlet case
   if ((machInner > -1.0) && (machInner < 0.0)) {

     _dataGhostState[EulerTerm::RHO] = pInnerState/(R*_temperature);
     _dataGhostState[EulerTerm::VX] = 2.0*_uInf - u;
     _dataGhostState[EulerTerm::VY] = 2.0*_vInf - v;
     _dataGhostState[EulerTerm::V] = sqrt(_dataGhostState[EulerTerm::VX]*
					  _dataGhostState[EulerTerm::VX] +
					  _dataGhostState[EulerTerm::VY]*
					  _dataGhostState[EulerTerm::VY]);
     _dataGhostState[EulerTerm::P] = pInnerState;
     _dataGhostState[EulerTerm::H] = (gammaDivGammaMinus1*_dataGhostState[EulerTerm::P]
				      + 0.5*_dataGhostState[EulerTerm::RHO]*
				      _dataGhostState[EulerTerm::V]*
				      _dataGhostState[EulerTerm::V])/
       _dataGhostState[EulerTerm::RHO];

     _dataGhostState[EulerTerm::A] = sqrt(gamma*_dataGhostState[EulerTerm::P]/
					  _dataGhostState[EulerTerm::RHO]);
     _dataGhostState[EulerTerm::T] = _temperature; // JGM
     _varSet->computeStateFromPhysicalData(_dataGhostState, *ghostState);
 // std::cout <<"Sub Inlet: _dataGhostState" << _dataGhostState << std::endl;
 // std::cout <<"Sub Inlet: *ghostState" << *ghostState << std::endl;

   }
 }

//////////////////////////////////////////////////////////////////////////////

    } // namespace FiniteVolume

  } // namespace Numerics

} // namespace COOLFluiD
