#include "MerkleTree.h"

// 
MerkleTree::MerkleTree()
{
    root = NULL;
}

// 
MerkleTree::~MerkleTree(){
    delete root;
}

// 
void MerkleTree::hashFileBlock(string file_path)
{
    // Buka file dalam mode biner
    ifstream file(file_path, ios::binary);
    if (!file)
    {
        cerr << "File tidak dapat dibuka!" << endl;
        return;
    }

    // Baca isi file ke dalam buffer
    vector<uint8_t> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // Ukuran blok yang diinginkan (misalnya 512 byte)
    const size_t block_size = 512;
    size_t total_blocks = (buffer.size() + block_size - 1) / block_size;

    // Hash setiap blok
    for (size_t i = 0; i < total_blocks; ++i)
    {
        size_t start = i * block_size;
        size_t end = min(start + block_size, buffer.size());
        size_t length = end - start;
        string hash = sha256(buffer.data() + start, length);
        MerkleNode* newLeaf = new MerkleNode();
        newLeaf->hash = hash;
        leaves.push_back(newLeaf);
        // cout << "Block " << i + 1 << " hash: " << hash << endl;
    }
};

// 
MerkleNode* MerkleTree::buildTree() {
    if (leaves.empty()) return nullptr;

    vector<MerkleNode*> level;
    for (const auto& leaf : leaves) {
        MerkleNode* node = new MerkleNode();
        node->hash = leaf->hash;
        level.push_back(node);
    }

    while (level.size() > 1) {
        vector<MerkleNode*> nextLevel;
        for (size_t i = 0; i < level.size(); i += 2) {
            MerkleNode* parent = new MerkleNode;
            parent->left = level[i];
            if (i + 1 < level.size()) {
                parent->right = level[i + 1];
            }
            nextLevel.push_back(parent);
        }
        level = nextLevel;
    }

    root = level.front();
}

// 
void MerkleTree::calculateHash(MerkleNode* node) {
    if (node == NULL) return;
    calculateHash(node->left);
    calculateHash(node->right);
    if (node->left != NULL && node->right != NULL) {
        node->hash = sha256(node->left->hash + node->right->hash);
        // cout << "Hash: " << node->hash << endl;
        // cout << "Left: " << node->left->hash << endl;
        // cout << "Right: " << node->right->hash << endl;
    }
}

//
string MerkleTree::getRootHash() {
    return root->hash;;
}

//
bool MerkleTree::verifyHash(string hash, string proof) {
    return (hash == proof);
}