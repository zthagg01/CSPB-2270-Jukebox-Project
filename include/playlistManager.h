#ifndef PLAYLIST_MANAGER_H
#define PLAYLIST_MANAGER_H

#include <list>
#include <unordered_set>
#include "playlist.h"

class PlaylistManager {

    const std::string FILE_NAME = "res/playlist.csv";
    static PlaylistManager* instance_;
    std::list<Playlist> playlists_;
    int totalPlaylists;
    std::unordered_set<std::string> uniqueSongs;
    std::unordered_set<std::string> uniqueAuthors;

    public:
        // Delete copy and move constructors and assign operators
        PlaylistManager(const PlaylistManager&) = delete;
        PlaylistManager(PlaylistManager&&) = delete;
        PlaylistManager& operator=(const PlaylistManager&) = delete;
        PlaylistManager& operator=(PlaylistManager&&) = delete;
    
        // Singleton access method
        static PlaylistManager* getInstance();
        static void releaseInstance();
        
        void addPlaylist(const Playlist& playlist);
        void addSongToPlaylist(const std::string&, const Song&);
        std::list<Playlist>& getPlaylists();

        // Getters
        int getTotalPlaylists() const;
        int getTotalUniqueSongs() const;
        int getTotalUniqueAuthors() const;
        void updateStatistics();

    private:

        // Private constructor and destructor to prevent external instantiation
        PlaylistManager() { readFile(); }
        ~PlaylistManager() {}

        // Read in file!  
        void readFile();
        std::string trim(const std::string&);

};

#endif // PLAYLIST_MANAGER_H
