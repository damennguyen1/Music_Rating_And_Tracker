#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
#include <utility>

class MusicItem {
protected:
    std::string title_;
    int rating_;

public:
    MusicItem(std::string title, int rating)
        : title_(std::move(title)), rating_(rating) {
        if (title_.empty())
            throw std::invalid_argument("Title cannot be empty");

        if (rating_ < 1 || rating_ > 10)
            throw std::invalid_argument("Rating must be between 1 and 10");
    }

    virtual ~MusicItem() = default;

    virtual void displayInfo(std::ostream& out) const = 0;
    virtual std::string type() const = 0;
    virtual std::string artistName() const = 0;

    virtual int trackCount() const {
        return 0;
    }

    const std::string& title() const {
        return title_;
    }

    int rating() const {
        return rating_;
    }

    void setRating(int rating) {
        if (rating < 1 || rating > 10)
            throw std::invalid_argument("Rating must be between 1 and 10");

        rating_ = rating;
    }
};

