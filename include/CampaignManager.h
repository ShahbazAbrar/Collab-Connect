#ifndef CAMPAIGNMANAGER_H
#define CAMPAIGNMANAGER_H

#include <QString>
#include <QVector>
#include <QDateTime>
#include "CampaignTasks.h"

struct Campaign {
    int campaignId;
    QString name;
    QString brandName;
    double budget;
    QString influencerName;
    QDateTime createdDate;
    CampaignTasks* tasks;
    bool isActive;
    
    // Constructor
    Campaign(int id, QString n, QString brand, double b, QString influencer = "")
        : campaignId(id), name(n), brandName(brand), budget(b), 
          influencerName(influencer), createdDate(QDateTime::currentDateTime()), 
          tasks(new CampaignTasks()), isActive(true) {}
    
    // Destructor
    ~Campaign() {
        delete tasks;
    }
};

// Campaign Manager class
class CampaignManager {
private:
    QVector<Campaign*> campaigns;
    int campaignIdCounter;
    
public:
    CampaignManager();
    
    // Create new campaign
    int createCampaign(QString name, QString brand, double budget, QString influencer = "");
    // Load campaign with existing ID
    void loadCampaign(int id, QString name, QString brand, double budget, QString influencer, QDateTime created, bool active);
    
    // Retrieve campaigns
    Campaign* getCampaignById(int id);
    QVector<Campaign*> getCampaignsByBrand(QString brandName);
    QVector<Campaign*> getCampaignsByInfluencer(QString influencerName);
    QVector<Campaign*> getAllCampaigns();
    
    // Assign influencer to campaign
    bool assignInfluencerToCampaign(int campaignId, QString influencerName);
    
    ~CampaignManager();
};

#endif // CAMPAIGNMANAGER_H
