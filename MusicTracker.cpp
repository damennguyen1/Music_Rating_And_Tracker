#include <QApplication>
#include <QHeaderView>
#include <QMainWindow>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "MusicItem.h"
#include "Song.h"
#include "Album.h"
#include "Artist.h"
#include "ui_MusicTracker.h"

// Add example entries shown when the application starts.
void loadSampleMusic(MusicLibrary& entries) {
    entries.push_back(std::make_unique<Song>("Blinding Lights", "The Weeknd", 10));
    entries.push_back(std::make_unique<Song>("Hello", "Adele", 9));
    entries.push_back(std::make_unique<Song>("Love Story", "Taylor Swift", 8));
    entries.push_back(std::make_unique<Song>("God's Plan", "Drake", 6));
    entries.push_back(std::make_unique<Album>("After Hours", "The Weeknd", 9, 14));
    entries.push_back(std::make_unique<Album>("Folklore", "Taylor Swift", 8, 16));
    entries.push_back(std::make_unique<Artist>("The Weeknd", "Pop", 10));
    entries.push_back(std::make_unique<Artist>("Adele", "Soul", 9));
}

class MainWindow final : public QMainWindow {
public:
    // Build the window and connect its controls.
    MainWindow() {
        ui_.setupUi(this);
        ui_.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        // Connect UI actions to the functions that handle them.
        connect(ui_.filterComboBox, &QComboBox::currentTextChanged, this, [this](const QString&) { refresh(); });
        connect(ui_.addSongButton, &QPushButton::clicked, this, [this] {
            ::addSong(entries_, this);
            refresh();
        });
        connect(ui_.addAlbumButton, &QPushButton::clicked, this, [this] {
            ::addAlbum(entries_, this);
            refresh();
        });
        connect(ui_.artistsButton, &QPushButton::clicked, this, [this] { showRanking("Artist"); });
        connect(ui_.songsButton, &QPushButton::clicked, this, [this] { showRanking("Song"); });
        connect(ui_.albumsButton, &QPushButton::clicked, this, [this] { showRanking("Album"); });

        loadSampleMusic(entries_);
        refresh();
    }

private:
    MusicLibrary entries_;
    Ui::MainWindow ui_;

    // Rebuild the table using the selected type filter.
    void refresh() {
        const QString selected = ui_.filterComboBox->currentText();
        ui_.tableWidget->setRowCount(0);
        for (const auto& entry : entries_) {
            if (selected != "All" && QString::fromStdString(entry->type()) != selected)
                continue;

            const int row = ui_.tableWidget->rowCount();
            ui_.tableWidget->insertRow(row);
            ui_.tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(entry->type())));
            ui_.tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(entry->title())));
            ui_.tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(entry->artistName())));
            ui_.tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(entry->rating()) + "/10"));
            ui_.tableWidget->setItem(row, 4, new QTableWidgetItem(entry->trackCount() ? QString::number(entry->trackCount()) : "-"));
        }
    }

    // Display entries of one type ordered by rating.
    void showRanking(const QString& type) {
        auto items = getRankedItems(entries_, type.toStdString());

        QString text;
        for (const auto* item : items)
            text += QString("%1 — %2 (%3/10)\n").arg(QString::fromStdString(item->title()),
                QString::fromStdString(item->artistName())).arg(item->rating());
        QMessageBox::information(this, "Top " + type + "s", text.isEmpty() ? "No entries yet." : text);
    }
};

// Start the Qt application and show the main window.
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
