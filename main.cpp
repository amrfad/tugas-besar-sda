#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Song.h"
#include "User.h"
#include "Menu.h"

// using namespace std;
int main()
{
    // Hash string "Hello, World!"
    // Song song1 = {1, }
    // std::cout << "Hash string \"Hello, World!\": " << sha256("Hello World!") << std::endl;
    // std::cout << "Hash string \"Hello, World!\": " << sha256("Hello, World") << std::endl;
    // std::cout << "Hash string \"Hello, World!\": " << sha256("Hello, Worlds") << std::endl;

    User user;
    // printLoginMenu(&user);

    _SongList.loadSongsFromFile();

    printMenu(&user);

    _SongList.saveSongsToFile();

    // Song song1;
    // song1.title = "lagutamat";
    // song1.merkleTree.hashFileBlock("SimulatedCloud/Song/Sunny.mp3");
    // song1.merkleTree.buildTree();
    // song1.merkleTree.calculateHash(song1.merkleTree.root);
    // std::cout << "Root Hash: " << song1.merkleTree.getRootHash() << std::endl;
    // std::cout << "Verify Hash: " << song1.merkleTree.verifyHash(song1.merkleTree.getRootHash(), "68a487fd8957f1aeca94889e581953a6374e4e11e4c5ad83e14da9a0aa824da4") << std::endl;
    // playSong(song1);
    // // song1.merkleTree.printBinaryTreeUI();
    // downloadSong("lagutamat");

    // Membuat beberapa objek Song
    // Song song1 = {1, "Safe and Sound", "NCS", "hash1"};
    // calculateHash(&song1, true);
    // Song song2 = {2, "Sunny", "Yorushika", "hash2"};
    // calculateHash(&song2, true);
    // Song song3 = {3, "Sway to My Beat in Cosmos", "Robin", "hash3"};
    // calculateHash(&song3, true);

    // // Membuat objek SongList dan menambahkan lagu-lagu
    // SongList songList;
    // songList.addSong(song1);
    // songList.addSong(song2);
    // songList.addSong(song3);

    // // Menyimpan SongList ke file teks
    // songList.saveSongsToFile("assets/songs.txt");
    // std::cout << "SongList telah disimpan ke file songs.txt" << std::endl;

    // // Membuat SongList baru yang kosong
    // SongList loadedSongList;

    // // Memuat SongList dari file teks
    // loadedSongList.loadSongsFromFile("songs.txt");
    // std::cout << "SongList telah dimuat dari file songs.txt" << std::endl;

    // // Mencetak lagu-lagu yang dimuat dari file
    // std::cout << "Lagu-lagu yang dimuat dari file:" << std::endl;
    // SongNode* current = loadedSongList.getHead();
    // while (current != nullptr) {
    //     std::cout << "ID: " << current->song.songId << ", Judul: " << current->song.title << ", Artis: " << current->song.artist << ", Hash: " << current->song.hash << std::endl;
    //     current = current->next;
    // }

    return 0;
}