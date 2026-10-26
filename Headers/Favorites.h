#ifndef FAVORITES_H
#define FAVORITES_H

INCLUDE <string>
INCLUDE <vector>
INCLUDE "RankedList.h"
INCLUDE "Song.h"
INCLUDE "Album.h"

CLASS Favorites
PRIVATE :
artists: RankedList<string>
songs : RankedList<Song>
albums : RankedList<Album>

PUBLIC :
    Favorites() = default

    setArtist(name : string, position : int)    // throws out_of_range / invalid_argument
    setSong(song : Song, position : int)
    setAlbum(album : Album, position : int)

    removeArtist(position: int)
    removeSong(position: int)
    removeAlbum(position: int)

    getArtists() const->vector<string>
    getSongs() const->vector<Song>
    getAlbums() const->vector<Album>

#endif
