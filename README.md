# MusicPlayer

A simple console-based playlist manager written in C for Windows.

---

## Features

- Load playlist from a text file (`Playlist.txt`)
- Display playlist with current song indicator
- Play/Pause functionality simulation
- Navigate to next and previous songs
- Add new songs to the playlist
- Delete existing songs from the playlist
- Sort playlist by various fields (ID, Artist Name, Album Name, Track Number, Track Name)
- Search songs by different criteria
- Randomize playlist order
- Save updated playlist to a text file (`Updated Playlist.txt`)

---

## Requirements

- Windows OS
- GCC compiler (e.g., MinGW)
- Console capable of handling `_getch()` and `_kbhit()` (Windows console)

---

## How to Build

1. Clone or download the repository.
2. Open a terminal in the project directory.
3. Compile using GCC:
   ```bash
   gcc main.c Playlist.c -o MusicPlayer.exe
    ```
Run the executable:
  ```bash
MusicPlayer.exe
 ```

## Usage
Use the keyboard to control the playlist:

e: Play/Pause current song

n: Next song

p: Previous song

a: Add a new song

d: Delete current song

s: Sort playlist

S: Search for a song

r: Randomize playlist

E: Exit the program

The playlist will be loaded from Playlist.txt and saved to Updated Playlist.txt after changes.

Playlist File Format
The playlist file should be a text file with the following columns (with a header line):


|ID|ArtistName|AlbumName|TrackNo|TrackName|
|--|----------|---------|-------|----------|


Each song entry should follow the header with matching fields.

## Project Structure
main.c – Program entry point and main menu control

Playlist.c – Core functionality for playlist operations

Playlist.h – Header file declaring functions and the Song struct

Playlist.txt – Sample playlist input file

Updated Playlist.txt – Output playlist file after modifications

## License
This project is open source and free to use.

## Author
Roi Kagan

