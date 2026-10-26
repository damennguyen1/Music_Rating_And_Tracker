#ifndef MAINWINDOW_H
#define MAINWINDOW_H

INCLUDE <wx / wx.h>
INCLUDE <wx / notebook.h>
INCLUDE <wx / spinctrl.h>
INCLUDE <vector>
INCLUDE "MusicLibrary.h"
INCLUDE "Favorites.h"
INCLUDE "FileManager.h"

CLASS MainWindow : PUBLIC wxFrame
PUBLIC :
MainWindow(title : wxString)

PRIVATE :
    // ----- Application objects (composition) -----
    library : MusicLibrary
    favorites : Favorites
    fileManager : FileManager
    currentResults : vector<MusicItem*>       // non-owning

    // ----- Widgets (owned by wx parents, never delete) -----
    tabs : wxNotebook *
    // Tab 1
    typeChoice : wxChoice *
    titleBox, artistBox, extraBox : wxTextCtrl *
    ratingSpin : wxSpinCtrl *
    addButton : wxButton *
    libraryList : wxListBox *
    // Tab 2
    searchBox : wxTextCtrl *
    filterChoice, sortChoice : wxChoice *
    searchButton : wxButton *
    resultsList : wxListBox *
    // Tab 3
    artistsList, songsList, albumsList : wxListBox *
    itemPicker, positionChoice : wxChoice *
    setFavoriteButton : wxButton *

    // ----- Setup helpers -----
    buildAddTab(parent)->wxPanel*
    buildSearchTab(parent)->wxPanel*
    buildFavoritesTab(parent)->wxPanel*
    buildMenuBar()

    // ----- Event handlers -----
    OnAdd(event: wxCommandEvent&)
    OnSearch(event: wxCommandEvent&)
    OnSetFavorite(event: wxCommandEvent&)
    OnSave(event: wxCommandEvent&)
    OnLoad(event: wxCommandEvent&)
    OnClose(event: wxCloseEvent&)

    // ----- Display refresh -----
    refreshLibraryList()
    refreshFavoritesLists()
    refreshItemPicker()
    refreshAllDisplays()

    // ----- Menu IDs -----
    ENUM{ ID_SAVE = wxID_HIGHEST + 1, ID_LOAD }

#endif
