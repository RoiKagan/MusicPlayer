#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <stdio.h>

#define ORIGINAL_FILE_NAME "Playlist.txt"
#define UPDATED_FILE_NAME "Updated Playlist.txt"

// Song struct definition
typedef struct Song {
    int id;
    char artistName[31];
    char albumName[31];
    int trackNo;
    char trackName[31];
    struct Song* next;
    struct Song* prev;
} Song;

// Utility Functions
void trim_spaces(char** str);

// File I/O
Song* ReadTxtFile(char* file);
void UpdateTxtFile(Song* playlist, char* file);

// Playlist Management
void FreePlaylist(Song** head);
void AddNewSong(Song** currentSong, Song** head);
void DeleteSong(Song** currentSong, Song** head);

// Navigation
void NextSong(Song** currentSong, Song* head);
void PrevSong(Song** currentSong, Song* head);

// Sorting
void Sort(Song** head, Song** currentSong);
Song** Build_Array(Song** head, int* sz);
void Heapify(Song** arr, int sz, int root_indx, char input);
void HeapSort(Song** arr, int sz, char input);
void Array2List(Song** arr, Song** head, int sz, char dir, Song** currentSong);

// Searching
void Search(Song** head, Song** currentSong);
int StringContains(char* str, char* source);

// Randomization
void Randomize(Song** head, Song** currentSong);

// User Interface
void PrintMenu(Song* head, Song* currentSong, int playing);
void Menu(Song** head, char* updated_file_name);

#endif // MUSICPLAYER_H
