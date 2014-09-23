
#include "CoordinateLinker.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Numerics {
	
		namespace ExplicitFilters {

//////////////////////////////////////////////////////////////////////////////

CoordinateLinker::CoordinateLinker(const std::string& name) :
  Framework::MethodStrategy<FilterData>(name)
{
}

//////////////////////////////////////////////////////////////////////////////


CoordinateLinker::~CoordinateLinker()
{
}


//////////////////////////////////////////////////////////////////////////////
	
	  } // end of namespace ExplicitFilters
		
  } // namespace Numerics

} // namespace COOLFluiD
