set(tagit_SOURCES

	TagIt.cpp

)

add_executable(tagit ${tagit_SOURCES})
target_link_libraries(tagit ${tagit_LIBRARIES} tagitcommon)
qt5_use_modules(tagit ${tagit_QT5_MODULES})
