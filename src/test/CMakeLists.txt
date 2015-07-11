find_package(DWARF REQUIRED)

set(test_RESOURCES

	data.qrc

)

set(test_SOURCES

	TagItTest.cpp

	audio/AudioFileTest.cpp

	fs/EnvironmentTest.cpp
	fs/FSTest.cpp
	fs/TemporaryStorageTest.cpp

	io/MemoryMappedFileTest.cpp

	tag/TagTest.cpp

	util/BitwiseTest.cpp
	util/ErrnoTest.cpp
	util/ScopeExitTest.cpp
	util/StringTest.cpp

)

qt5_add_resources(test_RESOURCES_RCC ${test_RESOURCES})

add_executable(tagit-test ${test_RESOURCES_RCC} ${test_SOURCES})
target_link_libraries(tagit-test ${tagit_LIBRARIES} tagitcommon)
qt5_use_modules(tagit-test ${tagit_QT5_MODULES})

add_test(TagitTest tagit-test)
