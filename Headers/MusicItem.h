#ifndef MUSICITEM_H
#define MUSICITEM_H

INCLUDE <string>

ABSTRACT CLASS MusicItem
PRIVATE :
title: string
artist : string
rating : int

PUBLIC :
MusicItem(title, artist, rating)      // validates, throws invalid_argument
VIRTUAL ~MusicItem() = default        // required for delete through base pointer

getTitle() const->string
getArtist() const->string
getRating() const -> int
setRating(newRating)                  // validates, throws invalid_argument

PURE VIRTUAL describe() const->string
PURE VIRTUAL toFileLine() const->string
PURE VIRTUAL typeName() const->string

// Two items are equal if title and artist match (ignoring case).
// RankedList uses this to reject duplicates.
operator==(other: MusicItem) const -> bool

#endif
