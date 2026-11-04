# Music Rating and Tracker

COP 3003 team project.

## Synopsis

Music Rating and Tracker is a C++ program for people who want to keep track of the
music they listen to. Users enter songs, albums, and artists by hand, rate each one
from 1 to 10, and see their collection ranked. Nothing is streamed or pulled from
an online service, so everything in the library is something the user added.

The project is built around a small class hierarchy. `MusicItem` is an abstract base
class that holds a title and a rating and enforces the rating rules. `Song`, `Album`,
and `Artist` derive from it, and each one prints and describes itself differently.
The program works with all three through base-class pointers, so adding a new kind of
item later does not require changing the code that displays or ranks them. Invalid
input, such as a rating outside 1 to 10 or an empty title, is rejected with an
exception and leaves the library unchanged.

### What works now (console version)

- Add a song with a title, artist, and rating from 1 to 10
- Add an album with a title, artist, rating, and track count
- Reject duplicate songs and albums (ignoring upper and lower case), invalid ratings,
  and invalid track counts
- See top artists: each artist's highest-rated song and the average rating of all
  their songs
- See top songs and top albums, each sorted by rating
- See all music, with songs, albums, and artists each shown in their own format

### Planned

- Search by title or artist, with sorting by rating or alphabetically
- Top Five lists for artists, songs, and albums, using a template class
- Saving and loading the library to a local file, with errors that never overwrite
  valid saved data
- A graphical interface built with Qt 6

### Concepts demonstrated

Abstract base class, inheritance, runtime polymorphism through virtual functions,
composition (the library owns its items), exception handling, and separation of
rules from user-interface code.

## Status

| Part | Status |
|---|---|
| `MusicItem` (abstract base class) | Implemented |
| `Song`, `Album`, `Artist` (derived classes) | Implemented |
| Console driver: `MusicTracker.cpp` (menu loop, sample data) plus console functions at the end of `MusicItem.h`, `Song.h`, and `Album.h` | Implemented |
| `MusicLibrary` class with overloaded `search` | Planned |
| `RankedList<T>` template (Artist, Song, Album) and `Favorites` | Planned |
| `FileManager` (save/load) | Planned |
| Qt 6 (Widgets) GUI | Planned |

## Environment

Fill in the values used by your team.

- Operating system: _______ (example: Windows 11)
- Compiler: _______ (example: MSVC from Visual Studio, or g++ 13)
- C++ standard: C++20 (the project is set to `stdcpp20`; the code also compiles as C++17)
- Dependencies: none for this checkpoint (standard library only). Planned: Qt 6 (Widgets module); the exact version will be recorded here when the GUI is added.

## Build and run

### Option A: Visual Studio (Windows)

1. Clone the repository and open `MusicTracker.slnx`.
2. Choose `x64` and `Debug` in the toolbar.
3. Press Ctrl+F5 (Start Without Debugging).

The project file uses platform toolset **v145** (project version 18.0), which comes
with the newest Visual Studio. `.slnx` is Visual Studio's newer solution format, and
older Visual Studio versions may not open it. If you use an older version, either
update Visual Studio, or open the folder with CMake (Option C). If Visual Studio
reports a missing toolset, right-click the project, choose Properties, and set
Platform Toolset to the one you have installed.

### Option B: compile directly with g++ (no other tools needed)

```
git clone <repository URL>
cd Music_Rating_And_Tracker
g++ -std=c++20 -Wall -Wextra MusicTracker.cpp -o music_tracker
./music_tracker
```

### Option C: CMake

```
cmake -S . -B build
cmake --build build
./build/music_tracker          (Windows: build\Debug\music_tracker.exe)
```

## Using the program

The menu has seven choices: add a song, add an album, see top artists (each artist's best
song and average rating), see top songs, see top albums, see all music, and exit. The program starts with a few
songs, albums, and artists so every screen has something to show. Ratings must be
whole numbers from 1 to 10, and a song that is already in the library is rejected.

## Files

```
MusicItem.h       abstract base class, plus the library alias, show functions,
                  menu, and getRating
Song.h            Song class, plus addSong (with duplicate check)
Album.h           Album class, plus addAlbum and getTrackCount
Artist.h          Artist class
MusicTracker.cpp  menu loop and sample data
MusicTracker.slnx, MusicTracker.vcxproj, MusicTracker.vcxproj.filters
                  Visual Studio solution and project
CMakeLists.txt    CMake build
```

Build folders, executables, and per-user Visual Studio files (`*.user`, `.vs/`) are
not committed (see `.gitignore`).
