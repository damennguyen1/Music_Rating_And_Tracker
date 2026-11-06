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
