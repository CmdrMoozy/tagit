# Once done this will define:
#
# Taglib_FOUND - system has the taglib library
# Taglib_CFLAGS - the taglib cflags
# Taglib_LIBRARIES - The libraries needed to use taglib

if(NOT TAGLIB_MIN_VERSION)
	set(TAGLIB_MIN_VERSION "1.9")
endif(NOT TAGLIB_MIN_VERSION)

find_program(TAGLIBCONFIG_EXECUTABLE NAMES taglib-config)

set(Taglib_LIBRARIES)
set(Taglib_CFLAGS)

if(TAGLIBCONFIG_EXECUTABLE)
	exec_program(${TAGLIBCONFIG_EXECUTABLE}
		ARGS --version RETURN_VALUE _return_VALUE
		OUTPUT_VARIABLE TAGLIB_VERSION)

	if(TAGLIB_VERSION STRLESS "${TAGLIB_MIN_VERSION}")
		message(STATUS "Taglib version ${TAGLIB_VERSION} found, ${TAGLIB_MIN_VERSION} required.")
		set(Taglib_FOUND FALSE)
	else()
		exec_program(${TAGLIBCONFIG_EXECUTABLE}
			ARGS --libs RETURN_VALUE _return_VALUE
			OUTPUT_VARIABLE Taglib_LIBRARIES)
		exec_program(${TAGLIBCONFIG_EXECUTABLE}
			ARGS --cflags RETURN_VALUE _return_VALUE
			OUTPUT_VARIABLE Taglib_CFLAGS)

		if(Taglib_LIBRARIES AND Taglib_CFLAGS)
			set(Taglib_FOUND TRUE)
		endif()
		string(REGEX REPLACE " *-I" ";" TAGLIB_INCLUDES "${Taglib_CFLAGS}")
	endif()
	mark_as_advanced(Taglib_CFLAGS Taglib_LIBRARIES TAGLIB_INCLUDES)
endif()

if(Taglib_FOUND)
	if(NOT TAGLIB_FIND_QUIETLY AND TAGLIBCONFIG_EXECUTABLE)
		message(STATUS "Found Taglib: ${Taglib_LIBRARIES}")
	endif()
else()
	if(Taglib_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find Taglib")
	endif()
endif()
