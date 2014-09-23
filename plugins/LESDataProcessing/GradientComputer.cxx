
#include "GradientComputer.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace COOLFluiD::MathTools;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Numerics {
	
		namespace LESDataProcessing {

//////////////////////////////////////////////////////////////////////////////

void GradientComputer::defineConfigOptions(Config::OptionList& options)
{
  // Configuration option definitions here	

}

//////////////////////////////////////////////////////////////////////////////

GradientComputer::GradientComputer(const std::string& name) :
  Framework::MethodStrategy<LESProcessingData>(name)
{
  addConfigOptionsTo(this);
  // Setting default configurations here.
  
}

//////////////////////////////////////////////////////////////////////////////


GradientComputer::~GradientComputer()
{
}

//////////////////////////////////////////////////////////////////////////////

void GradientComputer::setup()
{
  CFAUTOTRACE; 
}

//////////////////////////////////////////////////////////////////////////////

void GradientComputer::configure ( Config::ConfigArgs& args )
{
  Framework::MethodStrategy<LESProcessingData>::configure(args);
}

//////////////////////////////////////////////////////////////////////////////
	
	  } // end of namespace LESDataProcessing
		
  } // namespace Numerics

} // namespace COOLFluiD
