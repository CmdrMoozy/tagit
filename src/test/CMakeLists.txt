find_package(DWARF REQUIRED)

set(test_SOURCES

	TagItTest.cpp

)

include_directories(${CMAKE_SOURCE_DIR}/vrfy/src)

add_executable(tagit-test ${test_SOURCES})
target_link_libraries(tagit-test ${tagit_LIBRARIES} ${Vrfy_LIBS})
