# Needs environmental variables
#   MITREM_HOME
# Sets
#   MITREM_INCLUDE_DIR
#   MITREM_LIBRARY
#   CF_HAVE_MITREM

SET_TRIAL_INCLUDE_PATH ("") # clear include search path
SET_TRIAL_LIBRARY_PATH ("") # clear library search path

IF ( EXISTS ${MITREM_HOME} )
  ADD_TRIAL_INCLUDE_PATH( ${MITREM_HOME} )
  ADD_TRIAL_INCLUDE_PATH( ${MITREM_HOME}/include )
  ADD_TRIAL_LIBRARY_PATH( ${MITREM_HOME} )
  ADD_TRIAL_LIBRARY_PATH( ${MITREM_HOME}/lib )
ENDIF()
IF ( EXISTS $ENV{MITREM_HOME} )
  ADD_TRIAL_INCLUDE_PATH( $ENV{MITREM_HOME}/include )
  ADD_TRIAL_LIBRARY_PATH( $ENV{MITREM_HOME}/lib )
ENDIF()

FIND_PATH(MITREM_INCLUDE_DIR MITReM.h ${TRIAL_INCLUDE_PATHS} NO_DEFAULT_PATH)
FIND_PATH(MITREM_INCLUDE_DIR MITReM.h)

FIND_LIBRARY(MITREM_LIBRARY mitremassembler ${TRIAL_LIBRARY_PATHS} NO_DEFAULT_PATH)
FIND_LIBRARY(MITREM_LIBRARY mitremassembler)

IF(MITREM_INCLUDE_DIR AND MITREM_LIBRARY)
  SET(CF_HAVE_MITREM 1 CACHE BOOL "MITReM library: found")
ELSE(MITREM_INCLUDE_DIR AND MITREM_LIBRARY)
  SET(CF_HAVE_MITREM 0 CACHE BOOL "MITReM library: not found")
ENDIF(MITREM_INCLUDE_DIR AND MITREM_LIBRARY)

MARK_AS_ADVANCED (
  MITREM_LIBRARY
  MITREM_INCLUDE_DIR
  CF_HAVE_MITREM
)

LOG ( "CF_HAVE_MITREM: [${CF_HAVE_MITREM}]" )
IF(CF_HAVE_MITREM)
  LOGFILE ( "  MITREM_INCLUDE_DIR: [${MITREM_INCLUDE_DIR}]" )
  LOGFILE ( "  MITREM_LIBRARY:     [${MITREM_LIBRARY}]" )
ENDIF(CF_HAVE_MITREM)
