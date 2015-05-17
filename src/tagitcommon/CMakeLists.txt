set(tagitcommon_SOURCES

	MainWindow.cpp
	MainWindow.h

	audio/AACFile.cpp
	audio/AACFile.h
	audio/ALACFile.cpp
	audio/ALACFile.h
	audio/AudioFile.cpp
	audio/AudioFile.h
	audio/AudioFileModel.cpp
	audio/AudioFileModel.h
	audio/FLACFile.cpp
	audio/FLACFile.h
	audio/MP3File.cpp
	audio/MP3File.h
	audio/Utils.cpp
	audio/Utils.h
	audio/VorbisFile.cpp
	audio/VorbisFile.h
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

	tag/Tag.cpp
	tag/Tag.h
	tag/TaggedFile.h

	ui/AudioTagWidget.cpp
	ui/AudioTagWidget.h
	ui/PathInputWidget.cpp
	ui/PathInputWidget.h

	util/Bitwise.cpp
	util/Bitwise.h
	util/ConstexprString.h
	util/Errno.cpp
	util/Errno.h
	util/ScopeExit.cpp
	util/ScopeExit.h
	util/String.cpp
	util/String.h
	util/VariantUtils.h
	util/visualAsciiTranslationMap.cpp
	util/visualAsciiTranslationMap.h

)

add_library(tagitcommon STATIC ${tagitcommon_SOURCES})
qt5_use_modules(tagitcommon ${tagit_QT5_MODULES})
