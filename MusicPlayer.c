// MusicPlayer.c
// Implements the music playlist manager logic

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "MusicPlayer.h"

#define ORIGINAL_FILE_NAME "Playlist.txt"
#define UPDATED_FILE_NAME "Updated Playlist.txt"

// Remove leading/trailing spaces from a string
void trim_spaces(char** str) {
	char* start = *str;
	char* end = *str + strlen(*str) - 1; //-1 for '\0'
	while (*end == ' ') end--;
	*(++end) = '\0';

	while (*start == ' ') {
		start++;
	}
	*str = start;
}

// Read a playlist text file and build a doubly linked list of songs
Song* ReadTxtFile(char* file) {
	FILE* fp = fopen(file, "r");
	if (!fp) {
		printf("Error: Could not open file %s\n", file);
		char input = _getch();
		return NULL;
	}

	fscanf(fp, "%*[^\n]\n"); // Skip header line



	int id, trackNo, songs_count;
	char artistName[50]; //+1 for '\0'
	char albumName[50]; //+1 for '\0'
	char trackName[50]; //+1 for '\0'

	int first_song = 1;
	Song* head = NULL;
	Song* prev_song = NULL;

	while (fscanf(fp,
		"%6d%31[^\n]%30[^\n]%10d%50[^\n]",
		&id, artistName, albumName, &trackNo, trackName) > 0)
	{

		char* pArtist = artistName;
		trim_spaces(&pArtist);

		char* pAlbum = albumName;
		trim_spaces(&pAlbum);

		char* pTrack = trackName;
		trim_spaces(&pTrack);

		Song* new_song = (Song*)malloc(sizeof(struct Song));
		new_song->id = id;
		strcpy(new_song->artistName, pArtist);
		strcpy(new_song->albumName, pAlbum);
		new_song->trackNo = trackNo;
		strcpy(new_song->trackName, pTrack);
		new_song->prev = prev_song;
		if (first_song) {
			head = new_song;
			first_song = 0;
		}
		else prev_song->next = new_song;
		prev_song = new_song;
	}
	if (prev_song) {
		prev_song->next = NULL;
	}
	fclose(fp);
	return head;
}

// Write the current playlist to a text file
void UpdateTxtFile(Song* playlist, char* file) {
	FILE* fp = fopen(file, "w");
	if (!fp) {
		printf("Error: Could not open file %s\n", file);
		char input = _getch();
		return;
	}

	fprintf(fp, "%-5s %-30s %-29s %-9s %-30s\n",
		"ID", "ArtistName", "AlbumName", "TrackNo", "TrackName");
	while (playlist) {
		fprintf(fp, "%-5d %-30s %-29s %-9d %-30s\n",
			playlist->id, playlist->artistName,
			playlist->albumName, playlist->trackNo,
			playlist->trackName);
		playlist = playlist->next;
	}
	fclose(fp);
}

// Free memory allocated for the playlist linked list
void FreePlaylist(Song** head) {
	if (!head) return;

	system("cls");
	printf("See you next time;)\n");

	Song* song = *head;
	while (song) {
		Song* next_song = song->next;
		free(song);
		song = next_song;
	}
	*head = NULL;
}

// Display the main menu and current playlist
void PrintMenu(Song* head, Song* currentSong, int playing) {
	system("cls");
	printf("Playlist:\n");
	printf("%-5s %-30s %-29s %-10s %-30s %-3s\n",
		"ID", "ArtistName",
		"AlbumName", "TrackNo",
		"TrackName", "CurrentSong");
	Song* song = head;
	while (song) {
		if (song == currentSong) printf(" ");
		printf("%-5d %-30s %-29s %-10d %-30s",
			song->id, song->artistName,
			song->albumName, song->trackNo,
			song->trackName);
		if (song == currentSong) printf("<-");
		song = song->next;
		printf("\n");
	}

	if (playing && head) {
		printf("\nPlaying:\n");
		printf("%s by %s", currentSong->trackName, currentSong->artistName);
	}
	else printf("\nPauseing...");

	printf("\n\nMenu:\n");
	printf("Press e to play/stop a song\n");//v
	printf("Press n for next song\n");//v
	printf("Press p for previes song\n");//v
	printf("Press d to delete the current song\n");//v
	printf("Press a to add a song\n");//v
	printf("Press s to sort the playlist\n");
	printf("Press S to search a song\n");
	printf("Press r to randomize the playlist order\n");
	printf("Press E to exit\n");//v
}

// Move to the next song in the playlist
void NextSong(struct Song** currentSong, struct Song* head) {
	if (!head) return;

	if ((*currentSong)->next) *currentSong = (*currentSong)->next;
	else *currentSong = head;
}

// Move to the previous song in the playlist
void PrevSong(struct Song** currentSong, struct Song* head) {
	if (head == NULL) return;

	if ((*currentSong)->prev) *currentSong = (*currentSong)->prev;

	else {
		Song* p = head;
		while (p->next) p = p->next;
		*currentSong = p;
	}
}

// Delete the current song from the playlist
void DeleteSong(Song** currentSong, Song** head) {
	if (!*head) return;

	Song* NewcurrentSong;
	if ((*currentSong)->prev) {
		(*currentSong)->prev->next = (*currentSong)->next;
		NewcurrentSong = (*currentSong)->prev;
	}
	else {
		*head = (*currentSong)->next;
		NewcurrentSong = *head;
		if (NewcurrentSong)
			while (NewcurrentSong->next)
				NewcurrentSong = NewcurrentSong->next;
	}


	if ((*currentSong)->next)
		(*currentSong)->next->prev = (*currentSong)->prev;

	free(*currentSong);
	*currentSong = NewcurrentSong;
}

// Add a new song to the end of the playlist
void AddNewSong(Song** currentSong, Song** head) {
	struct Song* new_song = (struct Song*)malloc(sizeof(struct Song));

	system("cls");
	printf("===Add Song===\n");

	//create the new song as the tail and adding all of the categories of the song
	printf("New song id:");
	scanf("%d", &new_song->id);

	printf("New song artistName:");
	scanf(" %30[^\n]", new_song->artistName);


	printf("New song albumName:");
	scanf(" %30[^\n]", new_song->albumName);

	printf("New song trackNo:");
	scanf("%d", &new_song->trackNo);

	printf("New song trackName:");
	scanf(" %30[^\n]", new_song->trackName);

	new_song->next = NULL;
	new_song->prev = NULL;
	if (*head) {
		struct Song* temp = *head;
		while (temp->next) temp = temp->next;
		new_song->prev = temp;
		temp->next = new_song;
	}
	else {
		*head = new_song;
		*currentSong = *head;
	}
}

void Swap_list(Song** song1, Song** song2, Song** head) {
	if (!(*song1) || !(*song2) || *song1 == *song2) return;

	if (*head == *song1) *head = *song2;
	else if (*head == *song2) *head = *song1;

	//song1 just before song2
	if ((*song1)->next == *song2) {
		if ((*song1)->prev) (*song1)->prev->next = *song2;
		if ((*song2)->next) (*song2)->next->prev = *song1;
		(*song2)->prev = (*song1)->prev;
		(*song1)->next = (*song2)->next;
		(*song1)->prev = *song2;
		(*song2)->next = *song1;
		return;
	}//song1 just before song2
	else if ((*song2)->next == *song1) {
		if ((*song2)->prev) (*song2)->prev->next = *song1;
		if ((*song1)->next) (*song1)->next->prev = *song2;
		(*song1)->prev = (*song2)->prev;
		(*song2)->next = (*song1)->next;
		(*song2)->prev = *song1;
		(*song1)->next = *song2;
		return;
	}

	//Non-adjacent
	if ((*song1)->prev) (*song1)->prev->next = *song2;
	if ((*song2)->prev) (*song2)->prev->next = *song1;

	if ((*song1)->next) (*song1)->next->prev = *song2;
	if ((*song2)->next) (*song2)->next->prev = *song1;

	Song* temp = (*song1)->next;
	(*song1)->next = (*song2)->next;
	(*song2)->next = temp;

	temp = (*song1)->prev;
	(*song1)->prev = (*song2)->prev;
	(*song2)->prev = temp;
}

void Swap_arr(Song** a, Song** b) {
	Song* temp = *a;
	*a = *b;
	*b = temp;
}

Song** Build_Array(Song** head, int* sz) {
	Song* song = *head;
	*sz = 0;
	while (song) {
		(*sz)++;
		song = song->next;
	}
	Song** arr = (Song**)malloc((*sz) * sizeof(Song*));

	song = *head;
	int i = 0;
	while (song) {
		arr[i++] = song;
		song = song->next;
	}
	return arr;
}

void Heapify(Song** arr, int sz, int root_indx, char input) {
	int largest_indx = root_indx;
	int left_indx = 2 * root_indx + 1;
	int right_indx = 2 * root_indx + 2;

	if (left_indx < sz) {
		if ((input == '1' && arr[left_indx]->id > arr[largest_indx]->id) ||
			(input == '2' && strcmp(arr[left_indx]->artistName, arr[largest_indx]->artistName) > 0) ||
			(input == '3' && strcmp(arr[left_indx]->albumName, arr[largest_indx]->albumName) > 0) ||
			(input == '4' && arr[left_indx]->trackNo > arr[largest_indx]->trackNo) ||
			(input == '5' && strcmp(arr[left_indx]->trackName, arr[largest_indx]->trackName) > 0)) {
			largest_indx = left_indx;
		}
	}

	if (right_indx < sz) {
		if ((input == '1' && arr[right_indx]->id > arr[largest_indx]->id) ||
			(input == '2' && strcmp(arr[right_indx]->artistName, arr[largest_indx]->artistName) > 0) ||
			(input == '3' && strcmp(arr[right_indx]->albumName, arr[largest_indx]->albumName) > 0) ||
			(input == '4' && arr[right_indx]->trackNo > arr[largest_indx]->trackNo) ||
			(input == '5' && strcmp(arr[right_indx]->trackName, arr[largest_indx]->trackName) > 0)) {
			largest_indx = right_indx;
		}
	}

	if (largest_indx != root_indx) {
		Swap_arr(&arr[root_indx], &arr[largest_indx]);
		Heapify(arr, sz, largest_indx, input);
	}
}

void HeapSort(Song** arr, int sz, char input) {
	// Build Max heap
	for (int root_indx = sz / 2 - 1; root_indx >= 0; root_indx--)
		Heapify(arr, sz, root_indx, input);

	// Extract elements from heap one by one
	for (int i = sz - 1; i > 0; i--) {
		// Move current root to end
		Swap_arr(&arr[0], &arr[i]);
		// call max heapify on the reduced heap
		Heapify(arr, i, 0, input);
	}
}

void Array2List(Song** arr, Song** head, int sz, char dir, Song** currentSong) {
	Song* prev_song = NULL;
	Song* song = *head;
	if (dir == 'a') { // Ascending
		for (int i = 0; i < sz; i++) {
			arr[i]->prev = prev_song;
			if (i < sz - 1)
				arr[i]->next = &arr[i + 1];
			else
				arr[i]->next = NULL;

			if (prev_song)
				prev_song->next = arr[i];

			prev_song = arr[i];


		}
		*head = arr[0];
	}

	else if (dir == 'd') { // Descending
		for (int i = sz - 1; i >= 0; i--) {
			arr[i]->prev = prev_song;
			if (i > 0)
				arr[i]->next = &arr[i - 1];
			else
				arr[i]->next = NULL;

			if (prev_song)
				prev_song->next = arr[i];

			prev_song = arr[i];


		}
		*head = arr[sz - 1];
	}
}

void Sort(Song** head, Song** currentSong) {
	if (!(*head)) return;
	if ((!(*head)->next)) return;

	system("cls");
	printf("===Sort===\n");
	printf("\nBy which field would you like to sort the playlist?\n");
	printf("1. ID\n");
	printf("2. Artist Name\n");
	printf("3. Album Name\n");
	printf("4. Track Number\n");
	printf("5. Track Name\n");
	printf("to exit press any other key\n");
	printf("Enter your choice: ");
	char input = _getch();
	char dir;
	Song** arr;
	int sz;
	if ('1' <= input && input <= '5') {
		printf("\nAscend/Descend (a/d): ");
		dir = _getch();
		while (dir != 'a' && dir != 'd') {
			printf("Plese enter direction again (a/d): ");
			dir = _getch();
		}

		arr = Build_Array(head, &sz);
		HeapSort(arr, sz, input);
		Array2List(arr, head, sz, dir, currentSong);
		free(arr);
	}
}

int StringContains(char* str, char* source) {
	int i = 0;
	while (str[i] != '\0') {
		if (tolower(str[i]) != tolower(source[i])) return 0;
		i++;
	}
	return 1;
}

void Search(Song** head, Song** currentSong) {
	char input;
	system("cls");
	printf("===Search===\n");
	printf("\nBy which field would you like to search?\n");
	printf("1. ID\n");
	printf("2. Artist Name\n");
	printf("3. Album Name\n");
	printf("4. Track Number\n");
	printf("5. Track Name\n");
	printf("to exit press any other key\n");
	printf("Enter your choice: ");
	scanf(" %c", &input);
	int num_search;
	char str_search[30];
	char serch_word[30];
	Song* song;
	if ('1' <= input && input <= '5') {
		switch (input) {
		case '1':
			strcpy(serch_word, "ID");
			break;
		case '2':
			strcpy(serch_word, "Artist Name");
			break;
		case '3':
			strcpy(serch_word, "Album Name");
			break;
		case '4':
			strcpy(serch_word, "Track Number");
			break;
		case '5':
			strcpy(serch_word, "Track Name");
			break;
		}
		printf("Please enter the %s you want: ", serch_word);
		if (input == '1' || input == '4') {
			scanf("%d", &num_search);
			song = *head;
			while (song) {
				if (input == '1' && song->id == num_search ||
					input == '4' && song->trackNo == num_search) {
					*currentSong = song;
					return;
				}
				song = song->next;
			}
			printf("Not found:(\n");
			printf("Enter any key to continue");
			input = _getch();
			return;
		}
		else {
			scanf(" %[^\n]", str_search);
			song = *head;
			while (song) {
				if (input == '2' && StringContains(str_search, song->artistName) ||
					input == '3' && StringContains(str_search, song->albumName) ||
					input == '5' && StringContains(str_search, song->trackName))
				{
					*currentSong = song;
					return;
				}
				song = song->next;
			}
			printf("Not found:(\n");
			printf("Enter any key to continue");
			input = _getch();
			return;
		}
	}
}

void Randomize(Song** head, Song** currentSong) {
	if (!(*head)) return;
	if ((!(*head)->next)) return;

	int sz;
	Song** arr = Build_Array(head, &sz);

	for (int i = sz - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		Song* temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	Array2List(arr, head, sz, 'a', currentSong);
	free(arr);
}

void Menu(Song** head, char* updated_file_name) {
	struct Song* currentSong = *head;
	int playing = 0;
	PrintMenu(*head, currentSong, playing);
	srand(time(NULL));

	char input;
	int sort_index;
	while (1) {
		if (_kbhit()) {
			input = _getch();
			switch (input) {
			case 'e':
				playing ^= 1;
				PrintMenu(*head, currentSong, playing);
				break;
			case 'n':
				NextSong(&currentSong, *head);
				PrintMenu(*head, currentSong, playing);
				break;
			case 'p':
				PrevSong(&currentSong, *head);
				PrintMenu(*head, currentSong, playing);
				break;
			case 'd':
				DeleteSong(&currentSong, head);
				UpdateTxtFile(*head, updated_file_name);
				PrintMenu(*head, currentSong, playing);
				break;
			case 'a':
				AddNewSong(&currentSong, head);
				UpdateTxtFile(*head, updated_file_name);
				PrintMenu(*head, currentSong, playing);
				break;
			case 's':
				Sort(head, &currentSong);
				UpdateTxtFile(*head, updated_file_name);
				PrintMenu(*head, currentSong, playing);
				break;
			case 'S':
				Search(head, &currentSong);
				PrintMenu(*head, currentSong, playing);
				break;
			case 'r':
				Randomize(head, &currentSong);
				UpdateTxtFile(*head, updated_file_name);
				PrintMenu(*head, currentSong, playing);
				break;
			case 'E':
				FreePlaylist(head);
				return;
			}
		}
	}
}
