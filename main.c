// main.c
// Entry point for the music playlist manager

#include <stdio.h>
#include "MusicPlayer.h"

int main() {
    char original_file_name[] = ORIGINAL_FILE_NAME;
    Song* playlist = ReadTxtFile(original_file_name);

    char updated_file_name[] = UPDATED_FILE_NAME;
    UpdateTxtFile(playlist, updated_file_name);

    Menu(&playlist, updated_file_name);

    return 0;
}