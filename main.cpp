#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>

class Entry {
public:
    std::string Artist;
    double Rating;
    std::string Title;

    // Constructor to initialize the entry
    Entry(std::string artist, std::string title, double rating)
        : Artist(artist), Rating(rating), Title(title) {
    }

    // Function to display the entry in a formatted manner
    void display() const {
        std::cout << std::left
            << std::setw(25) << Artist
            << std::setw(30) << Title
            << std::right
            << std::fixed << std::setprecision(1)
            << std::setw(8) << Rating
            << "\n";
    }
};

void printHeader() {
    std::cout << std::left
        << std::setw(25) << "Artist"
        << std::setw(30) << "Title"
        << std::right
        << std::setw(8) << "Rating"
        << "\n";
    std::cout << std::string(63, '-') << "\n";
}

void showTopSongs(std::vector<Entry> entries) {
    std::sort(entries.begin(), entries.end(),
        [](const Entry& a, const Entry& b) {
            return a.Rating > b.Rating;
        });

    printHeader();

    for (const auto& entry : entries) {
        entry.display();
    }
}

// Each artist's best-rated song, highest first
void showTopArtists(const std::vector<Entry>& entries) {
    std::vector<Entry> best;
    for (const auto& entry : entries) {
        auto it = std::find_if(best.begin(), best.end(),
            [&](const Entry& b) { return b.Artist == entry.Artist; });
        if (it == best.end()) {
            best.push_back(entry);
        }
        else if (entry.Rating > it->Rating) {
            *it = entry;
        }
    }
    showTopSongs(best);
}

int main() {
    std::vector<Entry> entries;

    entries.emplace_back("Taylor Swift", "Love Story", 4.5);
    entries.emplace_back("The Weeknd", "Blinding Lights", 4.9);
    entries.emplace_back("Drake", "God's Plan", 3.8);
    entries.emplace_back("Adele", "Hello", 4.7);

    int options = 0;
    do {
        std::cout << "\nOptions: \n"
            << "1. Make new playlist \n"
            << "2. See top artists \n"
            << "3. See top songs \n"
            << "4. Exit\n"
            << "Choose: ";

        if (!(std::cin >> options)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            options = 0;
        }

        switch (options) {
        case 1:
            std::cout << "Make new playlist \n";
            break;

        case 2:
            showTopArtists(entries);
            break;

        case 3:
            showTopSongs(entries);
            break;

        case 4:
            std::cout << "Goodbye!" << "\n";
            break;

        default:
            std::cout << "Please enter a number (1 - 4)" << "\n";
            break;
        }
    } while (options != 4);

    return 0;
}
