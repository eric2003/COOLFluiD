# Needs environmental variables
#   LESMODELS_DIR
# Sets
#   LESMODELS_INCLUDE_DIR
#   LESMODELS_LIBRARIES
#   CF_HAVE_LESMODELS

SET_TRIAL_INCLUDE_PATH ("") # clear include search path
SET_TRIAL_LIBRARY_PATH ("") # clear library search path

IF ( EXISTS ${LESMODELS_DIR} )
  ADD_TRIAL_INCLUDE_PATH( ${LESMODELS_DIR} )
  ADD_TRIAL_INCLUDE_PATH( ${LESMODELS_DIR}/include )
  ADD_TRIAL_LIBRARY_PATH( ${LESMODELS_DIR} )
  ADD_TRIAL_LIBRARY_PATH( ${LESMODELS_DIR}/lib )
ENDIF()

IF ( EXISTS $ENV{LESMODELS_DIR} )
  ADD_TRIAL_INCLUDE_PATH( $ENV{LESMODELS_DIR}/include )
  ADD_TRIAL_LIBRARY_PATH( $ENV{LESMODELS_DIR}/lib )
ENDIF()

FIND_PATH(LESMODELS_INCLUDE_DIR les_interface.h ${TRIAL_INCLUDE_PATHS} NO_DEFAULT_PATH)
FIND_PATH(LESMODELS_INCLUDE_DIR les_interface.h)

FIND_LIBRARY(LESMODELS_LIBRARIES LESModels ${TRIAL_LIBRARY_PATHS} NO_DEFAULT_PATH)
FIND_LIBRARY(LESMODELS_LIBRARIES LESModels )

IF(LESMODELS_INCLUDE_DIR AND LESMODELS_LIBRARIES)
  SET(CF_HAVE_LESMODELS 1 CACHE BOOL "LESModels library found")
ELSE(LESMODELS_INCLUDE_DIR AND LESMODELS_LIBRARIES)
  SET(CF_HAVE_LESMODELS 0 CACHE BOOL "LESModels library not found")
ENDIF(LESMODELS_INCLUDE_DIR AND LESMODELS_LIBRARIES)

MARK_AS_ADVANCED (
  LESMODELS_LIBRARIES
  LESMODELS_INCLUDE_DIR
  CF_HAVE_LESMODELS
)

LOG ( "CF_HAVE_LESMODELS: [${CF_HAVE_LESMODELS}]" )
LOGFILE ( "  LESMODELS_INCLUDE_DIR: [${LESMODELS_INCLUDE_DIR}]" )
LOGFILE ( "  LESMODELS_LIBRARIES:   [${LESMODELS_LIBRARIES}]" )

