#include "Environment/ObjectProvider.hh"

#include "UFEM/TetraP1P1Cell/NStokesStabilized.hh"
#include "UFEM/TetraP1P1Cell/UFEMTetraP1P1Cell.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {
  namespace UFEM {
    namespace TetraP1P1Cell {

using namespace std;
using namespace COOLFluiD::Environment;
using namespace COOLFluiD::Framework;
using namespace COOLFluiD::Common;

//////////////////////////////////////////////////////////////////////////////

Environment::ObjectProvider < NStokesStabilized,
                              UFEMTerm,
                              UFEMTetraP1P1CellPlugin,
                              UFEMTerm::NARGS >
aTriagP1P1Cell_NStokesStabilized_Provider ( "TetraP1P1Cell_NStokesStabilized" );

//////////////////////////////////////////////////////////////////////////////

void NStokesStabilized::defineConfigOptions ( Config::OptionList& options )
{
  CFAUTOTRACE;

  options.addConfigOption< CFreal >("RhoRef","Reference Density");
  options.addConfigOption< CFreal >("TRef","Reference Temperature");
  options.addConfigOption< CFreal >("URef","Reference Velocity");
  options.addConfigOption< CFreal >("MuLam", "Laminar Molecular Viscosity");
  options.addConfigOption< CFreal >("Beta", "Volumetric heat expansion coefficient");
  options.addConfigOption< std::vector<CFreal> >("G", "Gravitational Acceleration");
}

//////////////////////////////////////////////////////////////////////////////

NStokesStabilized::NStokesStabilized ( const std::string& name, Common::SafePtr<ElemProps> props  ) :
  UFEMTerm ( name, props ),
  m_cellprops ( *props.d_castTo<TetraP1P1Cell::CellProps>() ),
  socket_interStates("interStates")
{
  CFAUTOTRACE;
  addConfigOptionsTo(this);

  //Default values
  CFuint nbDim = PhysicalModelStack::getActive()->getDim();
  m_G.resize(nbDim);
  for (CFuint i=0; i<m_G.size(); i++) m_G[i] = 0.;
  m_RhoRef = 1.; 
  m_TRef   = 0.; 
  m_URef   = 1.; 
  m_MuLam  = 1.e-2; 
  m_Beta   = 0.001; 

  setParameter( "RhoRef", &m_RhoRef );
  setParameter( "TRef",   &m_TRef );
  setParameter( "URef",   &m_URef );
  setParameter( "MuLam",  &m_MuLam );
  setParameter( "Beta",   &m_Beta );
  setParameter( "G",      &m_G );

}

//////////////////////////////////////////////////////////////////////////////

NStokesStabilized::~NStokesStabilized()
{
  CFAUTOTRACE;
}

//////////////////////////////////////////////////////////////////////////////

void NStokesStabilized::configure ( Config::ConfigArgs& args )
{
  CFAUTOTRACE;
  UFEMTerm::configure ( args );

  CFLog(INFO, getClassName() << ": reference density: "           << m_RhoRef    << "\n");
  CFLog(INFO, getClassName() << ": reference temperature: "       << m_TRef      << "\n");
  CFLog(INFO, getClassName() << ": reference velocity: "          << m_URef      << "\n");
  CFLog(INFO, getClassName() << ": laminar viscosity: "           << m_MuLam     << "\n");
  CFLog(INFO, getClassName() << ": volumetric heat expansion: "   << m_Beta      << "\n");
  std::ostringstream sstr;
  sstr.str(""); for (CFuint i=0; i<m_G.size(); i++) sstr << m_G[i] << " ";
  CFLog(INFO, getClassName() << ": gravitational acceleration: "  << sstr.str()     << "\n");
  getMethodData().setRhoElm(m_RhoRef);
  getMethodData().setMuElm(m_MuLam);
}

//////////////////////////////////////////////////////////////////////////////

void NStokesStabilized::setup ()
{
  CFAUTOTRACE;
  UFEMTerm::setup ();

  socket_interStates.setParentNamespace ( getMethodData().getNamespace() );
}

//////////////////////////////////////////////////////////////////////////////

void NStokesStabilized::unsetup ()
{
  CFAUTOTRACE;
  UFEMTerm::unsetup ();
}

//////////////////////////////////////////////////////////////////////////////

void NStokesStabilized::compute ( const Framework::GeometricEntity& cell , AssemblyData& adata )
{
  CFAUTOTRACE;

#define kronecker(i,j) ((i)==(j)?1.:0.)

  const CFuint nbEqs = PhysicalModelStack::getActive()->getNbEq();

  RealVector estate(nbEqs);
  estate = 0.;

  const vector< State* >& states = cell.getStates();
  DataHandle<Framework::State*> interStates = socket_interStates.getDataHandle();
  for (CFuint iState=0; iState<4; ++iState) {
    State& state = *states[iState];
    State& interState = *interStates[state.getLocalID()];
    for (CFuint iEq=0; iEq<nbEqs; ++iEq) {
      estate[iEq] += interState[iEq];
    }
  }
  for (CFuint iEq=0; iEq<nbEqs; ++iEq) estate[iEq] *= 1./4.;

  CFuint Pi,Ui,Vi,Wi,Pj,Uj,Vj,Wj;
  CFreal val;

  CFreal nueff  = getMethodData().getMuElm()/getMethodData().getRhoElm();
  CFreal gx  = 0.;//m_G[0];
  CFreal gy  = 0.;//m_G[1];
  CFreal gz  = 0.;//m_G[2];

  // time scales
  CFreal fc  = .5;
  CFreal umag=sqrt(estate[1]*estate[1]+estate[2]*estate[2]+estate[3]*estate[3]);
  CFreal tauSUPG=0.;
  const CellProps::CellData &celldata=m_cellprops.getCellData();

  if (umag!=0.)
  {
    CFreal sx=estate[1]/umag;
    CFreal sy=estate[2]/umag;
    CFreal sz=estate[3]/umag;
    CFreal h=0.;
    h+=fabs(sx*celldata.nx[0]+sy*celldata.ny[0]+sz*celldata.nz[0]);
    h+=fabs(sx*celldata.nx[1]+sy*celldata.ny[1]+sz*celldata.nz[1]);
    h+=fabs(sx*celldata.nx[2]+sy*celldata.ny[2]+sz*celldata.nz[2]);
    h+=fabs(sx*celldata.nx[3]+sy*celldata.ny[3]+sz*celldata.nz[3]);
    h/=(2.*celldata.vol);
    h=1./h;
    CFreal ree=umag*h/(2.*nueff);
    CFreal xi=max(0.,min(ree/3.,1.));
    tauSUPG=h*xi/(2.*umag);
  }
  CFreal he=pow(3./4./3.141592654*celldata.vol,1./3.);
  CFreal ree=m_URef*he/(2.*nueff);
  CFreal xi=max(0.,min(ree/3.,1.));
  CFreal tauPSPG=he*xi/(2.*m_URef);
  CFreal tauBULK=he*m_URef/xi;

//  tauSUPG*=0.;
//  tauBULK*=0.;

  Pi=0; Ui=1; Vi=2; Wi=3;
  for(CFuint i=0; i<4; ++i) {

    CFreal u_ni=estate[1]*celldata.nx[i]+estate[2]*celldata.ny[i]+estate[3]*celldata.nz[i];
/*
     //gravity
     adata.b[Ui] += -m_Beta*(estate[4] - m_TRef)*gx*celldata.vol/4.;
     adata.b[Vi] += -m_Beta*(estate[4] - m_TRef)*gy*celldata.vol/4.;
     adata.b[Wi] += -m_Beta*(estate[4] - m_TRef)*gz*celldata.vol/4.;
*/
    Pj=0; Uj=1; Vj=2; Wj=3;
    for(CFuint j=0; j<4; ++j) {
/*
      for(CFuint k=0; k<4; ++k){

        CFreal uk=estate[1];
        CFreal vk=estate[2];
        CFreal wk=estate[3];
        CFreal uknj=uk*celldata.nx[j]+vk*celldata.ny[j]+wk*celldata.nz[j];

        // Convection (Standard + SUPG)
        val  = 1./60.*uknj*(1.+kronecker(i,k));
        val += tauSUPG/(36.*celldata.vol)*uknj*u_ni;
        adata.A(Ui,Uj) += val;
        adata.A(Vi,Vj) += val;
        adata.A(Wi,Wj) += val;

        // Convection (PSPG)
        val = tauPSPG/(36.*celldata.vol)*uknj;
        adata.A(Pi,Uj) += val*celldata.nx[i];
        adata.A(Pi,Vj) += val*celldata.ny[i];
        adata.A(Pi,Wj) += val*celldata.nz[i];

        // Convection Skewsymm (Standard + SUPG)
        val  = fc/60.*(1.+kronecker(i,k));
        val += fc*tauSUPG/(36.*celldata.vol)*u_ni;
        adata.A(Ui,Uj) += val*uk*celldata.nx[j];
        adata.A(Ui,Vj) += val*uk*celldata.ny[j];
        adata.A(Ui,Wj) += val*uk*celldata.nz[j];
        adata.A(Vi,Uj) += val*vk*celldata.nx[j];
        adata.A(Vi,Vj) += val*vk*celldata.ny[j];
        adata.A(Vi,Wj) += val*vk*celldata.nz[j]; 
        adata.A(Wi,Uj) += val*vk*celldata.nx[j];
        adata.A(Wi,Vj) += val*vk*celldata.ny[j];
        adata.A(Wi,Wj) += val*vk*celldata.nz[j]; 

        // Convection Skewsymm (PSPG)
        val = fc*tauPSPG/(36.*celldata.vol);
        adata.A(Pi,Uj) += val*celldata.nx[i]*uk*celldata.nx[j];
        adata.A(Pi,Vj) += val*celldata.nx[i]*uk*celldata.ny[j];
        adata.A(Pi,Wj) += val*celldata.nx[i]*uk*celldata.nz[j];
        adata.A(Pi,Uj) += val*celldata.ny[i]*vk*celldata.nx[j];
        adata.A(Pi,Vj) += val*celldata.ny[i]*vk*celldata.ny[j];
        adata.A(Pi,Wj) += val*celldata.ny[i]*vk*celldata.nz[j];
        adata.A(Pi,Uj) += val*celldata.nz[i]*vk*celldata.nx[j];
        adata.A(Pi,Vj) += val*celldata.nz[i]*vk*celldata.ny[j];
        adata.A(Pi,Wj) += val*celldata.nz[i]*vk*celldata.nz[j];

      }
*/
      CFreal uk=estate[1];
      CFreal vk=estate[2];
      CFreal wk=estate[3];
      CFreal uknj=uk*celldata.nx[j]+vk*celldata.ny[j]+wk*celldata.nz[j];

      // Convection (Standard + SUPG)
      val  = 1./12.*uknj;
      val += tauSUPG/(9.*celldata.vol)*uknj*u_ni;
      adata.A(Ui,Uj) += val;
      adata.A(Vi,Vj) += val;
      adata.A(Wi,Wj) += val;

      // Convection (PSPG)
      val = tauPSPG/(9.*celldata.vol)*uknj;
      adata.A(Pi,Uj) += val*celldata.nx[i];
      adata.A(Pi,Vj) += val*celldata.ny[i];
      adata.A(Pi,Wj) += val*celldata.nz[i];

      // Convection Skewsymm (Standard + SUPG)
      val  = fc/12.;
      val += fc*tauSUPG/(9.*celldata.vol)*u_ni;
      adata.A(Ui,Uj) += val*uk*celldata.nx[j];
      adata.A(Ui,Vj) += val*uk*celldata.ny[j];
      adata.A(Ui,Wj) += val*uk*celldata.nz[j];
      adata.A(Vi,Uj) += val*vk*celldata.nx[j];
      adata.A(Vi,Vj) += val*vk*celldata.ny[j];
      adata.A(Vi,Wj) += val*vk*celldata.nz[j]; 
      adata.A(Wi,Uj) += val*wk*celldata.nx[j];
      adata.A(Wi,Vj) += val*wk*celldata.ny[j];
      adata.A(Wi,Wj) += val*wk*celldata.nz[j]; 

      // Convection Skewsymm (PSPG)
      val = fc*tauPSPG/(9.*celldata.vol);
      adata.A(Pi,Uj) += val*celldata.nx[i]*uk*celldata.nx[j];
      adata.A(Pi,Vj) += val*celldata.nx[i]*uk*celldata.ny[j];
      adata.A(Pi,Wj) += val*celldata.nx[i]*uk*celldata.nz[j];
      adata.A(Pi,Uj) += val*celldata.ny[i]*vk*celldata.nx[j];
      adata.A(Pi,Vj) += val*celldata.ny[i]*vk*celldata.ny[j];
      adata.A(Pi,Wj) += val*celldata.ny[i]*vk*celldata.nz[j];
      adata.A(Pi,Uj) += val*celldata.nz[i]*wk*celldata.nx[j];
      adata.A(Pi,Vj) += val*celldata.nz[i]*wk*celldata.ny[j];
      adata.A(Pi,Wj) += val*celldata.nz[i]*wk*celldata.nz[j];


      //difusion (Standard)
      val = nueff/(9.*celldata.vol);
      adata.A(Ui,Uj)+=val*(4./3.*celldata.nx[i]*celldata.nx[j]+      celldata.ny[i]*celldata.ny[j]+      celldata.nz[i]*celldata.nz[j]);
      adata.A(Ui,Vj)+=val*       celldata.nx[i]*celldata.ny[j];
      adata.A(Ui,Wj)+=val*       celldata.nx[i]*celldata.nz[j];
      adata.A(Vi,Uj)+=val*       celldata.ny[i]*celldata.nx[j];
      adata.A(Vi,Vj)+=val*(      celldata.nx[i]*celldata.nx[j]+4./3.*celldata.ny[i]*celldata.ny[j]+      celldata.nz[i]*celldata.nz[j]);
      adata.A(Vi,Wj)+=val*       celldata.ny[i]*celldata.nz[j];
      adata.A(Wi,Uj)+=val*       celldata.nz[i]*celldata.nx[j];
      adata.A(Wi,Vj)+=val*       celldata.nz[i]*celldata.ny[j];
      adata.A(Wi,Wj)+=val*(      celldata.nx[i]*celldata.nx[j]+      celldata.ny[i]*celldata.ny[j]+4./3.*celldata.nz[i]*celldata.nz[j]);

      // Pressure (Standard + SUPG)
      val  = 1./(12.*m_RhoRef);
      val += tauSUPG/(9.*m_RhoRef*celldata.vol)*u_ni;
      adata.A(Ui,Pj) += celldata.nx[j]*val;
      adata.A(Vi,Pj) += celldata.ny[j]*val;
      adata.A(Wi,Pj) += celldata.nz[j]*val;

      // Pressure (PSPG)
      val = tauPSPG/(9.*m_RhoRef*celldata.vol)*(celldata.nx[i]*celldata.nx[j]+celldata.ny[i]*celldata.ny[j]+celldata.nz[i]*celldata.nz[j]);
      adata.A(Pi,Pj) += val;

      // Continuity (Standard)
      val = 1./12.;
      adata.A(Pi,Uj) += val*celldata.nx[j];
      adata.A(Pi,Vj) += val*celldata.ny[j];
      adata.A(Pi,Wj) += val*celldata.nz[j];

      // Bulk viscosity (Standard)
      val = tauBULK/(9.*celldata.vol);
      adata.A(Ui,Uj) += val*celldata.nx[i]*celldata.nx[j];
      adata.A(Ui,Vj) += val*celldata.nx[i]*celldata.ny[j];
      adata.A(Ui,Wj) += val*celldata.nx[i]*celldata.nz[j];
      adata.A(Vi,Uj) += val*celldata.ny[i]*celldata.nx[j];
      adata.A(Vi,Vj) += val*celldata.ny[i]*celldata.ny[j];
      adata.A(Vi,Wj) += val*celldata.ny[i]*celldata.nz[j];
      adata.A(Wi,Uj) += val*celldata.nz[i]*celldata.nx[j];
      adata.A(Wi,Vj) += val*celldata.nz[i]*celldata.ny[j];
      adata.A(Wi,Wj) += val*celldata.nz[i]*celldata.nz[j];

      // Time (Standard + SUPG)
      val  = celldata.vol/20.*(1.+kronecker(i,j));
      val += tauSUPG/12.*u_ni;
      adata.T(Ui,Uj) += val;
      adata.T(Vi,Vj) += val;
      adata.T(Wi,Wj) += val;

      // Time (PSPG)
      val = tauPSPG/12.;
      adata.T(Pi,Uj) += val*celldata.nx[i];
      adata.T(Pi,Vj) += val*celldata.ny[i];
      adata.T(Pi,Wj) += val*celldata.nz[i];

      // Increasing diagonal dominance - crank nicholson related
      adata.A(Pi,Pj) *= 2.;
      adata.A(Pi,Uj) *= 2.;
      adata.A(Pi,Vj) *= 2.;
      adata.A(Pi,Wj) *= 2.;

      Pj+=nbEqs; Uj+=nbEqs; Vj+=nbEqs; Wj+=nbEqs;
    }
    Pi+=nbEqs; Ui+=nbEqs; Vi+=nbEqs; Wi+=nbEqs;
  }

  return;

#undef kronecker

}

//////////////////////////////////////////////////////////////////////////////

std::vector< Common::SafePtr< BaseDataSocketSource > > NStokesStabilized::providesSockets()
{
  CFAUTOTRACE;
  std::vector<Common::SafePtr<BaseDataSocketSource> > result;

  return result;
}

//////////////////////////////////////////////////////////////////////////////

std::vector< Common::SafePtr< BaseDataSocketSink > > NStokesStabilized::needsSockets()
{
  CFAUTOTRACE;
  std::vector< Common::SafePtr<BaseDataSocketSink> > result = UFEMTerm::needsSockets();

  result.push_back(&socket_interStates);

  return result;
}

//////////////////////////////////////////////////////////////////////////////

    }  // end namespace TetraP1P1Cell
  }  // end namespace UFEM
}  // end namespace COOLFluiD

