find_package(DWARF REQUIRED)

set(test_RESOURCES

	data.qrc

)

set(test_SOURCES

	TagItTest.cpp

	audio/AudioFileTest.cpp
	audio/AudioFileTest.h

	fs/EnvironmentTest.cpp
	fs/EnvironmentTest.h
	fs/FSTest.cpp
	fs/FSTest.h
	fs/TemporaryStorageTest.cpp
	fs/TemporaryStorageTest.h

	io/MemoryMappedFileTest.cpp
	io/MemoryMappedFileTest.h

	util/BitwiseTest.cpp
	util/BitwiseTest.h
	util/ErrnoTest.cpp
	util/ErrnoTest.h
	util/ScopeExitTest.cpp
	util/ScopeExitTest.h

)

include_directories(${CMAKE_SOURCE_DIR}/vrfy/src)

qt5_add_resources(test_RESOURCES_RCC ${test_RESOURCES})

add_executable(tagit-test ${test_RESOURCES_RCC} ${test_SOURCES})
target_link_libraries(tagit-test ${tagit_LIBRARIES} tagitcommon ${Vrfy_LIBS})
qt5_use_modules(tagit-test ${tagit_QT5_MODULES})
