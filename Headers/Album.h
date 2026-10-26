#ifndef ALBUM_H
#define ALBUM_H

INCLUDE "MusicItem.h"

CLASS Album : PUBLIC MusicItem
PRIVATE :
trackCount: int

PUBLIC :
Album(title, artist, rating, trackCount)
// calls MusicItem constructor
// IF trackCount < 1 THROW invalid_argument("Track count must be positive")
getTrackCount() const -> int

describe() const OVERRIDE->string
toFileLine() const OVERRIDE->string
typeName() const OVERRIDE->string

#endif
