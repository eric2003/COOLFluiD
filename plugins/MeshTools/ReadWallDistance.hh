// Copyright (C) 2012 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef COOLFluiD_MeshTools_ReadWallDistance_hh
#define COOLFluiD_MeshTools_ReadWallDistance_hh

//////////////////////////////////////////////////////////////////////////////

#include "Framework/DataProcessingData.hh"
#include "Framework/Storage.hh"
#include "Framework/DataSocketSource.hh"
#include "Framework/DataSocketSink.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace MeshTools {

//////////////////////////////////////////////////////////////////////////////

/**
 *
 * This class computes the distance from the states to the wall
 * and outputs to a file
 *
 * @author Thomas Wuilbaut
 *
 */

class ReadWallDistance : public Framework::DataProcessingCom {
public:

  /**
   * Defines the Config Option's of this class
   * @param options a OptionList where to add the Option's
   */
  static void defineConfigOptions(Config::OptionList& options);

  /**
   * Constructor.
   */
  ReadWallDistance(const std::string& name);

  /**
   * Default destructor
   */
  ~ReadWallDistance();

  /**
   * Set up private data and data of the aggregated classes
   * in this command before processing phase
   */
  void setup();

  /**
   * Unset up private data and data of the aggregated classes
   * in this command
   */
  void unsetup();

  /**
   * Returns the DataSocket's that this command needs as sources
   * @return a vector of SafePtr with the DataSockets
   */
  std::vector<Common::SafePtr<Framework::BaseDataSocketSource> > providesSockets();

  /**
   * Returns the DataSocket's that this command needs as sinks
   * @return a vector of SafePtr with the DataSockets
   */
  std::vector<Common::SafePtr<Framework::BaseDataSocketSink> > needsSockets();

  /**
   * Execute on a set of dofs
   */
  void execute();

  /**
   * Configures this object with supplied arguments.
   */
  virtual void configure ( Config::ConfigArgs& args );

private: //data

  /// socket for the qualityCell storage
  Framework::DataSocketSource<CFreal> socket_wallDistance;

  /// socket for State's
  Framework::DataSocketSink < Framework::State* , Framework::GLOBAL > socket_states;

  /// Name of Output File where to read the distances.
  std::string _nameInputFile;

  /// Output File Stream
  std::ofstream _inputFile;

}; // end of class ReadWallDistance

//////////////////////////////////////////////////////////////////////////////

  } // namespace MeshTools

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_MeshTools_ReadWallDistance_hh
