set(tagitcommon_SOURCES

	MainWindow.cpp
	MainWindow.h

	fs/Environment.cpp
	fs/Environment.h
	fs/FS.cpp
	fs/FS.h
	fs/TemporaryStorage.cpp
	fs/TemporaryStorage.h

	util/Errno.cpp
	util/Errno.h
	util/ScopeExit.cpp
	util/ScopeExit.h

)

add_library(tagitcommon STATIC ${tagitcommon_SOURCES})
qt5_use_modules(tagitcommon ${tagit_QT5_MODULES})
