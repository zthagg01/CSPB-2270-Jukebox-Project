# Jukebox Application

This is a Jukebox Application implemented in C++. It allows users to control playback, edit the song library, and manage playlists.

## Data Structure Implemented

#### Deque (std::deque):  

**Purpose:** The deque is chosen for its ability to manage playlists due to its flexibility in inserting and removing elements at both ends. This feature is particularly useful for operations like adding new playlists, accessing the current playlist, and reordering playlists efficiently.

## Project Structure

The project follows a modular structure, with each component implemented in a separate header and source file.

#### player.h and player.cpp: 

Contains the declaration and implementation of the Player class, which manages playback functionality such as playing, pausing, skipping tracks, and toggling repeat mode.

#### playlist.h and playlist.cpp: 

Contains the declaration and implementation of the Playlist class, which represents a collection of songs.

#### playlistManager.h and playlistManager.cpp:

Contains the declaration and implementation of the PlaylistManager class, which manages the loading and manipulation of playlists.

#### song.h and song.cpp: 

Contains the declaration and implementation of the Song class, which represents an individual song with attributes like title, artist, and duration.

#### ui.h and ui.cpp:

Contains the declaration and implementation of the UI class, which provides a user interface for interacting with the Jukebox Application.

## Dependencies

**CSV Files:** Holds all song and playlist data.

## Building and Running the Application

To build and run the Jukebox Application, follow these steps:

**Open a Terminal:** Open your terminal application.

**Navigate to the Project Directory:** Use the `cd` command to navigate to the directory where the project is stored.

**Clean the Build:**
Run `make clean` to remove any existing object files and executables.

**Build the Application:**
Run `make` to compile the source files and generate object files (`.o` files).

**Run the Application:**
Execute the command `./a.out` to run the compiled application.

**Alternatively use `make clean && make && ./a.out` to get the program running quicker.

## Additional Notes

Anyone can modify the CSV files to add or remove songs and playlists as needed. Ensure that the file structure and data format are maintained for proper functioning of the application.
