// Copyright (C) 2012 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef COOFluiD_Environment_FactoryBase_hh
#define COOFluiD_Environment_FactoryBase_hh

//////////////////////////////////////////////////////////////////////////////

#include "Common/NonCopyable.hh"
#include "Common/COOLFluiD.hh"
#include "Environment/Environment.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Common { class ProviderBase; }

  namespace Environment {

//////////////////////////////////////////////////////////////////////////////

/// This class serves as a base class for factory's so that all factories
/// can be held by a FactoryRegistry
/// @author Tiago Quintino
class Environment_API FactoryBase :
  public Common::NonCopyable<FactoryBase> {

public: // methods

  /// @return the name of the type of this factory
  virtual std::string getTypeName() const = 0;

  /// @return all the providers in this Factory in a std::vector
  virtual std::vector<Common::ProviderBase*> getAllProviders() = 0;

}; // end class FactoryBase

//////////////////////////////////////////////////////////////////////////////

  } // namespace Environment

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOFluiD_Environment_FactoryBase_hh
