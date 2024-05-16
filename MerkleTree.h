#ifndef MERKLE_TREE_H
#define MERKLE_TREE_H

#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>
#include "sha256.h"
using namespace std;

struct MerkleNode
{
    string hash = "";
    MerkleNode *left = NULL;
    MerkleNode *right = NULL;
};

class MerkleTree
{
public:
    MerkleNode *root;

private:
    vector<MerkleNode *> leaves;

public:
    MerkleTree();
    ~MerkleTree();
    void addLeaf(string hash);
    void hashFileBlock(string file_path);
    MerkleNode *buildTree();
    void calculateHash(MerkleNode *node);
    string getRootHash();
    bool verifyHash(string hash, string proof);
};

#endif