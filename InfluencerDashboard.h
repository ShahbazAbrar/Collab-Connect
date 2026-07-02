#ifndef INFLUENCER_DASHBOARD_H
#define INFLUENCER_DASHBOARD_H

#include <QWidget>
#include <QQueue>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>

struct CollabRequest {
    QString brandName;
    QString date;
    QString description;
    QString amount;
};

#include "include/SystemManager.h"

class InfluencerDashboard : public QWidget {
    Q_OBJECT

public:
    explicit InfluencerDashboard(SystemManager *manager, QWidget *parent = nullptr);
    void setCurrentInfluencer(QString name);

protected:
    void showEvent(QShowEvent *event) override;

signals:
    void logoutClicked();

private slots:
    void onAcceptClicked();
    void onRejectClicked();

private:
    void setupUI();
    void updateOfferDisplay();
    void applyStyles();

    // UI Elements
    QQueue<CollabRequest> offerQueue;
    QLabel *brandLabel;
    QLabel *amountLabel;
    QLabel *descriptionLabel;
    QLabel *dateLabel;
    QLabel *queueStatusLabel;
    QFrame *offerCard;
    QVBoxLayout *offersListLayout; // Added this
    QWidget *buttonContainer;
    QWidget *emptyStateWidget;
    
    SystemManager *systemManager;
    QString currentInfluencerName = "Sarah Johnson"; // Default for demo

    // Container layout need member access for refreshing
    QVBoxLayout *taskItemsLayout;
    QVBoxLayout *logListLayout; // Added for log refreshing
    
    void refreshTasks();
    void refreshLogs(); // Added this
    void updateTaskCounter();
};

#endif // INFLUENCER_DASHBOARD_H
