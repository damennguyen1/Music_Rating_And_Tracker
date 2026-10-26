
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

class Entry {
public:
    std::string Artist;
    double Rating;
    std::string Title;

    Entry(std::string artist, std::string title, double rating)
        : Artist(artist), Rating(rating), Title(title) {
    }

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

int main() {
    std::vector<Entry> entries;

    entries.emplace_back("Taylor Swift", "Love Story", 4.5);
    entries.emplace_back("The Weeknd", "Blinding Lights", 4.9);
    entries.emplace_back("Drake", "God's Plan", 3.8);
    entries.emplace_back("Adele", "Hello", 4.7);

    std::sort(entries.begin(), entries.end(),
        [](const Entry& a, const Entry& b) {
            return a.Rating > b.Rating;
        });

    // Print column headers
    std::cout << std::left
        << std::setw(25) << "Artist"
        << std::setw(30) << "Title"
        << std::right
        << std::setw(8) << "Rating"
        << "\n";

    std::cout << std::string(63, '-') << "\n";

    for (const auto& entry : entries) {
        entry.display();
    }

    return 0;
}
