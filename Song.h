#ifndef SONG_H
#define SONG_H

#include <string>
#include "MerkleTree.h"
using namespace std;

struct Song {
    int songId;
    string title;
    string artist;
    string hash; // Hash lagu
    MerkleTree merkleTree; // Merkle Hash Tree untuk lagu ini
};

struct LicenseTicket {
    int songId;
    int userId;
    string purchaseDate;
    string expirationDate;
    string hash; // Hash tiket lisensi
};

#endif