#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <limits>
#include <memory>
#include <vector>

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

// The library: owns every Song, Album, and Artist.
// (Planned: this becomes a MusicLibrary class with search and sort.)
using MusicLibrary = std::vector<std::unique_ptr<MusicItem>>;

// Lowercase copy
// Used for case-insensitive comparisons of titles and artist names.
inline std::string lowerCase(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return text;
}

// Display the table header
inline void printHeader() {
    std::cout << std::left
        << std::setw(12) << "Type"
        << std::setw(25) << "Artist"
        << std::setw(30) << "Title"
        << std::right
        << std::setw(8) << "Rating"
        << "\n";

    std::cout << std::string(75, '-') << "\n";
}

// Display a music item as one table row
inline void displayEntry(const MusicItem& item) {
    std::cout << std::left
        << std::setw(12) << item.type()
        << std::setw(25) << item.artistName()
        << std::setw(30) << item.title()
        << std::right
        << std::setw(5) << item.rating()
        << "/10\n";
}

// Sort and display all songs
inline void showTopSongs(const MusicLibrary& entries) {
    std::vector<const MusicItem*> songs;

    for (const auto& entry : entries) {
        if (entry->type() == "Song") {
            songs.push_back(entry.get());
        }
    }

    // stable_sort keeps equal ratings in the order they were added
    std::stable_sort(songs.begin(), songs.end(),
        [](const MusicItem* a, const MusicItem* b) {
            return a->rating() > b->rating();
        });

    printHeader();

    if (songs.empty()) {
        std::cout << "(no songs yet)\n";
    }

    for (const auto* song : songs) {
        displayEntry(*song);
    }
}

// Display each artist's highest-rated song and the average rating of all
// their songs. If an artist has several songs tied for the highest rating,
// the first one added is shown.
inline void showTopArtists(const MusicLibrary& entries) {
    struct ArtistStats {
        std::string name;
        const MusicItem* best;   // highest-rated song so far
        int total;               // sum of all their song ratings
        int count;               // number of their songs
        double average() const { return static_cast<double>(total) / count; }
    };
    std::vector<ArtistStats> artists;

    // One pass: collect each artist's best song, total, and song count.
    for (const auto& entry : entries) {
        if (entry->type() != "Song")      // albums and Artist items are not songs
            continue;

        auto it = std::find_if(artists.begin(), artists.end(),
            [&](const ArtistStats& a) {
                return lowerCase(a.name) == lowerCase(entry->artistName());
            });

        if (it == artists.end()) {
            artists.push_back({ entry->artistName(), entry.get(), entry->rating(), 1 });
        }
        else {
            it->total += entry->rating();
            it->count++;
            if (entry->rating() > it->best->rating()) {   // strict: first added wins ties
                it->best = entry.get();
            }
        }
    }

    // Highest best-song rating first; higher average breaks ties.
    std::stable_sort(artists.begin(), artists.end(),
        [](const ArtistStats& a, const ArtistStats& b) {
            if (a.best->rating() != b.best->rating())
                return a.best->rating() > b.best->rating();
            return a.average() > b.average();
        });

    std::cout << std::left
        << std::setw(25) << "Artist"
        << std::setw(30) << "Top song"
        << std::right
        << std::setw(8) << "Best"
        << std::setw(9) << "Average"
        << "\n";
    std::cout << std::string(72, '-') << "\n";

    if (artists.empty()) {
        std::cout << "(no artists yet)\n";
    }

    for (const auto& a : artists) {
        std::cout << std::left
            << std::setw(25) << a.name
            << std::setw(30) << a.best->title()
            << std::right
            << std::setw(5) << a.best->rating() << "/10"
            << std::setw(9) << std::fixed << std::setprecision(1) << a.average()
            << "\n";
    }
}

// Sort and display all albums
inline void showTopAlbums(const MusicLibrary& entries) {
    std::vector<const MusicItem*> albums;

    for (const auto& entry : entries) {
        if (entry->type() == "Album") {
            albums.push_back(entry.get());
        }
    }

    // stable_sort keeps equal ratings in the order they were added
    std::stable_sort(albums.begin(), albums.end(),
        [](const MusicItem* a, const MusicItem* b) {
            return a->rating() > b->rating();
        });

    printHeader();

    if (albums.empty()) {
        std::cout << "(no albums yet)\n";
    }

    for (const auto* album : albums) {
        displayEntry(*album);
    }
}
// Show every item. displayInfo is a pure virtual function, so each
// Song, Album, and Artist prints itself in its own format.
inline void showAllMusic(const MusicLibrary& entries) {
    if (entries.empty()) {
        std::cout << "(library is empty)\n";
        return;
    }

    for (const auto& entry : entries) {
        entry->displayInfo(std::cout);
        std::cout << "\n";
    }
}

// Print the main menu
inline void printMenu() {
    std::cout << "\n===== MUSIC PLAYLIST =====\n"
        << "1. Add song\n"
        << "2. Add album\n"
        << "3. See top artists\n"
        << "4. See top songs\n"
        << "5. See top albums\n"
        << "6. See all music\n"
        << "7. Exit\n"
        << "Choose: ";
}

// Get a valid rating
inline int getRating() {
    int rating;

    while (true) {
        std::cout << "Enter rating (1-10): ";

        if (std::cin >> rating && rating >= 1 && rating <= 10) {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            return rating;
        }

        // Input ended (Ctrl+Z / Ctrl+D): stop asking. Returning 0 makes the
        // Song constructor reject it, and addSong prints the error.
        if (std::cin.eof()) {
            return 0;
        }

        std::cout << "Invalid rating. Please enter 1-10.\n";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
