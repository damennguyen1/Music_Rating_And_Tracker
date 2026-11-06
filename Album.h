#pragma once
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QWidget>
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

// Add an album using values that have already been collected.
inline void addAlbum(MusicLibrary& entries, const std::string& title,
    const std::string& artist, int rating, int tracks) {
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
}

// Create a new album from console input.
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
        ::addAlbum(entries, title, artist, rating, tracks);
        std::cout << "Album successfully added!\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

// Create a new album from Qt input.
inline void addAlbum(MusicLibrary& entries, QWidget* parent) {
    bool ok = false;
    QString title = QInputDialog::getText(
        parent, "Add Album", "Title:", QLineEdit::Normal, {}, &ok);
    if (!ok) return;

    QString artist = QInputDialog::getText(
        parent, "Add Album", "Artist:", QLineEdit::Normal, {}, &ok);
    if (!ok) return;

    int rating = QInputDialog::getInt(
        parent, "Add Album", "Rating (1-10):", 5, 1, 10, 1, &ok);
    if (!ok) return;

    int tracks = QInputDialog::getInt(
        parent, "Add Album", "Number of tracks:", 1, 1, 999, 1, &ok);
    if (!ok) return;

    try {
        ::addAlbum(entries, title.toStdString(), artist.toStdString(), rating, tracks);
    }
    catch (const std::invalid_argument& error) {
        QMessageBox::warning(parent, "Unable to add album", error.what());
    }
}
