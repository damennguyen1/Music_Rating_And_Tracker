#pragma once
#include <string>
#include <utility>
#include <stdexcept>
#include "MusicItem.h"

class Song : public MusicItem {
private:
    std::string artist_;

public:
    Song(std::string title, std::string artist, int rating)
        : MusicItem(std::move(title), rating),
        artist_(std::move(artist)) {
        if (artist_.empty())
            throw std::invalid_argument("Artist cannot be empty");
    }

    std::string type() const override {
        return "Song";
    }

    std::string artistName() const override {
        return artist_;
    }

    void displayInfo(std::ostream& out) const override {
        out << "[Song] " << title_
            << " by " << artist_
            << " | Rating: " << rating_ << "/10";
    }
};

// Create a new song
inline void addSong(MusicLibrary& entries) {
    std::string title;
    std::string artist;

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter song title: ";
    std::getline(std::cin, title);

    std::cout << "Enter artist name: ";
    std::getline(std::cin, artist);

    int rating = getRating();

    try {
        // The constructor validates title, artist, and rating first.
        auto song = std::make_unique<Song>(title, artist, rating);

        bool duplicate = std::any_of(entries.begin(), entries.end(),
            [&](const std::unique_ptr<MusicItem>& e) {
                return e->type() == song->type()
                    && lowerCase(e->title()) == lowerCase(song->title())
                    && lowerCase(e->artistName()) == lowerCase(song->artistName());
            });

        if (duplicate) {
            throw std::invalid_argument("That song is already in the library");
        }

        entries.push_back(std::move(song));
        std::cout << "Song successfully added!\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}
