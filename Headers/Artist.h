#pragma once
#include "MusicItem.h"

class Artist : public MusicItem {
private:
    std::string genre_;

public:
    Artist(std::string name, std::string genre, int rating)
        : MusicItem(std::move(name), rating),
        genre_(std::move(genre)) {

        if (genre_.empty())
            throw std::invalid_argument("Genre cannot be empty");
    }

    std::string type() const override {
        return "Artist";
    }

    std::string artistName() const override {
        return title_;
    }

    const std::string& genre() const {
        return genre_;
    }

    void displayInfo(std::ostream& out) const override {
        out << "[Artist] " << title_
            << " | Genre: " << genre_
            << " | Rating: " << rating_ << "/10";
    }
};
