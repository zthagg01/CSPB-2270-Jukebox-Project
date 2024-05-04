#include <iostream>
#include <exception>
#include "../include/ui.h"
#include "../include/playlistManager.h"

int main () {
    
    // Create our jukebox app. 
    UI* jukebox = new UI;

    // Used for error checking in our program. 
    try { jukebox->run(); }

    catch (const std::exception& e) { 
        std::cerr << e.what() << std::endl; 
    }

    // Delete and set pointer to nullptr to 
    // remover the potential for dangling pointers. 
    delete jukebox;
    jukebox = nullptr;

    // Release the instance for our playlist manager. 
    PlaylistManager::releaseInstance();

    return 0;

}
