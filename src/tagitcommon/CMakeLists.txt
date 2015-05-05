set(tagitcommon_SOURCES

	MainWindow.cpp
	MainWindow.h

	audio/AudioFile.cpp
	audio/AudioFile.h
	audio/WaveFile.cpp
	audio/WaveFile.h

	fs/Environment.cpp
	fs/Environment.h
	fs/FS.cpp
	fs/FS.h
	fs/TemporaryStorage.cpp
	fs/TemporaryStorage.h

	io/MemoryMappedFile.cpp
	io/MemoryMappedFile.h

	util/Errno.cpp
	util/Errno.h
	util/ScopeExit.cpp
	util/ScopeExit.h
	util/VariantUtils.h

)

add_library(tagitcommon STATIC ${tagitcommon_SOURCES})
qt5_use_modules(tagitcommon ${tagit_QT5_MODULES})
