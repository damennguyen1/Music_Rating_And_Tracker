cmake_minimum_required(VERSION 3.16)
project(MusicRatingTracker CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The classes (MusicItem, Song, Album, Artist) are header-only,
# so the only source file is the console driver.
add_executable(music_tracker MusicTracker.cpp)
target_include_directories(music_tracker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
