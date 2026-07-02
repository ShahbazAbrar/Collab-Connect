#ifndef INFLUENCERTREE_H
#define INFLUENCERTREE_H

#include <QString>
#include <QVector>

// Influencer node structure for BST
struct Influencer {
    int id;
    QString name;
    QString niche;
    int followers;
    float engagementRate;
    QString email;
    QString password; // Added password field
    Influencer* left;
    Influencer* right;
    
    // Constructor
    Influencer(int i, QString n, QString nic, int f, float e, QString em = "", QString p = "")
        : id(i), name(n), niche(nic), followers(f), engagementRate(e), 
          email(em), password(p), left(nullptr), right(nullptr) {}
};

// Binary Search Tree for managing influencers sorted by follower count
class InfluencerTree {
private:
    Influencer* root;
    
    // Helper functions for recursive operations
    void insertHelper(Influencer*& node, Influencer* newInf);
    void inorderHelper(Influencer* node, QVector<Influencer*>& results);
    void searchRangeHelper(Influencer* node, int min, int max, QVector<Influencer*>& results);
    void destroyTree(Influencer* node);
    Influencer* searchByIdHelper(Influencer* node, int id);
    
public:
    InfluencerTree();
    
    // Insert new influencer sorted by followers
    void insert(int id, QString name, QString niche, int followers, float engagement, QString email, QString password);
    
    // Search operations
    QVector<Influencer*> searchByRange(int minFollowers, int maxFollowers);
    QVector<Influencer*> searchByNiche(QString niche);
    QVector<Influencer*> getAllInfluencers();
    Influencer* searchById(int id);
    
    // Utility
    bool isEmpty();
    void clear();
    
    ~InfluencerTree();
};

#endif // INFLUENCERTREE_H
