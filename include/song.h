#ifndef SONG_H
#define SONG_H

#include <string>

class Song{

    // Internal Variables
    std::string title_;
    std::string artist_;
    int priority_;          // Lower numbers mean higher priority

    public:
    
        // Constructors and Destructors
        Song();
        Song(const std::string&, const std::string&, const int&); 

        // GETTERS 
        std::string getTitle()  const;
        std::string getArtist() const;
        int getPriority() const;

        // Comparision Operator
        bool operator<(const Song& other) const;

};

#endif // SONG_H
