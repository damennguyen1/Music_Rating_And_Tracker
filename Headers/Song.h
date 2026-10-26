#ifndef SONG_H
#define SONG_H

INCLUDE "MusicItem.h"

CLASS Song : PUBLIC MusicItem
PRIVATE :
genre: string

PUBLIC :
Song(title, artist, rating, genre)    // calls MusicItem constructor
getGenre() const->string

describe() const OVERRIDE->string
toFileLine() const OVERRIDE->string
typeName() const OVERRIDE->string

#endif
