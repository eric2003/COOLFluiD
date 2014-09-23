#ifndef COOLFluiD_Numerics_SpectralFV_StdInitState_hh
#define COOLFluiD_Numerics_SpectralFV_StdInitState_hh

//////////////////////////////////////////////////////////////////////////////

#include "Framework/VectorialFunction.hh"
#include "Framework/VarSetTransformer.hh"
#include "Framework/DataSocketSink.hh"
#include "SpectralFV/SpectralFVMethodData.hh"
#include "SpectralFV/SpectralFVElementData.hh"
#include "SpectralFV/LineSpectralFVElementData.hh"
#include "SpectralFV/TriagSpectralFVElementData.hh"
#include "SpectralFV/SimplexGaussIntegrator.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace SpectralFV {

//////////////////////////////////////////////////////////////////////////////

/**
 * A initalizing solution command for the spectral finite volume method using quadrature formulas
 *
 * @author Kris Van den Abeele
 *
 *
 */
class StdInitState : public SpectralFVMethodCom {
public:

  /**
   * Defines the Config Option's of this class
   * @param options a OptionList where to add the Option's
   */
  static void defineConfigOptions(Config::OptionList& options);

  /**
   * Constructor.
   */
  explicit StdInitState(const std::string& name);

  /**
   * Destructor.
   */
  ~StdInitState();

  /**
   * Set up the member data
   */
  virtual void setup();

  /**
   * UnSet up private data and data of the aggregated classes
   * in this command after processing phase
   */
  virtual void unsetup();

protected:

  /**
   * Execute Processing actions
   */
  void executeOnTrs();

  /**
   * Configures the command.
   */
  virtual void configure ( Config::ConfigArgs& args );

protected: // data

  /// physical model var set
  Common::SafePtr<Framework::ConvectiveVarSet> m_varSet;

  /// Transformer from Update to Linear Variables
  Common::SelfRegistPtr<Framework::VarSetTransformer> m_inputToUpdateVar;

  /// a vector of string to hold the functions
  std::vector<std::string> m_functions;

  /// a vector of string to hold the variables
  std::vector<std::string> m_vars;

  /// the VectorialFunction to use
  Framework::VectorialFunction m_vFunction;

  /// a string to hold the name of the input variables
  std::string m_inputVarStr;

  /// states in initialization points
  std::vector< Framework::State* > m_initPntsStates;

  /// input state
  Framework::State* m_inputState;

  /// number of equations in the physical model
  CFuint m_nbrEqs;

}; // class StdInitStateQuad

//////////////////////////////////////////////////////////////////////////////

    } // namespace SpectralFV

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_Numerics_SpectralFV_StdInitState_hh

