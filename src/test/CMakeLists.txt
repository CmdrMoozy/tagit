find_package(DWARF REQUIRED)

set(test_SOURCES

	TagItTest.cpp

	fs/EnvironmentTest.cpp
	fs/EnvironmentTest.h

	util/ErrnoTest.cpp
	util/ErrnoTest.h

)

include_directories(${CMAKE_SOURCE_DIR}/vrfy/src)

add_executable(tagit-test ${test_SOURCES})
target_link_libraries(tagit-test ${tagit_LIBRARIES} tagitcommon ${Vrfy_LIBS})
qt5_use_modules(tagit-test ${tagit_QT5_MODULES})
