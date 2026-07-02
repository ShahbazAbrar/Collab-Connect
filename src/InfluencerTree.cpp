#include "include/InfluencerTree.h"

// Constructor
InfluencerTree::InfluencerTree() : root(nullptr) {}

// Destructor - clean up all nodes
InfluencerTree::~InfluencerTree() {
    destroyTree(root);
}

// Recursive helper to destroy tree
void InfluencerTree::destroyTree(Influencer* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Insert influencer into BST sorted by followers
void InfluencerTree::insert(int id, QString name, QString niche, int followers, float engagement, QString email, QString password) {
    Influencer* newInf = new Influencer(id, name, niche, followers, engagement, email, password);
    insertHelper(root, newInf);
}

// Recursive helper for insertion
void InfluencerTree::insertHelper(Influencer*& node, Influencer* newInf) {
    if (node == nullptr) {
        node = newInf;
    } else if (newInf->followers < node->followers) {
        insertHelper(node->left, newInf);
    } else {
        insertHelper(node->right, newInf);
    }
}

// Search influencers by follower range
QVector<Influencer*> InfluencerTree::searchByRange(int min, int max) {
    QVector<Influencer*> results;
    searchRangeHelper(root, min, max, results);
    return results;
}

// Recursive helper for range search
void InfluencerTree::searchRangeHelper(Influencer* node, int min, int max, QVector<Influencer*>& results) {
    if (node == nullptr) return;
    
    // If current node's followers are greater than min, search left subtree
    if (node->followers > min) {
        searchRangeHelper(node->left, min, max, results);
    }
    
    // If current node is in range, add to results
    if (node->followers >= min && node->followers <= max) {
        results.append(node);
    }
    
    // If current node's followers are less than max, search right subtree
    if (node->followers < max) {
        searchRangeHelper(node->right, min, max, results);
    }
}

// Search influencers by niche
QVector<Influencer*> InfluencerTree::searchByNiche(QString niche) {
    QVector<Influencer*> allInfluencers = getAllInfluencers();
    QVector<Influencer*> results;
    
    for (Influencer* inf : allInfluencers) {
        if (inf->niche == niche) {
            results.append(inf);
        }
    }
    
    return results;
}

// Get all influencers sorted by followers (inorder traversal)
QVector<Influencer*> InfluencerTree::getAllInfluencers() {
    QVector<Influencer*> results;
    inorderHelper(root, results);
    return results;
}

// Recursive inorder traversal helper
void InfluencerTree::inorderHelper(Influencer* node, QVector<Influencer*>& results) {
    if (node != nullptr) {
        inorderHelper(node->left, results);
        results.append(node);
        inorderHelper(node->right, results);
    }
}

// Search influencer by ID
Influencer* InfluencerTree::searchById(int id) {
    return searchByIdHelper(root, id);
}

// Recursive helper for ID search
Influencer* InfluencerTree::searchByIdHelper(Influencer* node, int id) {
    if (node == nullptr) return nullptr;
    
    if (node->id == id) {
        return node;
    }
    
    // Search both subtrees since BST is sorted by followers, not ID
    Influencer* leftResult = searchByIdHelper(node->left, id);
    if (leftResult != nullptr) return leftResult;
    
    return searchByIdHelper(node->right, id);
}

// Check if tree is empty
bool InfluencerTree::isEmpty() {
    return root == nullptr;
}

void InfluencerTree::clear() {
    destroyTree(root);
    root = nullptr;
}
