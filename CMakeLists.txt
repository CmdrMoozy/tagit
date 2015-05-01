cmake_minimum_required(VERSION 3.0.2)
project(TagIt)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Note which type of build we're performing.

if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "No CMAKE_BUILD_TYPE specified; defaulting to Release.")
	set(CMAKE_BUILD_TYPE "Release")
endif()

string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER)

# Find our dependencies.

find_package(Boost REQUIRED)
find_package(Taglib REQUIRED)

# Setup our compile flags.

include(${PROJECT_SOURCE_DIR}/cmake/SetFlags.cmake)
tagitSetCompileFlags()

if(CMAKE_BUILD_TYPE_LOWER MATCHES debug)
	add_definitions(-DTAGIT_DEBUG)
endif()

include_directories("src")

# Define the libraries to link against.

set(tagit_LIBRARIES

	${Taglib_LIBRARIES}

)

# Add our targets.

add_subdirectory(src/tagit)
