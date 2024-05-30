#include "MerkleTree.h"

// Metode konstruktor
MerkleTree::MerkleTree()
{
    root = NULL;
}

// Metode destruktor
MerkleTree::~MerkleTree(){
    delete root;
}

// Metode untuk menambahkan leaf ke dalam tree
void MerkleTree::addLeaf(std::string hash)
{
    MerkleNode* newLeaf = new MerkleNode();
    newLeaf->hash = hash;
    leaves.push_back(newLeaf);
}

// Metode untuk melakukan hashing pada setiap blok data file
void MerkleTree::hashFileBlock(std::string file_path)
{
    // Buka file dalam mode biner
    std::ifstream file(file_path, std::ios::binary);
    if (!file)
    {
        std::cerr << "File tidak dapat dibuka!" << std::endl;
        return;
    }

    // Baca isi file ke dalam buffer
    std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // Ukuran blok yang diinginkan (misalnya 512 byte)
    const size_t block_size = 512;
    size_t total_blocks = (buffer.size() + block_size - 1) / block_size;

    // Hash setiap blok
    for (size_t i = 0; i < total_blocks; ++i)
    {
        size_t start = i * block_size;
        size_t end = std::min(start + block_size, buffer.size());
        size_t length = end - start;
        std::string hash = sha256(buffer.data() + start, length);
        addLeaf(hash);
        // cout << "Block " << i + 1 << " hash: " << hash << endl;
    }
};

// Metode untuk membangun tree dari daftar leaf
MerkleNode* MerkleTree::buildTree() {
    if (leaves.empty()) return NULL;

    std::vector<MerkleNode*> level;
    for (const auto& leaf : leaves) {
        MerkleNode* node = new MerkleNode();
        node->hash = leaf->hash;
        level.push_back(node);
    }

    while (level.size() > 1) {
        std::vector<MerkleNode*> nextLevel;
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
    return NULL;
}

// Metode untuk menghitung hash pada setiap node
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

// Metode untuk mengembalikan hash pada root node
std::string MerkleTree::getRootHash() {
    return root->hash;;
}

// Metode untuk memverifikasi hash
bool MerkleTree::verifyHash(std::string hash, std::string proof) {
    return (hash == proof);
}
