#ifndef MERKLE_TREE_H
#define MERKLE_TREE_H

#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>
#include <queue>
#include <stdbool.h>
#include "sha256.h"
// using namespace std;

struct MerkleNode
{
    std::string hash = "";
    MerkleNode *left = NULL;
    MerkleNode *right = NULL;
};

class MerkleTree
{
public:
    MerkleNode *root;

private:
    std::vector<MerkleNode *> leaves;

public:
    MerkleTree();
    // ~MerkleTree();
    void addLeaf(std::string hash);
    void hashFileBlock(std::string song_title, bool isCloud);
    MerkleNode *buildTree();
    void calculateHash(MerkleNode** node);
    std::string getRootHash();
    bool verifyHash(std::string proof);
    void printBinaryTreeUI();
};

#endif