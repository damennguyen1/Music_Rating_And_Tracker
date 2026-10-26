#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

INCLUDE <vector>
INCLUDE <memory>
INCLUDE <string>
INCLUDE "MusicItem.h"
INCLUDE "Song.h"
INCLUDE "Album.h"

CLASS MusicLibrary
PRIVATE :
items: vector<unique_ptr<MusicItem>>

PUBLIC :
    MusicLibrary() = default
    MusicLibrary(MusicLibrary&&) = default               // movable, not copyable
    operator=(MusicLibrary&&) = default                  // (unique_ptr is move-only)

    addSong(title, artist, rating, genre)                // throws invalid_argument
    addAlbum(title, artist, rating, trackCount)          // throws invalid_argument
    addItem(item: unique_ptr<MusicItem>)                 // used by FileManager::load

    // Overloaded search
    search(text: string) const->vector<MusicItem*>
    search(text: string, type : string) const->vector<MusicItem*>

    sortByRating(list: vector<MusicItem*>&) const
    sortAlphabetically(list: vector<MusicItem*>&) const

    getAll() const->vector<MusicItem*>
    size() const -> int

#endif
