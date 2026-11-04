#include <iostream>
#include <limits>

#include "MusicItem.h"
#include "Song.h"
#include "Album.h"
#include "Artist.h"

// Test Sample Music Library
void loadSampleMusic(MusicLibrary& entries) {
    entries.push_back(std::make_unique<Song>("Blinding Lights", "The Weeknd", 10));
    entries.push_back(std::make_unique<Song>("Hello", "Adele", 9));
    entries.push_back(std::make_unique<Song>("Love Story", "Taylor Swift", 8));
    entries.push_back(std::make_unique<Song>("God's Plan", "Drake", 6));
    entries.push_back(std::make_unique<Album>("After Hours", "The Weeknd", 9, 14));
    entries.push_back(std::make_unique<Album>("Folklore", "Taylor Swift", 8, 16));
    entries.push_back(std::make_unique<Artist>("The Weeknd", "Pop", 10));
    entries.push_back(std::make_unique<Artist>("Adele", "Soul", 9));
}

int main() {
    MusicLibrary entries;
    int options = 0;

    loadSampleMusic(entries);

    do {
        printMenu();

        if (!(std::cin >> options)) {
            if (std::cin.eof()) {
                break;   
            }

            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');

            options = 0;
        }

        switch (options) {
        case 1:
            addSong(entries);
            break;

        case 2:
            addAlbum(entries);
            break;
        case 3:
            showTopArtists(entries);
            break;

        case 4:
            showTopSongs(entries);
            break;

        case 5:
            showTopAlbums(entries);
            break;

        case 6:
            showAllMusic(entries);
            break;

        case 7:
            std::cout << "Goodbye!\n";
            break;
        default:
            std::cout << "Please enter a number (1-7).\n";
            break;
        }

    } while (options != 7);

    return 0;
}
