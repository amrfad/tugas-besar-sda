#ifndef SONG_H
#define SONG_H

#include <string>
#include "MerkleTree.h"
#include <windows.h>
#include <mmsystem.h>
using namespace std;

struct Song {
    int songId;
    string title;
    string artist;
    string hash; // Hash lagu
    MerkleTree merkleTree; // Merkle Hash Tree untuk lagu ini
};

struct SongNode {
    Song song;
    SongNode* next;
};

struct LicenseTicket {
    int songId;
    int userId;
    string purchaseDate;
    string expirationDate;
    string hash; // Hash tiket lisensi
};

void playSong(const Song& song);

class SongList {
    private:
        SongNode* head;
        SongNode* tail;
        int size;
    public:
        SongList();
        ~SongList();
        void addSong(Song& song);
        void removeSong(int songId);
        void printSongs();
        SongNode* searchSong(const string& title);
        void sortSongs(bool ascending = true);
        SongNode* getSongNode(int songId);
        Song* getSong(int songId);
        void playingSong(string& title);
        int getSize();
        SongNode* getHead();
};
#endif