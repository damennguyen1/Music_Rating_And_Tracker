#pragma once
#include <string>
#include <utility>
#include <stdexcept>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QWidget>
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

// Add a song using values that have already been collected.
inline void addSong(MusicLibrary& entries, const std::string& title,
    const std::string& artist, int rating) {
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
}

// Create a new song from console input.
inline void addSong(MusicLibrary& entries) {
    std::string title;
    std::string artist;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter song title: ";
    std::getline(std::cin, title);

    std::cout << "Enter artist name: ";
    std::getline(std::cin, artist);

    int rating = getRating();

    try {
        addSong(entries, title, artist, rating);
        std::cout << "Song successfully added!\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

// Create a new song from Qt input.
inline void addSong(MusicLibrary& entries, QWidget* parent) {
    bool ok = false;
    QString title = QInputDialog::getText(
        parent, "Add Music", "Title:", QLineEdit::Normal, {}, &ok);
    if (!ok) return;

    QString artist = QInputDialog::getText(
        parent, "Add Music", "Artist:", QLineEdit::Normal, {}, &ok);
    if (!ok) return;

    int rating = QInputDialog::getInt(
        parent, "Add Music", "Rating (1-10):", 5, 1, 10, 1, &ok);
    if (!ok) return;

    try {
        ::addSong(entries, title.toStdString(), artist.toStdString(), rating);
    }
    catch (const std::invalid_argument& error) {
        QMessageBox::warning(parent, "Unable to add song", error.what());
    }
}
