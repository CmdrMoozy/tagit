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

set(CMAKE_AUTOMOC ON)

find_package(Boost REQUIRED filesystem system)
find_package(Taglib REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

# Setup our compile flags.

include(${PROJECT_SOURCE_DIR}/cmake/SetFlags.cmake)
tagitSetCompileFlags()

add_definitions(-DQT_NO_KEYWORDS)

if(CMAKE_BUILD_TYPE_LOWER MATCHES debug)
	add_definitions(-DTAGIT_DEBUG)
endif()

include_directories("src")

# Define the libraries to link against.

set(tagit_LIBRARIES

	${Boost_SYSTEM_LIBRARY}
	${Boost_FILESYSTEM_LIBRARY}
	${Taglib_LIBRARIES}
	${Qt5Core_LIBRARIES}
	${Qt5Gui_LIBRARIES}
	${Qt5Widgets_LIBRARIES}

)

set(tagit_QT5_MODULES

	Core
	Gui
	Widgets

)

# Build libvrfy, if applicable.

if(CMAKE_BUILD_TYPE_LOWER MATCHES debug)
	add_subdirectory(vrfy)
endif()

# Add our targets.

enable_testing()

add_subdirectory(src/tagitcommon)
add_subdirectory(src/tagit)

if(CMAKE_BUILD_TYPE_LOWER MATCHES debug)
	add_subdirectory(src/test)
endif()
