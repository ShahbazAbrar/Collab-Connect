#ifndef BRANDDASHBOARD_H
#define BRANDDASHBOARD_H

#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QPushButton> // Added missing include

#include "include/SystemManager.h"

class BrandDashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit BrandDashboard(SystemManager *manager, QWidget *parent = nullptr);

signals:
    void logoutClicked();

private slots:
    void handleSearch();
    void addCampaignTask();
    void handleCreateCampaign();

private:
    QWidget *createSearchInfluencersTab();
    QWidget *createCampaignCreationTab();
    QWidget *createCampaignHistoryTab();
    QWidget *createManageInfluencersTab();
    
    // UI Elements for Management
    QLineEdit *mgmtNameField;
    QLineEdit *mgmtNicheField;
    QLineEdit *mgmtFollowersField;
    QLineEdit *mgmtEngagementField;
    QLineEdit *mgmtEmailField;
    QPushButton *mgmtSaveBtn;
    QComboBox *mgmtSelectInfluencer;
    
    void handleSaveInfluencer();
    void loadInfluencerForEdit();
    // Removed duplicate declarations here

    // Search Tab
    QComboBox *nicheCombo;
    QLineEdit *followersField;
    QLineEdit *regionField;
    QListWidget *influencerResultsList;

    // Campaign Tab
    QComboBox *selectedInfluencerField; // Changed from QLineEdit
    QTextEdit *campaignDescription;
    QListWidget *taskListWidget;
    QLineEdit *newTaskField;

    // History Tab
    QListWidget *campaignHistoryList;

    SystemManager *systemManager;
};

#endif // BRANDDASHBOARD_H
