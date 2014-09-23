// Copyright (C) 2012 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "Common/NullPointerException.hh"

namespace COOLFluiD {
namespace Common {

//////////////////////////////////////////////////////////////////////////////

NullPointerException::NullPointerException(const Common::CodeLocation& where, const std::string& what)
: Exception(where, what,"NullPointerException")
{}

//////////////////////////////////////////////////////////////////////////////

  } // namespace Common
} // namespace COOLFluiD
