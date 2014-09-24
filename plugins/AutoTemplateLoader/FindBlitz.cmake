# Sets:
#   BLITZ_INCLUDE_DIR  = where blitz/array.h can be found
#   CF_HAVE_BLITZ      = set to true after finding the library

ADD_TRIAL_INCLUDE_PATH( ${BLITZ_HOME}/include )
ADD_TRIAL_INCLUDE_PATH( $ENV{BLITZ_HOME}/include )

FIND_PATH(BLITZ_INCLUDE_DIR blitz/array.h ${TRIAL_INCLUDE_PATHS} NO_DEFAULT_PATH)
FIND_PATH(BLITZ_INCLUDE_DIR blitz/array.h)

IF(BLITZ_INCLUDE_DIR)
  SET(CF_HAVE_BLITZ 1 CACHE BOOL "Found Blitz library")
ELSE(BLITZ_INCLUDE_DIR)
  SET(CF_HAVE_BLITZ 0 CACHE BOOL "Not fount Blitz library")
ENDIF(BLITZ_INCLUDE_DIR)

MARK_AS_ADVANCED(
  BLITZ_INCLUDE_DIR
  CF_HAVE_BLITZ
)

LOG ( "CF_HAVE_BLITZ: [${CF_HAVE_BLITZ}]" )
IF(CF_HAVE_BLITZ)
  LOGFILE ( "  BLITZ_INCLUDE_DIR: [${BLITZ_INCLUDE_DIR}]" )
ENDIF(CF_HAVE_BLITZ)