
ABSTRACT CLASS MusicItem
  PRIVATE:
    title: string
    artist: string
    rating: int

  PUBLIC:
    CONSTRUCTOR(title, artist, rating)
      IF title is empty OR artist is empty
        THROW invalid_argument("Title and artist required")
      IF rating < 1 OR rating > 10
        THROW invalid_argument("Rating must be 1-10")
      store values

    VIRTUAL DESTRUCTOR = default      // needed for deleting through base pointer

    getTitle(), getArtist(), getRating()
    setRating(newRating)
      IF newRating outside 1-10 THROW invalid_argument
      rating = newRating

    PURE VIRTUAL describe() -> string       // text shown in the GUI
    PURE VIRTUAL toFileLine() -> string     // how it is saved
    PURE VIRTUAL typeName() -> string       // "Song" or "Album"

CLASS Song : PUBLIC MusicItem
  PRIVATE: genre: string   // optional, ties in your "by genre" idea
  describe() OVERRIDE   -> "Song: <title> by <artist> - <rating>/10"
  toFileLine() OVERRIDE -> "SONG|title|artist|rating|genre"
  typeName() OVERRIDE   -> "Song"

CLASS Album : PUBLIC MusicItem
  PRIVATE: trackCount: int
  describe() OVERRIDE   -> "Album: <title> by <artist> (<trackCount> tracks) - <rating>/10"
  toFileLine() OVERRIDE -> "ALBUM|title|artist|rating|trackCount"
  typeName() OVERRIDE   -> "Album"
