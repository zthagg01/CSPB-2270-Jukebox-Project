#include <iostream>
#include "../include/player.h"
#include "../include/playlistManager.h"

Player::Player() : currentPlaylist(nullptr), isPlaying(false), repeat(false) {
    // Access the singleton instance of PlaylistManager
    PlaylistManager* pm = PlaylistManager::getInstance();
    
    // Load playlists from the PlaylistManager
    std::list<Playlist>& playlists = pm->getPlaylists();
    for (Playlist& playlist : playlists) {
        queue.push_back(playlist);
    }

    // Automatically set the first playlist if available
    if (!queue.empty()) {
        currentPlaylist = &queue.front();
        if (!currentPlaylist->getSongs().empty()) {
            currentSongIterator = currentPlaylist->getSongs().begin();
        }
    }
}

Player::~Player() {}

void Player::addPlaylist(const Playlist& playlist) {
    queue.push_back(playlist);
    // Update current playlist if necessary
    if (!currentPlaylist) {
        currentPlaylist = &queue.front();
        currentSongIterator = currentPlaylist->getSongs().begin();
    }
}

void Player::swapPlaylistToTop(int index) {
    int size = queue.size();
    if (index < 0 || size) {
        std::cout << "| Invalid index provided.\n";
        return;
    }

    if (index == 0) {
        std::cout << "| Playlist is already at the top.\n";
        return;
    }

    // Get the playlist at the given index
    auto it = queue.begin() + index;
    Playlist selectedPlaylist = *it;  // Make a copy of the playlist
    queue.erase(it);  // Remove the playlist from its current position
    queue.push_front(selectedPlaylist);  // Push it to the front of the deque

    // Update the currentPlaylist if necessary
    currentPlaylist = &queue.front();
    if (!currentPlaylist->getSongs().empty()) {
        currentSongIterator = currentPlaylist->getSongs().begin();
    }
}


std::string Player::play() {

    if (!currentPlaylist || currentPlaylist->getSongs().empty()) {
        return "No Playlist or Songs.";
    }

    isPlaying = true;
    const Song& song = *currentSongIterator;
    std::string output = "Now Playing: " + song.getTitle() + " by " + song.getArtist();

    if (output.length() > 50) {  // Check if the string exceeds 33 characters (36 - 3 for ellipsis)
        output = output.substr(0, 50) + "...";
    }

    return output;
}

void Player::nextSong() {
    if (currentPlaylist && currentSongIterator != currentPlaylist->getSongs().end()) {
        
        ++currentSongIterator;

        if (currentSongIterator == currentPlaylist->getSongs().end() && repeat) {
            currentSongIterator = currentPlaylist->getSongs().begin();
        }
        else if (currentSongIterator == currentPlaylist->getSongs().end()) {
            --currentSongIterator;
        }

        play();
    }
}

void Player::firstTrack(){
    currentSongIterator = currentPlaylist->getSongs().begin();
}

void Player::previousSong() {
    if (currentPlaylist && currentSongIterator != currentPlaylist->getSongs().begin()) {
        --currentSongIterator;
        play();
    }
}

void Player::setRepeat(bool state) {
    repeat = state;
}

bool Player::isCurrentlyPlaying() const {
    return isPlaying;
}
