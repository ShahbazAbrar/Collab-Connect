#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <QString>
#include <QVector>
#include "InfluencerTree.h"
#include "CampaignManager.h"
#include "RequestQueue.h"
#include "NotificationStack.h"

struct Brand {
    int id;
    QString name;
    QString email;
    QString password;
    QString niche;
};

// Central system coordinator integrating all DSA components
class SystemManager {
private:
    InfluencerTree* influencerTree;
    CampaignManager* campaignManager;
    RequestQueue* requestQueue;
    NotificationStack* brandNotifications;
    NotificationStack* influencerNotifications;
    
    QVector<Brand> brands; // Store loaded brands
    
    // Load sample data from files
    void loadSampleData();
    void loadInfluencersFromFile();
    void loadBrandsFromFile(); // New
    void loadCampaignsFromFile();
    void loadTasksFromFile();
    void loadRequestsFromFile();
    void loadNotificationsFromFile();
    
public:
    SystemManager();
    
    // Auth operations
    bool verifyBrandLogin(QString email, QString password);
    bool verifyInfluencerLogin(QString username, QString password);
    
    // Influencer operations
    void addInfluencer(int id, QString name, QString niche, int followers, float engagement, QString email = "", QString password = "pass");
    void updateInfluencer(int id, QString name, QString niche, int followers, float engagement, QString email, QString password);
    QVector<Influencer*> searchInfluencers(int minFollowers, int maxFollowers, QString niche = "All");
    QVector<Influencer*> getAllInfluencers();
    Influencer* getInfluencerById(int id);
    
    // Campaign operations
    int createCampaign(QString name, QString brand, double budget, QString influencer = "");
    void addTaskToCampaign(int campaignId, QString taskDescription, QString deadline = "");
    bool markTaskComplete(int campaignId, int taskId);
    Campaign* getCampaign(int campaignId);
    QVector<Campaign*> getBrandCampaigns(QString brandName);
    QVector<Campaign*> getInfluencerCampaigns(QString influencerName);
    QVector<Campaign*> getAllCampaigns();
    
    // Request operations
    void sendCollaborationRequest(QString brand, QString campaign, QString influencer, int campaignId = 0);
    const RequestNode* getRequestById(int requestId);
    bool acceptRequest(int requestId); // Changed to take ID
    bool rejectRequest(int requestId); // Changed to take ID
    QVector<QString> getAllPendingRequests();
    
    // Notification operations
    void addNotification(QString message, QString userType, QString category = "SYSTEM", QString recipient = "ALL");
    QVector<QString> getNotifications(QString userType, QString username);
    void clearNotifications(QString userType);
    
    // File operations
    void saveAllData();
    void saveInfluencersToFile();
    void saveBrandsToFile(); // New
    void saveCampaignsToFile();
    void saveTasksToFile(); // Added this
    void saveRequestsToFile();
    void saveNotificationsToFile();
    
    ~SystemManager();
};

#endif // SYSTEMMANAGER_H
