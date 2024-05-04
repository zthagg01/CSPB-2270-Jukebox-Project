#ifndef UI_H
#define UI_H

#include "player.h"

class UI{

    Player* player_;
    bool    isValid_;

    public:

        // Constructor / Destructors
        UI();
        ~UI();

        // Display Different Menus
        void displayMainMenu();
        void displayMainTitle();
        void displayEditPlaylistMenu();
        void displayEditSongLibraryMenu();
        void displayControlPlaybackMenu();
        void displayRearrangePlaylistsMenu();
        
        // Program Logic. 
        void handleUserInput();
        void handlePlaylistMenu();
        void handlePlaybackMenu();
        void handleEditSongsMenu();
        void run();

};

#endif // UI_H
