#ifndef SONG_H
#define SONG_H

#include <string>
#include "MerkleTree.h"
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#include <fstream>
#include <stdbool.h>
// using namespace std;

struct Song {
    int songId;
    std::string title;
    std::string artist;
    std::string hash; // Hash lagu
    MerkleTree merkleTree; // Merkle Hash Tree untuk lagu ini
};

struct SongNode {
    Song song;
    SongNode* next;
};

class SongList {
    private:
        SongNode* head;
        SongNode* tail;
        int size;
    public:
        SongList();
        // ~SongList();
        void addSong(Song& song);
        void removeSong(int songId);
        void printSongs();
        SongNode* searchSong(const std::string& title);
        bool isHashExist(std::string title);
        void sortSongs(bool ascending = true);
        SongNode* getSongNode(int songId);
        Song* getSong(int songId);
        void playingSong(std::string& title);
        int getSize();
        SongNode* getHead();
        void saveSongsToFile(); 
        void loadSongsFromFile();
};

extern SongList _SongList;

void calculateHash(Song* song, bool isCloud);
void playSong(const Song& song);
void downloadSong(std::string songName);
void uploadSong(std::string songName);

#endif