#pragma once
#include "MusicItem.h"

class Album : public MusicItem {
private:
    std::string artist_;
    int tracks_;

public:
    Album(std::string title, std::string artist, int rating, int tracks)
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
