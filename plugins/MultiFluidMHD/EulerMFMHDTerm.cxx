#include "Config/BiggerThanZero.hh"
#include "MultiFluidMHD/EulerMFMHDTerm.hh"
#include "MathTools/MathConsts.hh"
#include "MultiFluidMHDModel.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::Config;
using namespace COOLFluiD::Framework;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Physics {

    namespace MultiFluidMHD {

//////////////////////////////////////////////////////////////////////////////

void EulerMFMHDTerm::defineConfigOptions(Config::OptionList& options)
{
  options.addConfigOption< CFreal , ValidateOption < BiggerThanZero > > ("gamma","Specific heat ratio.");
  options.addConfigOption< CFreal > ("Omega", "RPM in revolutions/min");
  options.addConfigOption< CFreal > ("molecularMass1", "Molecular mass of first species");
  options.addConfigOption< CFreal > ("molecularMass2", "Molecular mass of second species");
  options.addConfigOption< CFreal > ("molecularMass3", "Molecular mass of third species");
  options.addConfigOption< std::vector<CFreal> >("nonInducedElectromagnetic", "nonInduced Electromagnetic Field");
  options.addConfigOption< CFreal > ("lightSpeed", "Speed of light. It can be reduced if it is still bigger than the speed of the fluid");
}

//////////////////////////////////////////////////////////////////////////////

EulerMFMHDTerm::EulerMFMHDTerm(const std::string& name) : 
  Maxwell::MaxwellProjectionTerm(name),
  _NonInducedEMField()
{ 
  addConfigOptionsTo(this);
   
  _gamma = 5./3.;
  setParameter("gamma",&_gamma); 
  
  _omega = 0.;
  setParameter("Omega",&_omega);
  
  _K = 1.3806505e-23;			//Boltzman's constant [J/K]
  
  _epsilon = 8.854187817e-12;		//Permittivity of free space [F/m]
  
  _mu = 4*MathTools::MathConsts::CFrealPi()*1e-7;
  
  _lightSpeed = 299792458;		//light Speed m/s
  setParameter("lightSpeed",&_lightSpeed);
  
  _molecularMass1 = 9.1094e-31;		// Electron's mass [kg] source:Standart Handbook for Electrical Engineerings   
  setParameter("molecularMass1",&_molecularMass1);  
  
  _molecularMass2 = 1.6726e-27;		// Proton's mass [kg] source:Standart Handbook for Electrical Engineerings 
  setParameter("molecularMass2",&_molecularMass2);  
  
  _molecularMass3 = 1.6726e-27;		// Neutral's mass [kg/mol] equal to proton's mass   
  setParameter("molecularMass3",&_molecularMass3);
  
  _nonInducedEMField = std::vector<CFreal>();
  setParameter("nonInducedElectromagnetic",&_nonInducedEMField);
}
      
//////////////////////////////////////////////////////////////////////////////

EulerMFMHDTerm::~EulerMFMHDTerm()
{
}

//////////////////////////////////////////////////////////////////////////////

void EulerMFMHDTerm::configure ( Config::ConfigArgs& args )
{
  Maxwell::MaxwellProjectionTerm::configure(args);
  
  _NonInducedEMField.resize(6);
  
  // conversion to radiants/sec
  _omega *= (2.*MathTools::MathConsts::CFrealPi()/60.);
}

//////////////////////////////////////////////////////////////////////////////

void EulerMFMHDTerm::resizePhysicalData(RealVector& physicalData)
{
  // resize the physical data
  cf_assert(getDataSize() > 0);
  physicalData.resize(getDataSize());
}

//////////////////////////////////////////////////////////////////////////////

void EulerMFMHDTerm::setupPhysicalData()
{
  cf_assert(getDataSize() > 0);

  // set the size of each physical data in the StatesData
  resizePhysicalData(m_physicalData);
  resizePhysicalData(m_refPhysicalData);
}

//////////////////////////////////////////////////////////////////////////////

void EulerMFMHDTerm::computeNonInducedEMField(CFreal xCoord, CFreal yCoord)
{
  for (CFuint i = 0; i < 6; i++){
    _NonInducedEMField[i] = _nonInducedEMField[i];
  }
     
//   _NonInducedEMField[0] = 0.1; //Dimensional NonInduced BX Component
//   _NonInducedEMField[1] = 0; //Dimensional NonInduced BY Component
//   _NonInducedEMField[2] = 0; //Dimensional NonInduced BZ Component  
//   _NonInducedEMField[3] = 0; //Dimensional NonInduced EX Component  
//   _NonInducedEMField[4] = 0; //Dimensional NonInduced EY Component  
}

//////////////////////////////////////////////////////////////////////////////

} // namespace MultiFluidMHD

} // namespace Physics

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////
