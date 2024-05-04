#ifndef PLAYER_H
#define PLAYER_H

#include <deque>
#include <vector>
#include <list>
#include "playlist.h" 

struct ComparePlaylist {
    bool operator()(const Playlist& lhs, const Playlist& rhs) {
        // Smaller queue front: More songs = higher priority
        return lhs.getSongs().size() > rhs.getSongs().size();
    }
};

class Player {

    std::deque<Playlist> queue;
    Playlist* currentPlaylist; // const pointer
    std::list<Song>::const_iterator currentSongIterator;

    bool isPlaying;
    bool repeat;

    public:
        Player();
        ~Player();  // If we use dynamic allocation, we need a destructor

        void addPlaylist(const Playlist& playlist);
        std::string play();
        void firstTrack();
        void nextSong();
        void previousSong();
        void setRepeat(bool state);
        bool isRepeat() { return repeat; }
        bool isCurrentlyPlaying() const;
        Playlist* getCurrentPlaylist() { return currentPlaylist; }
        void swapPlaylistToTop(int index);
        std::deque<Playlist> getQueue() { return queue; }
};

#endif // PLAYER_H
