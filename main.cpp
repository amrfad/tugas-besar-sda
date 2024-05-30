#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Song.h"

// using namespace std;
int main()
{
    Song song1;
    song1.merkleTree.hashFileBlock("Song/Sunny.mp3");
    song1.merkleTree.buildTree();
    song1.merkleTree.calculateHash(song1.merkleTree.root);
    std::cout << "Root Hash: " << song1.merkleTree.getRootHash() << std::endl;
    std::cout << "Verify Hash: " << song1.merkleTree.verifyHash(song1.merkleTree.getRootHash(), "68a487fd8957f1aeca94889e581953a6374e4e11e4c5ad83e14da9a0aa824da4") << std::endl;

    return 0;
}