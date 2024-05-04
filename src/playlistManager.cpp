#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/playlistManager.h"

PlaylistManager* PlaylistManager::instance_ = nullptr;

PlaylistManager* PlaylistManager::getInstance() {
    if (instance_ == nullptr) {
        instance_ = new PlaylistManager();
    }
    return instance_;
}

void PlaylistManager::readFile() {

    // Open file 
    std::ifstream file(FILE_NAME);

    // Throw an error if the file does not exists. 
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + FILE_NAME);
    }

    std::string line;
    getline(file, line); // Skip the header line

    // Continue reading in from file. 
    while (getline(file, line)) {
        
        // Read in and break up the data. 
        std::stringstream ss(line);
        std::string playlistName, artistName, songTitle;
        
        // Deliminate Data. 
        getline(ss, playlistName, ',');
        getline(ss, artistName, ',');
        getline(ss, songTitle, ',');

        // Clean data 
        playlistName = trim(playlistName);
        playlistName = trim(playlistName);
        playlistName = trim(playlistName);

        // TODO: IF MORE THAN 5 PLAYLISTS THROW AN ERROR. 

        // Find or create the playlist
        Playlist* foundPlaylist = nullptr;
        for(auto &elem : playlists_){
            if(elem.getName() == playlistName){
                foundPlaylist = &elem;
                break;
            }
        }

        // If the playlist is not found create a new one. 
        if(foundPlaylist == nullptr){
            Playlist newPlaylist(playlistName);
            newPlaylist.addSong(Song(songTitle, artistName, 10));
            playlists_.push_back(newPlaylist);
        }

        // Playlist is found so add a song to it!
        else{
            foundPlaylist->addSong(Song(songTitle, artistName, 10));
        }

    }

    // Close file stream.
    file.close();
}

std::string PlaylistManager::trim(const std::string& str){

    size_t first = str.find_first_not_of(' ');
    if(first == std::string::npos) { return ""; }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));

}

void PlaylistManager::releaseInstance() {
    delete instance_;
    instance_ = nullptr;
}

void PlaylistManager::addPlaylist(const Playlist& playlist) {
    playlists_.push_back(playlist);
}

void PlaylistManager::addSongToPlaylist(const std::string& playlistName, const Song& song) {
    for (auto& playlist : playlists_) {
        if (playlist.getName() == playlistName) {
            playlist.addSong(song);
            return;
        }
    }
}

std::list<Playlist>& PlaylistManager::getPlaylists() {
    return playlists_;
}

void PlaylistManager::updateStatistics() {
    uniqueSongs.clear();
    uniqueAuthors.clear();
    totalPlaylists = playlists_.size();
    
    for (const auto& playlist : playlists_) {
        for (const Song& song : playlist.getSongs()) {
            uniqueSongs.insert(song.getTitle());
            uniqueAuthors.insert(song.getArtist());
        }
    }
}

int PlaylistManager::getTotalPlaylists() const {
    return totalPlaylists;
}

int PlaylistManager::getTotalUniqueSongs() const {
    return uniqueSongs.size();
}

int PlaylistManager::getTotalUniqueAuthors() const {
    return uniqueAuthors.size();
}
