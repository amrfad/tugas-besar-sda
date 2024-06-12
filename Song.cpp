#include "Song.h"
#include "MerkleTree.h"

SongList _SongList = SongList();

SongList::SongList() {
    head = NULL;
    tail = NULL;
    size = 0;
}

// SongList::~SongList() {
//     SongNode* current = head;
//     while (current != NULL) {
//         SongNode* next = current->next;
//         delete current;
//         current = next;
//     }
// }

void SongList::addSong(Song& song) {
    SongNode* newNode = new SongNode;
    newNode->song = song;
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

void SongList::removeSong(int songId) {
    SongNode* current = head;
    SongNode* prev = NULL;
    while (current != NULL) {
        if (current->song.songId == songId) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            if (current == tail) {
                tail = prev;
            }
            delete current;
            size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void SongList::printSongs() {
    SongNode* current = head;
    while (current != NULL) {
        std::cout << "ID: " << current->song.songId << std::endl;
        std::cout << "Title: " << current->song.title << std::endl;
        std::cout << "Artist: " << current->song.artist << std::endl;
        std::cout << "Hash: " << current->song.hash << std::endl;
        std::cout << "Merkle Tree: " << std::endl;
        std::cout << std::endl;
        current = current->next;
    }
}

SongNode* SongList::searchSong(const std::string& title) {
    SongNode* current = head;
    while (current != NULL) {
        if (current->song.title == title) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

bool SongList::isHashExist(std::string title) {
    Song localSong = {0, title, "0", "0"};
    calculateHash(&localSong, false);
    SongNode* current = head;
    while (current != NULL) {
        if (localSong.merkleTree.verifyHash(current->song.hash)) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void SongList::sortSongs(bool ascending) {
    if (size <= 1) {
        return;
    }
    SongNode* current = head;
    SongNode* next = current->next;
    SongNode* prev = NULL;
    SongNode* temp = NULL;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        current = head;
        next = current->next;
        while (next != NULL) {
            if (ascending) {
                if (current->song.songId > next->song.songId) {
                    if (prev == NULL) {
                        head = next;
                    } else {
                        prev->next = next;
                    }
                    current->next = next->next;
                    next->next = current;
                    temp = current;
                    current = next;
                    next = temp;
                    swapped = true;
                }
            } else {
                if (current->song.songId < next->song.songId) {
                    if (prev == NULL) {
                        head = next;
                    } else {
                        prev->next = next;
                    }
                    current->next = next->next;
                    next->next = current;
                    temp = current;
                    current = next;
                    next = temp;
                    swapped = true;
                }
            }
            prev = current;
            current = current->next;
            next = current->next;
        }
    }
    SongNode* last = head;
    while (last->next != NULL) {
        last = last->next;
    }
    tail = last;
}

SongNode* SongList::getSongNode(int songId) {
    SongNode* current = head;
    while (current != NULL) {
        if (current->song.songId == songId) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Song* SongList::getSong(int songId) {
    SongNode* songNode = getSongNode(songId);
    if (songNode != NULL) {
        return &songNode->song;
    }
    return NULL;
}

int SongList::getSize() {
    return size;
}

SongNode* SongList::getHead() {
    return head;
}

void SongList::playingSong(std::string& title) {
    SongNode* current = head;
    while (current != NULL) {
        if (current->song.title == title) {
            playSong(current->song);
            return;
        }
        current = current->next;
    }
}

void calculateHash(Song* song, bool isCloud) {
    song->merkleTree.hashFileBlock(song->title, isCloud);
    song->merkleTree.buildTree();
    song->merkleTree.calculateHash(&(song->merkleTree.root));
    song->hash = song->merkleTree.getRootHash();
}

void playSong(const Song& song) {
    std::cout << "Playing " << song.title << " by " << song.artist << std::endl;
    std::string FileName = "SimulatedCloud/Song/" + song.title + ".wav";
    PlaySound(FileName.c_str(), NULL, SND_FILENAME | SND_ASYNC);

    std::cout << "Lagu sedang dimainkan..." << std::endl;
    std::cout << "Klik Enter untuk menghentikan lagu..." << std::endl;

    // Loop untuk mendeteksi input keyboard
    while(true) {
        if (kbhit()) {  // Jika ada input keyboard
            int ch = getch();
            if (ch == 13) {  // 13 adalah kode ASCII untuk Enter
                PlaySound(NULL, NULL, 0);  // Hentikan lagu
                break;
            }
        }
        // Tambahkan delay kecil untuk mengurangi penggunaan CPU
        Sleep(100);  // Delay 100ms, atau sesuaikan sesuai kebutuhan
    }

    std::cout << "Lagu selesai." << std::endl;
}

void downloadSong(std::string songName) {
    // verify hash before download
    Song realSong = _SongList.searchSong(songName)->song;
    Song cloudSong = realSong;
    cloudSong.hash = "0";
    calculateHash(&cloudSong, true);
    if (realSong.hash != cloudSong.hash) {
        std::cout << "Lagu tidak valid. Tidak dapat diunduh." << std::endl;
        return;
    }

    std::ifstream src("SimulatedCloud/Song/" + songName + ".wav", std::ios::binary);
    std::ofstream dst("MyDownload/" + songName + ".wav", std::ios::binary);

    dst << src.rdbuf();

    if (src && dst)
        std::cout << "Lagu berhasil diunduh" << std::endl;
    else
        std::cerr << "Lagu tidak ditemukan" << std::endl;
}

void uploadSong(std::string songName) {
    std::ifstream src("MyFolder/Song/" + songName + ".wav", std::ios::binary);
    std::ofstream dst("SimulatedCloud/Song/" + songName + ".wav", std::ios::binary);

    dst << src.rdbuf();

    if (src && dst)
        std::cout << "Lagu berhasil diunggah" << std::endl;
    else
        std::cerr << "Lagu tidak ditemukan" << std::endl;;
}

// void saveMerkleNode(std::ofstream& file, MerkleNode* node) {
//     if (node) {
//         file << node->hash << " ";
//         saveMerkleNode(file, node->left);
//         saveMerkleNode(file, node->right);
//     } else {
//         file << "null ";
//     }
// }

// void saveMerkleTree(std::ofstream& file, const MerkleTree& tree) {
//     saveMerkleNode(file, tree.root);
// }

// void SongList::saveSongListToFile(SongList& songList, const std::string& filename) {
//     std::ofstream file(filename);
//     SongNode* current = songList.getHead();
//     while (current != nullptr) {
//         file << current->song.songId << "|" << current->song.title << "|" << current->song.artist << "|" << current->song.hash << "|";
//         saveMerkleTree(file, current->song.merkleTree);
//         file << "\n";
//         current = current->next;
//     }
//     file.close();
// }

void SongList::saveSongsToFile() {
    std::string filename = "assets/songs.txt";
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Gagal membuka file " << filename << std::endl;
        return;
    }

    SongNode* current = getHead();
    while (current != nullptr) {
        file << current->song.songId << "|" << current->song.title << "|" << current->song.artist << "|" << current->song.hash << "\n";
        current = current->next;
    }

    file.close();
}


void SongList::loadSongsFromFile() {
    std::string filename = "assets/songs.txt";
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Gagal membuka file " << filename << std::endl;
        return;
    }

    // Menghapus semua node yang sudah ada dalam SongList
    SongNode* current = head;
    while (current != nullptr) {
        SongNode* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (std::getline(iss, token, '|')) {
            tokens.push_back(token);
        }
        if (tokens.size() >= 4) {
            Song song;
            song.songId = std::stoi(tokens[0]);
            song.title = tokens[1];
            song.artist = tokens[2];
            song.hash = tokens[3];
            addSong(song);
        }
    }

    file.close();
}