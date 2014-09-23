// Copyright (C) 2012 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef COOLFluiD_ShapeFunctions_SetLineLagrangeP1LagrangeP0StateCoord_hh
#define COOLFluiD_ShapeFunctions_SetLineLagrangeP1LagrangeP0StateCoord_hh

//////////////////////////////////////////////////////////////////////////////

#include "Framework/SetElementStateCoord.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Framework { class Node;  }
  namespace Framework { class State; }

  namespace ShapeFunctions {

//////////////////////////////////////////////////////////////////////////////

    /**
     * This class is a functor and offers an abstract interface
     * for setting the corrisponding space coordinates (Framework::Node) in
     * the State's in a triangle with P1 geometrical and solution
     * interpolation.
     *
     * @author Andrea Lani
     */
class SetLineLagrangeP1LagrangeP0StateCoord : public Framework::SetElementStateCoord {
public:

  /**
   * Constructor
   */
  SetLineLagrangeP1LagrangeP0StateCoord() : Framework::SetElementStateCoord()
  {
  }

  /**
   * Destructor
   */
  ~SetLineLagrangeP1LagrangeP0StateCoord()
  {
  }

  /**
   * Overloading of the operator () to make this class act as a
   * functor
   * @param nodes   list of the nodes in the current element
   * @param states  list of the states in the current element
   */
  void operator() (const std::vector<Framework::Node*>& nodes,
                   std::vector<Framework::State*>& states);

  /**
   * Function allowing to update the StateCoord
   * @param nodes   list of the nodes in the current element
   * @param states  list of the states in the current element
   */
  void update(const std::vector<Framework::Node*>& nodes,
                            std::vector<Framework::State*>& states);

}; // end of class SetLineLagrangeP1LagrangeP0StateCoord

//////////////////////////////////////////////////////////////////////////////

  } // namespace ShapeFunctions

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_ShapeFunctions_SetLineLagrangeP1LagrangeP0StateCoord_hh
