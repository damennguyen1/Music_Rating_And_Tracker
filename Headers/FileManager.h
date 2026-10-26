#ifndef FILEMANAGER_H
#define FILEMANAGER_H

INCLUDE <string>
INCLUDE "MusicLibrary.h"
INCLUDE "Favorites.h"

STRUCT LoadedData                         // bundles both results from one load
library : MusicLibrary
favorites : Favorites

CLASS FileManager
PUBLIC :
FileManager() = default

save(library : MusicLibrary const&, favorites : Favorites const&, filename : string) const
// throws runtime_error if the file cannot be written

load(filename: string) const->LoadedData
// throws runtime_error if missing or corrupted
// never touches the caller's current data

PRIVATE:
parseLine(line : string, library : MusicLibrary&)
// throws runtime_error with the line number on bad format

#endif
