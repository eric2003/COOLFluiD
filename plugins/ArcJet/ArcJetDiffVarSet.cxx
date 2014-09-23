#include "ArcJet/ArcJet.hh"
#include "ArcJetDiffVarSet.hh"
#include "ArcJet/ArcJetReactionTerm.hh"
#include "LTE/NavierStokes2DPuvtLTE.hh"
#include "LTE/NavierStokes3DPvtLTE.hh"
#include "NavierStokes/NavierStokes2DPuvt.hh"
#include "NavierStokes/NavierStokes3DPvt.hh"
#include "NavierStokes/EulerTerm.hh"
#include "Environment/ObjectProvider.hh"
#include "Framework/MultiScalarTerm.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::Framework;
using namespace COOLFluiD::Common;
using namespace COOLFluiD::Physics::NavierStokes;
using namespace COOLFluiD::Physics::LTE;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Physics {

    namespace ArcJet {

//////////////////////////////////////////////////////////////////////////////
      
Environment::ObjectProvider<ArcJetDiffVarSet
			    <NavierStokes2DPuvtLTE<MultiScalarTerm<EulerTerm> >, 
			     ArcJetReactionTerm<Framework::BaseTerm> >, 
			    DiffusiveVarSet, 
			    ArcJetModule, 2> 
arcJetLTE2DPuvtDiffProvider("ArcJetLTE2DPuvt");

Environment::ObjectProvider<ArcJetDiffVarSet
			    <NavierStokes3DPvtLTE, 
			     ArcJetReactionTerm<Framework::BaseTerm> >, 
			    DiffusiveVarSet, 
			    ArcJetModule, 2> 
arcJetLTE3DPvtDiffProvider("ArcJetLTE3DPvt");

Environment::ObjectProvider<ArcJetDiffVarSet
			    <NavierStokes2DPuvt, 
			     ArcJetReactionTerm<Framework::BaseTerm> >, 
			    DiffusiveVarSet, 
			    ArcJetModule, 2> 
arcJetPG2DPuvtDiffProvider("ArcJetPG2DPuvt");

Environment::ObjectProvider<ArcJetDiffVarSet
			    <NavierStokes3DPvt, 
			     ArcJetReactionTerm<Framework::BaseTerm> >, 
			    DiffusiveVarSet, 
			    ArcJetModule, 2> 
arcJetPG3DPvtDiffProvider("ArcJetPG3DPvt");

//////////////////////////////////////////////////////////////////////////////

    } // namespace ArcJet

  } // namespace Physics

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////
