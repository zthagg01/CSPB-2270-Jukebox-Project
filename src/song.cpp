#include <iostream>
#include <limits>
#include "../include/song.h"

Song::Song() 
    : title_(""), artist_(""), priority_(std::numeric_limits<int>::max()){}


Song::Song(const std::string& title, const std::string& artist, const int& priority)
    : title_(title), artist_(artist), priority_(priority){}


std::string Song::getTitle()  const     { return title_; }
std::string Song::getArtist() const     { return artist_; }
int Song::getPriority() const           { return priority_; };

bool Song::operator<(const Song& other) const { 
    return priority_ > other.priority_;
}
