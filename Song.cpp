#include "Song.h"
#include "MerkleTree.h"

SongList::SongList() {
    head = NULL;
    tail = NULL;
    size = 0;
}

SongList::~SongList() {
    SongNode* current = head;
    while (current != NULL) {
        SongNode* next = current->next;
        delete current;
        current = next;
    }
}

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

void playSong(const Song& song) {
    std::cout << "Playing " << song.title << " by " << song.artist << std::endl;
    std::string FileName = "SimulatedCloud/Song/" + song.title + ".wav";
    PlaySound(FileName.c_str(), NULL, SND_FILENAME | SND_ASYNC);
    system("pause");
}

void downloadSong(std::string songName) {
    std::ifstream src("SimulatedCloud/Song/" + songName + ".wav", std::ios::binary);
    std::ofstream dst("MyDownload/" + songName + ".wav", std::ios::binary);

    dst << src.rdbuf();

    if (src && dst)
        std::cout << "Lagu berhasil diunduh" << std::endl;
    else
        std::cerr << "Lagu tidak ditemukan" << std::endl;
}