#pragma once
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
