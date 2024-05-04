#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <list>
#include "song.h"

class Playlist{

    std::string name_;
    std::list<Song> songs_;

    public: 
        Playlist();
        Playlist(const std::string& name);
        void addSong(const Song& song);
        const std::list<Song>& getSongs() const;
        std::string getName() const;

};

#endif
