#include "../include/playlist.h"

// Default constructor initializes the playlist with an optional default name
Playlist::Playlist() : name_("Unnamed Playlist") {}

// Constructor that initializes the playlist with a specific name
Playlist::Playlist(const std::string& name) : name_(name) {}

// Adds a song to the playlist
void Playlist::addSong(const Song& song) { songs_.push_back(song); }

// Returns a constant reference to the list of songs
const std::list<Song>& Playlist::getSongs() const { return songs_; }

// Returns the name of the playlist
std::string Playlist::getName() const { return name_; }

