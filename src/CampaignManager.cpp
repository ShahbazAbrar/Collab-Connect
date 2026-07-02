#include "include/CampaignManager.h"


CampaignManager::CampaignManager() : campaignIdCounter(0) {}

CampaignManager::~CampaignManager() {
    for (Campaign* campaign : campaigns) {
        delete campaign;
    }
    campaigns.clear();
}


int CampaignManager::createCampaign(QString name, QString brand, double budget, QString influencer) {
    campaignIdCounter++;
    Campaign* newCampaign = new Campaign(campaignIdCounter, name, brand, budget, influencer);
    campaigns.append(newCampaign);
    return campaignIdCounter;
}

void CampaignManager::loadCampaign(int id, QString name, QString brand, double budget, QString influencer, QDateTime created, bool active) {
    Campaign* newCampaign = new Campaign(id, name, brand, budget, influencer);
    newCampaign->createdDate = created;
    newCampaign->isActive = active;
    
    campaigns.append(newCampaign);
    
    
    if (id > campaignIdCounter) {
        campaignIdCounter = id;
    }
}


Campaign* CampaignManager::getCampaignById(int id) {
    for (Campaign* campaign : campaigns) {
        if (campaign->campaignId == id) {
            return campaign;
        }
    }
    return nullptr;
}

QVector<Campaign*> CampaignManager::getCampaignsByBrand(QString brandName) {
    QVector<Campaign*> results;
    
    for (Campaign* campaign : campaigns) {
        if (campaign->brandName == brandName) {
            results.append(campaign);
        }
    }
    
    return results;
}


QVector<Campaign*> CampaignManager::getCampaignsByInfluencer(QString influencerName) {
    QVector<Campaign*> results;
    
    for (Campaign* campaign : campaigns) {
        if (campaign->influencerName == influencerName) {
            results.append(campaign);
        }
    }
    
    return results;
}


QVector<Campaign*> CampaignManager::getAllCampaigns() {
    return campaigns;
}

bool CampaignManager::assignInfluencerToCampaign(int campaignId, QString influencerName) {
    Campaign* campaign = getCampaignById(campaignId);
    
    if (campaign != nullptr) {
        campaign->influencerName = influencerName;
        return true;
    }
    
    return false;
}
