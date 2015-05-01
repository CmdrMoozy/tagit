set(tagit_SOURCES

	TagIt.cpp

)

add_executable(tagit ${tagit_SOURCES})
target_link_libraries(tagit ${tagit_LIBRARIES})
