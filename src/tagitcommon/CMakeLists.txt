set(tagitcommon_SOURCES

	MainWindow.cpp
	MainWindow.h

	fs/Environment.cpp
	fs/Environment.h

)

add_library(tagitcommon STATIC ${tagitcommon_SOURCES})
qt5_use_modules(tagitcommon ${tagit_QT5_MODULES})
