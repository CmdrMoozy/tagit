set(tagitcommon_SOURCES

	MainWindow.cpp
	MainWindow.h

)

add_library(tagitcommon STATIC ${tagitcommon_SOURCES})
qt5_use_modules(tagitcommon ${tagit_QT5_MODULES})
