# Once done this will define:
#
# TAGLIB_FOUND - system has the taglib library
# TAGLIB_CFLAGS - the taglib cflags
# TAGLIB_LIBRARIES - The libraries needed to use taglib

if(NOT TAGLIB_MIN_VERSION)
	set(TAGLIB_MIN_VERSION "1.9")
endif(NOT TAGLIB_MIN_VERSION)

find_program(TAGLIBCONFIG_EXECUTABLE NAMES taglib-config)

set(TAGLIB_LIBRARIES)
set(TAGLIB_CFLAGS)

if(TAGLIBCONFIG_EXECUTABLE)
	exec_program(${TAGLIBCONFIG_EXECUTABLE}
		ARGS --version RETURN_VALUE _return_VALUE
		OUTPUT_VARIABLE TAGLIB_VERSION)

	if(TAGLIB_VERSION STRLESS "${TAGLIB_MIN_VERSION}")
		message(STATUS "Taglib version ${TAGLIB_VERSION} found, ${TAGLIB_MIN_VERSION} required.")
		set(TAGLIB_FOUND FALSE)
	else()
		exec_program(${TAGLIBCONFIG_EXECUTABLE}
			ARGS --libs RETURN_VALUE _return_VALUE
			OUTPUT_VARIABLE TAGLIB_LIBRARIES)
		exec_program(${TAGLIBCONFIG_EXECUTABLE}
			ARGS --cflags RETURN_VALUE _return_VALUE
			OUTPUT_VARIABLE TAGLIB_CFLAGS)

		if(TAGLIB_LIBRARIES AND TAGLIB_CFLAGS)
			set(TAGLIB_FOUND TRUE)
		endif()
		string(REGEX REPLACE " *-I" ";" TAGLIB_INCLUDES "${TAGLIB_CFLAGS}")
	endif()
	mark_as_advanced(TAGLIB_CFLAGS TAGLIB_LIBRARIES TAGLIB_INCLUDES)
endif()

if(TAGLIB_FOUND)
	if(NOT TAGLIB_FIND_QUIETLY AND TAGLIBCONFIG_EXECUTABLE)
		message(STATUS "Found Taglib: ${TAGLIB_LIBRARIES}")
	endif()
else()
	if(Taglib_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find Taglib")
	endif()
endif()
