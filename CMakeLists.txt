cmake_minimum_required(VERSION 3.21)
project(MusicTracker VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(MusicTracker
	MusicTracker.cpp
	MusicTracker.ui
	MusicItem.h
	Song.h
	Album.h
	Artist.h
)

target_link_libraries(MusicTracker PRIVATE Qt6::Widgets)
target_include_directories(MusicTracker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# On Windows, copy the Qt DLLs and plugins next to MusicTracker.exe after each
# build, so the program runs from Visual Studio or by double-clicking it
# without Qt's bin folder on PATH.
if(WIN32)
	get_target_property(_qmake_exe Qt6::qmake IMPORTED_LOCATION)
	get_filename_component(_qt_bin_dir "${_qmake_exe}" DIRECTORY)
	find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}" REQUIRED)

	add_custom_command(TARGET MusicTracker POST_BUILD
		COMMAND "${WINDEPLOYQT_EXECUTABLE}" --no-translations --no-compiler-runtime
			"$<TARGET_FILE:MusicTracker>"
		COMMENT "Copying Qt DLLs next to MusicTracker.exe"
	)
endif()
