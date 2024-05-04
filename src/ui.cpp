#include <iostream>
#include <iomanip>
#include "../include/ui.h"
#include "../include/playlistManager.h"

UI::UI() : player_(nullptr), isValid_(true) {}

UI::~UI() { 
    if(player_ != nullptr){ 
        delete player_;  
        player_ = nullptr; 
    }
}

void printLine(const std::string& content){
    const int totalWidth = 55;
    std::cout << "|" << std::left << std::setw(totalWidth - 1) << content << "|\n";
}

void border(){
    const int totalWidth = 55;
    std::cout << "+";
    for (int i = 1; i < totalWidth; i++) { std::cout << "-"; }
    std::cout << "+\n";

}

void centerTitle(const std::string& title){
    const int totalWidth = 55;  // Total width including borders
    int titleWidth = title.length();
    int titlePadding = (totalWidth - titleWidth - 2) / 2;  // Calculate padding for title
    std::cout << "|" << std::setw(titlePadding + titleWidth) << std::right << title 
              << std::setw(totalWidth - titlePadding - titleWidth +1) << " |\n";
}

void UI::displayMainTitle(){

    PlaylistManager* pm = PlaylistManager::getInstance();
    pm->updateStatistics();  // Ensure statistics are up to date

    int totalWidth = 55;  
    int labelWidth = 25;  

    std::string title = "JUKEBOX APP";

    border();
    centerTitle(title);
    border();

    std::cout << std::left << std::setw(labelWidth)
              << "| Playlists Loaded: "  << pm->getTotalPlaylists() << "/5"
              << std::right << std::setw(totalWidth - labelWidth - 2) << "|" << "\n"
              << std::left << std::setw(labelWidth)
              << "| Total Unique Songs: " << pm->getTotalUniqueSongs()
              << std::right << std::setw(totalWidth - labelWidth -1) << "|" << "\n"
              << std::left << std::setw(labelWidth)
              << "| Total Unique Authors: " << pm->getTotalUniqueAuthors()
              << std::right << std::setw(totalWidth - labelWidth-1) << "|" << "\n";
}



void UI::displayMainMenu() {

    displayMainTitle();
    border();

    // Static options
    printLine(" [1] Control Playback");
    printLine(" [2] Edit Song Library");
    printLine(" [3] Rearrange Playlists");
    printLine(" [Q] Quit");

    border();

    // Command prompt line
    std::cout << "| Enter command: ";

}

void UI::displayEditSongLibraryMenu() {


    std::string title = "EDIT SONG LIBRARY";

    border();
    centerTitle(title);
    border();
    printLine(" " + player_->play());
    printLine(" Current Playlist: " + player_->getCurrentPlaylist()->getName());
    border();

    // Static options
    printLine(" [A] Add Song to the end of the Current Library (Temp)");
    printLine(" [B] Back to Main Menu");

    border();

    // Command prompt line
    std::cout << "| Enter command: ";
}

void UI::displayControlPlaybackMenu() {

    // Centered "CONTROL PLAYBACK" title within borders
    std::string title = "CONTROL PLAYBACK";
    std::string repeat = player_->isRepeat() ? "ON" : "OFF";

    border();
    centerTitle(title);
    border();

    printLine(" " + player_->play());
    printLine(" Current Playlist: " + player_->getCurrentPlaylist()->getName());
    printLine(" Repeat: " + repeat);
    
    border();

    // Static options
    printLine(" [N] Next Track");
    printLine(" [L] Previous Track");
    printLine(" [F] First Track of Current Playlist");
    printLine(" [X] Toggle Jukebox Repeat");
    printLine(" [B] Back to Main Menu");

    border();

    // Command prompt line
    std::cout << "| Enter command: ";
}


void UI::displayRearrangePlaylistsMenu() {

    // Centered "CONTROL PLAYBACK" title within borders
    std::string title = "REARRANGE PLAYLISTS";

    border();
    centerTitle(title);
    border();
    printLine(" Current Playlist: " + player_->getCurrentPlaylist()->getName());
    border();

    // Gets the current list. 
    std::deque<Playlist> currentList = player_->getQueue();

    // Iterate through the list of playlists and print each with an index
    int index = 1; // Start indexing from 1
    for (const auto& playlist : currentList) {
        printLine(" " + std::to_string(index) + ". " + playlist.getName());
        index++;
    } 

    // Static options
    border();
    printLine(" Instructions: Enter the  numbers of ");
    printLine(" playlist you want to make current! ");
    printLine(" [B] Back to Main Menu");

    border();
    std::cout << "| Enter command: ";

}

void UI::handlePlaylistMenu(){

    bool isValid = true;
    PlaylistManager* pm = PlaylistManager::getInstance();
    std::list<Playlist> currentList = pm->getPlaylists();

    while (isValid) {
        // Display the rearrange playlists menu
        displayRearrangePlaylistsMenu();

        // Take in the user information
        std::string input;
        std::cin >> input;

        // Convert to lowercase if it is an alphabetical input
        if (isalpha(input[0])) {
            input[0] = tolower(input[0]);
            if (input[0] == 'b') {
                isValid = false; // Break out of the loop to go back
                return;
            }
        }

        // Check if the input is a valid number and within range
        if (isdigit(input[0])) {
            int choice = std::stoi(input); // Convert input to integer
            int size = currentList.size();
            if (choice > 0 && choice <= size) {
                player_->swapPlaylistToTop(choice -1);
                std::cout << "| Playlist " << choice << " selected.\n";
                return;;
            }
        }

        // Handle invalid command
        std::cout << "| Invalid command. Please try again.\n";
    }
}

void UI::handleEditSongsMenu(){

    bool isValid = true;
    std::string name;
    std::string author;

    while (isValid) {

        // Add the menu. 
        displayEditSongLibraryMenu();

        // Take in the user information. 
        char command;
        std::cin >> command;

        // Add a to lower. 
        if(isalpha(command)){ command = tolower(command); }

        // Look through the logic an access the proper command. 
        switch (command) {

            // Next Track
            case 'a':
                std::cout << "| Enter the Song: ";
                std::cin.ignore();
                std::getline(std::cin,name);
                std::cout << "| Enter the Author: ";
                std::getline(std::cin,author);
                player_->getCurrentPlaylist()->addSong(Song(name, author, 10));
                break;
            
            // Go back to the previous menu. 
            case 'b': 
                isValid = false;
                break;
            
            // Default Case 
            default:
              std::cout << "| Invalid command. Please try again.\n";
        }

    }

}

void UI::handlePlaybackMenu(){

    bool isValid = true;

    while (isValid) {

        // Add the menu. 
        displayControlPlaybackMenu();

        // Take in the user information. 
        char command;
        std::cin >> command;

        // Add a to lower. 
        if(isalpha(command)){ command = tolower(command); }

        // Look through the logic an access the proper command. 
        switch (command) {

            // Next Track
            case 'n':
                player_->nextSong();
                break;
            
            // Previous Track
            case 'l':
                player_->previousSong();
                break;
        
            // First Track of current playlist
            case 'f': 
                player_->firstTrack();
                break;

            // Toggle jukebox repeat
            case 'x': 
                player_->setRepeat(!player_->isRepeat());
                break;

            // Go back to the previous menu. 
            case 'b': 
                isValid = false;
                break;
            
            // Default Case 
            default:
              std::cout << "| Invalid command. Please try again.\n";
        }

    }

}


void UI::handleUserInput() {
    
    // Take in the user information. 
    char command;
    std::cin >> command;

    // Add a to lower. 
    if(isalpha(command)){ command = tolower(command); }

    // Look through the logic an access the proper command. 
    switch (command) {
        // Handle Control Playback
        case '1': 
            handlePlaybackMenu();
            break;
        
        // Handle Edit Song Library
        case '2':
            handleEditSongsMenu();
            break;
        
        // Handle Manage Playlists
        case '3':
            handlePlaylistMenu();
            break;
    
        // Quit
        case 'q':  
            isValid_ = false; 
            break;
        
        // Default Case 
        default:
          std::cout << "| Invalid command. Please try again.\n";
    }

}


void UI::run() {

    // Check to see if the player has been created. 
    if(player_ == nullptr){ player_ = new Player; }

    // Continue running the code until the user asks to quit. 
    while (isValid_) {
        
        // Run code. 
        try {
            displayMainMenu();
            handleUserInput();
        }

        // Catch any error.
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

    }

}
