#pragma once
#include "MusicItem.h"

class Album : public MusicItem {
private:
    std::string artist_;
    int tracks_;

public:
    Album(std::string title, std::string artist,
        int rating, int tracks)
        : MusicItem(std::move(title), rating),
        artist_(std::move(artist)),
        tracks_(tracks) {

        if (artist_.empty())
            throw std::invalid_argument("Artist cannot be empty");

        if (tracks_ <= 0)
            throw std::invalid_argument("Track count must be positive");
    }

    std::string type() const override {
        return "Album";
    }

    std::string artistName() const override {
        return artist_;
    }

    int trackCount() const override {
        return tracks_;
    }

    void displayInfo(std::ostream& out) const override {
        out << "[Album] " << title_
            << " by " << artist_
            << " | " << tracks_ << " tracks"
            << " | Rating: " << rating_ << "/10";
    }
};

// Get a valid track count
inline int getTrackCount() {
    int tracks;

    while (true) {
        std::cout << "Enter number of tracks: ";

        if (std::cin >> tracks && tracks >= 1) {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            return tracks;
        }

        // Input ended (Ctrl+Z / Ctrl+D): stop asking. Returning 0 makes the
        // Album constructor reject it, and addAlbum prints the error.
        if (std::cin.eof()) {
            return 0;
        }

        std::cout << "Invalid track count. Please enter a whole number of 1 or more.\n";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Create a new album
inline void addAlbum(MusicLibrary& entries) {
    std::string title;
    std::string artist;

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter album title: ";
    std::getline(std::cin, title);

    std::cout << "Enter artist name: ";
    std::getline(std::cin, artist);

    int rating = getRating();
    int tracks = getTrackCount();

    try {
        // The constructor validates title, artist, rating, and track count first.
        auto album = std::make_unique<Album>(title, artist, rating, tracks);

        bool duplicate = std::any_of(entries.begin(), entries.end(),
            [&](const std::unique_ptr<MusicItem>& e) {
                return e->type() == album->type()
                    && lowerCase(e->title()) == lowerCase(album->title())
                    && lowerCase(e->artistName()) == lowerCase(album->artistName());
            });

        if (duplicate) {
            throw std::invalid_argument("That album is already in the library");
        }

        entries.push_back(std::move(album));
        std::cout << "Album successfully added!\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}
