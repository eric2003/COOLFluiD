#include "LUSGSMethod/LUSGSMethod.hh"
#include "LUSGSMethod/AddPastRhs.hh"


//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::Framework;
using namespace COOLFluiD::Common;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Numerics {

    namespace LUSGSMethod {

//////////////////////////////////////////////////////////////////////////////

MethodCommandProvider<AddPastRhs, LUSGSIteratorData, LUSGSMethodModule>
    addPastRhsProvider("AddPastRhs");

//////////////////////////////////////////////////////////////////////////////

AddPastRhs::AddPastRhs(std::string name) :
  LUSGSIteratorCom(name),
  socket_rhsCurrStatesSet("rhsCurrStatesSet"),
  socket_statesSetIdx("statesSetIdx"),
  socket_statesSetStateIDs("statesSetStateIDs"),
  socket_isStatesSetParUpdatable("isStatesSetParUpdatable"),
  socket_pastRhs("pastRhs"),
  m_nbrEqs()
{
}

//////////////////////////////////////////////////////////////////////////////

void AddPastRhs::execute()
{
  // Gets current states set index
  DataHandle< CFint > statesSetIdx = socket_statesSetIdx.getDataHandle();
  const CFuint currIdx = statesSetIdx[0];

  // get isStatesSetParUpdatable data handle
  DataHandle< bool > isStatesSetParUpdatable = socket_isStatesSetParUpdatable.getDataHandle();

  if (isStatesSetParUpdatable[currIdx])
  {
    // get the current states ID
    DataHandle< vector< CFuint > > statesSetStateIDs = socket_statesSetStateIDs.getDataHandle();
    const vector< CFuint >& currStatesIDs = statesSetStateIDs[currIdx];
    const CFuint currNbrStates = currStatesIDs.size();

    // get the rhs vectors
    DataHandle< CFreal > rhsCurrStatesSet = socket_rhsCurrStatesSet.getDataHandle();

    // get past rhs data handle
    DataHandle<CFreal> pastRhs = socket_pastRhs.getDataHandle();

    // add past rhs to rhs
    CFuint resIdx = 0;
    for (CFuint iState = 0; iState < currNbrStates; ++iState)
    {
      const CFuint stateID = currStatesIDs[iState];
      for (CFuint iEq = 0; iEq < m_nbrEqs; ++iEq, ++resIdx)
      {
        rhsCurrStatesSet[resIdx] += pastRhs(stateID,iEq,m_nbrEqs);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////

void AddPastRhs::setup()
{
  CFAUTOTRACE;

  // call setup of parent class
  LUSGSIteratorCom::setup();

  // get the number of equations
  m_nbrEqs = PhysicalModelStack::getActive()->getNbEq();
}

//////////////////////////////////////////////////////////////////////////////

vector<SafePtr<BaseDataSocketSink> > AddPastRhs::needsSockets()
{
  vector<SafePtr<BaseDataSocketSink> > result;

  result.push_back(&socket_rhsCurrStatesSet);
  result.push_back(&socket_statesSetIdx);
  result.push_back(&socket_statesSetStateIDs);
  result.push_back(&socket_isStatesSetParUpdatable);
  result.push_back(&socket_pastRhs);

  return result;
}

//////////////////////////////////////////////////////////////////////////////

    } // namespace LUSGSMethod

  } // namespace Numerics

} // namespace COOLFluiD
