#include "InfluencerDashboard.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QScrollArea>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QVariant>
#include <QDate>

InfluencerDashboard::InfluencerDashboard(SystemManager *manager, QWidget *parent) 
    : QWidget(parent), systemManager(manager) 
{
    setupUI();
    applyStyles();
    updateOfferDisplay();
}

void InfluencerDashboard::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // --- Header Bar ---
    QWidget *header = new QWidget();
    header->setObjectName("headerBar");
    header->setFixedHeight(70);
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(24, 0, 24, 0);

    QLabel *logo = new QLabel("✨ Collab Connect | Influencer");
    logo->setObjectName("headerLogo");

    QPushButton *logoutBtn = new QPushButton("Logout");
    logoutBtn->setObjectName("logoutBtn");
    logoutBtn->setCursor(Qt::PointingHandCursor);

    headerLayout->addWidget(logo);
    headerLayout->addStretch();
    
    QPushButton *refreshBtn = new QPushButton("🔄 Refresh");
    refreshBtn->setStyleSheet("background-color: #3b82f6; color: white; border: 1px solid white; padding: 8px 16px; border-radius: 8px; font-weight: bold; margin-right: 10px;");
    refreshBtn->setCursor(Qt::PointingHandCursor);
    headerLayout->addWidget(refreshBtn);
    
    headerLayout->addWidget(logoutBtn);
    connect(logoutBtn, &QPushButton::clicked, this, &InfluencerDashboard::logoutClicked);
    connect(refreshBtn, &QPushButton::clicked, this, [this](){
        updateOfferDisplay();
        refreshTasks();
    });

    // --- Main Tabs Container ---
    QTabWidget *tabs = new QTabWidget();
    tabs->setObjectName("mainTabs");

    // --- TAB 1: Collaboration Offers ---
    QWidget *offersTab = new QWidget();
    QVBoxLayout *offerLayout = new QVBoxLayout(offersTab);
    offerLayout->setContentsMargins(40, 40, 40, 40);

    QLabel *tabTitle = new QLabel("Incoming Collaboration Offers");
    tabTitle->setStyleSheet("font-size: 24px; font-weight: bold; color: #1e293b; margin-bottom: 5px;");
    queueStatusLabel = new QLabel("Loading offers...");
    queueStatusLabel->setStyleSheet("color: #64748b; font-size: 14px; margin-bottom: 20px;");

    // Scroll Area for Offers
    QScrollArea *offersScroll = new QScrollArea();
    offersScroll->setWidgetResizable(true);
    offersScroll->setFrameShape(QFrame::NoFrame);
    offersScroll->setStyleSheet("background: transparent;");

    QWidget *offersContainer = new QWidget();
    offersContainer->setStyleSheet("background: transparent;");
    offersListLayout = new QVBoxLayout(offersContainer);
    offersListLayout->setSpacing(20);
    offersListLayout->setContentsMargins(0, 0, 20, 0);
    
    offersScroll->setWidget(offersContainer);

    offerLayout->addWidget(tabTitle);
    offerLayout->addWidget(queueStatusLabel);
    offerLayout->addWidget(offersScroll);

    // --- TAB 2: Campaign Tasks ---
    QWidget *tasksTab = new QWidget();
    QVBoxLayout *tasksMainLayout = new QVBoxLayout(tasksTab);
    tasksMainLayout->setContentsMargins(40, 40, 40, 40);

    QLabel *tasksTitle = new QLabel("Current Campaign Tasks");
    tasksTitle->setStyleSheet("font-size: 26px; font-weight: 800; color: #0f172a;");

    QLabel *dynamicSubtitle = new QLabel("0 active tasks");
    dynamicSubtitle->setObjectName("dynamicTaskSubtitle");
    dynamicSubtitle->setStyleSheet("color: #64748b; font-size: 14px; margin-bottom: 20px;");

    tasksMainLayout->addWidget(tasksTitle);
    tasksMainLayout->addWidget(dynamicSubtitle);

    QScrollArea *taskScroll = new QScrollArea();
    taskScroll->setWidgetResizable(true);
    taskScroll->setFrameShape(QFrame::NoFrame);
    taskScroll->setStyleSheet("background: transparent;");

    QWidget *taskContainer = new QWidget();
    taskContainer->setStyleSheet("background: transparent;");
    taskItemsLayout = new QVBoxLayout(taskContainer); 
    taskItemsLayout->setSpacing(15);
    taskItemsLayout->setContentsMargins(0, 0, 20, 0);
    
    taskScroll->setWidget(taskContainer);
    tasksMainLayout->addWidget(taskScroll);

    // --- TAB 3: Activity Log ---
    QWidget *logsTab = new QWidget();
    QVBoxLayout *logsLayout = new QVBoxLayout(logsTab);
    logsLayout->setContentsMargins(40, 40, 40, 40);

    QScrollArea *scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    QWidget *logContent = new QWidget();
    logContent->setStyleSheet("background: transparent;");
    logListLayout = new QVBoxLayout(logContent);
    logListLayout->setSpacing(10);

    scroll->setWidget(logContent);
    logsLayout->addWidget(scroll);

    // Assemble Tabs
    tabs->addTab(offersTab, "1. Collaboration Offers");
    tabs->addTab(tasksTab, "2. Campaign Tasks");
    tabs->addTab(logsTab, "3. Activity Log");

    mainLayout->addWidget(header);
    mainLayout->addWidget(tabs);
    
    updateTaskCounter();
    refreshTasks();
    refreshLogs();
}

void InfluencerDashboard::updateOfferDisplay() {
    // Clear current list
    QLayoutItem *child;
    while ((child = offersListLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    QVector<QString> requestStrings = systemManager->getAllPendingRequests();
    int myCount = 0;

    for (const QString &req : requestStrings) {
        // Parse basic checks first
        if (!req.contains(currentInfluencerName, Qt::CaseInsensitive)) continue;

        myCount++;

        // Fetch Campaign Details
        double budget = 0.0;
        QString dateStr = "Unknown Date";
        Campaign* camp = systemManager->getCampaign(req.mid(req.indexOf("(Campaign ID: ") + 14).toInt()); // Try to parse ID from string if possible, OR rely on our precise parsing
        
        // Robust ID parsing from earlier logic
        int idStart = req.indexOf("#") + 1;
        int idEnd = req.indexOf(":");
        int reqId = req.mid(idStart, idEnd - idStart).toInt();
        
        // Restore parsing of brand and campaign name
        int startBrand = req.indexOf(": ") + 2;
        int endBrand = req.indexOf(" wants");
        QString brand = req.mid(startBrand, endBrand - startBrand);

        int startCamp = req.indexOf("'") + 1;
        int endCamp = req.lastIndexOf("'");
        QString campaignName = req.mid(startCamp, endCamp - startCamp);
        
        // Find campaign ID from the request string if possible, or query system
        // The request string format in RequestQueue.cpp:
        // "#" + QString::number(current->requestId) + ": " + current->brandName + " wants " + current->influencerName + " for '" + current->campaignName + "' (Campaign ID: " + QString::number(current->campaignId) + ")\nTime: " + current->timestamp.toString();
        
        int cIdStart = req.indexOf("(Campaign ID: ") + 14;
        int cIdEnd = req.indexOf(")", cIdStart);
        int campaignId = req.mid(cIdStart, cIdEnd - cIdStart).toInt();
        
        if (campaignId > 0) {
            Campaign* c = systemManager->getCampaign(campaignId);
            if (c) {
                budget = c->budget;
                dateStr = c->createdDate.toString("MMM d, yyyy");
            }
        }
        
        int timeStart = req.indexOf("Time: ") + 6;
        QString requestTime = req.mid(timeStart).trimmed();

        // --- Create Redesigned UI Card ---
        QFrame *card = new QFrame();
        card->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        card->setStyleSheet(R"(
            QFrame {
                background-color: white;
                border: 1px solid #e2e8f0;
                border-radius: 16px;
                padding: 0px;
            }
            QFrame:hover {
                border: 1px solid #3b82f6;
                background-color: #f8fafc;
            }
        )");
        
        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        cardLayout->setSpacing(0);
        cardLayout->setContentsMargins(24, 24, 24, 24);
        
        // Top Row: Brand + Status
        QHBoxLayout *topRow = new QHBoxLayout();
        QLabel *brandLabel = new QLabel(brand);
        brandLabel->setStyleSheet("font-size: 20px; font-weight: 800; color: #0f172a; border: none; background: transparent;");
        
        QLabel *statusBadge = new QLabel("Pending Offer");
        statusBadge->setStyleSheet(R"(
            background-color: #fff7ed; 
            color: #d97706; 
            border: 1px solid #ffedd5;
            padding: 6px 12px; 
            border-radius: 20px; 
            font-size: 12px; 
            font-weight: 700;
        )");
        
        topRow->addWidget(brandLabel);
        topRow->addStretch();
        topRow->addWidget(statusBadge);
        
        // Middle Row: Campaign Details
        QWidget *detailsContainer = new QWidget();
        detailsContainer->setStyleSheet("background: transparent; border: none;");
        QVBoxLayout *detailsLayout = new QVBoxLayout(detailsContainer);
        detailsLayout->setContentsMargins(0, 16, 0, 16);
        detailsLayout->setSpacing(8);
        
        QLabel *campName = new QLabel(campaignName);
        campName->setStyleSheet("font-size: 16px; font-weight: 600; color: #334155; border: none;");
        
        // Info Row (Budget | Date)
        QHBoxLayout *infoRow = new QHBoxLayout();
        
        auto createIconLabel = [](QString icon, QString text) -> QWidget* {
            QWidget *w = new QWidget();
            w->setStyleSheet("background: transparent; border: none;");
            QHBoxLayout *l = new QHBoxLayout(w);
            l->setContentsMargins(0,0,0,0);
            l->setSpacing(6);
            QLabel *i = new QLabel(icon);
            i->setStyleSheet("font-size: 14px;");
            QLabel *t = new QLabel(text);
            t->setStyleSheet("color: #64748b; font-size: 13px; font-weight: 500;");
            l->addWidget(i);
            l->addWidget(t);
            l->addStretch();
            return w;
        };
        
        infoRow->addWidget(createIconLabel("💰", QString("Budget: $%1").arg(budget)));
        infoRow->addWidget(createIconLabel("📅", "Req: " + requestTime));
        infoRow->addStretch();
        
        detailsLayout->addWidget(campName);
        detailsLayout->addLayout(infoRow);
        
        // Bottom Row: Actions
        QHBoxLayout *actionRow = new QHBoxLayout();
        actionRow->setSpacing(12);
        
        QPushButton *acceptBtn = new QPushButton("Accept Offer");
        acceptBtn->setCursor(Qt::PointingHandCursor);
        acceptBtn->setFixedHeight(40);
        acceptBtn->setStyleSheet(R"(
            QPushButton {
                background-color: #22c55e; 
                color: white; 
                border-radius: 8px; 
                font-weight: 600;
                border: none;
                padding: 0 20px;
            }
            QPushButton:hover { background-color: #16a34a; }
            QPushButton:pressed { background-color: #15803d; }
        )");
        
        QPushButton *rejectBtn = new QPushButton("Reject");
        rejectBtn->setCursor(Qt::PointingHandCursor);
        rejectBtn->setFixedHeight(40);
        rejectBtn->setStyleSheet(R"(
            QPushButton {
                background-color: white; 
                color: #ef4444; 
                border: 1px solid #fecaca; 
                border-radius: 8px; 
                font-weight: 600;
                padding: 0 20px;
            }
            QPushButton:hover { background-color: #fef2f2; border-color: #ef4444; }
        )");
        
        actionRow->addStretch();
        actionRow->addWidget(rejectBtn);
        actionRow->addWidget(acceptBtn);
        
        // Assemble Card
        cardLayout->addLayout(topRow);
        cardLayout->addWidget(detailsContainer);
        cardLayout->addLayout(actionRow);
        
        offersListLayout->addWidget(card);
        
        // Connect buttons
        connect(acceptBtn, &QPushButton::clicked, [this, reqId, brand]() {
            if(systemManager->acceptRequest(reqId)) {
                systemManager->addNotification("Accepted offer from " + brand, "influencer", "REQUEST", currentInfluencerName);
                systemManager->addNotification("Collaboration request accepted by " + currentInfluencerName, "brand", "REQUEST", "ALL"); 
                updateOfferDisplay();
                refreshTasks();
            }
        });
        
        connect(rejectBtn, &QPushButton::clicked, [this, reqId]() {
            if(systemManager->rejectRequest(reqId)) {
                updateOfferDisplay();
            }
        });
    }

    // Crucial: Add stretch to push items to the top and prevent stretching
    offersListLayout->addStretch();

    queueStatusLabel->setText(QString("You have %1 pending offers").arg(myCount));
    
    if (myCount == 0) {
        QLabel *empty = new QLabel("No pending offers at the moment.");
        empty->setAlignment(Qt::AlignCenter);
        empty->setStyleSheet("color: #94a3b8; font-size: 16px; margin-top: 40px;");
        offersListLayout->addWidget(empty);
    }
}

// Remove old onAccept/Reject slots as they are replaced by lambdas
void InfluencerDashboard::onAcceptClicked() {} 
void InfluencerDashboard::onRejectClicked() {}

void InfluencerDashboard::applyStyles() {
    this->setStyleSheet(R"(
        InfluencerDashboard { background-color: #f8fafc; }
        #headerBar { background-color: #2563eb; }
        #headerLogo { color: white; font-size: 20px; font-weight: bold; }
        #logoutBtn {
            background-color: #ef4444; color: white; border: none;
            padding: 8px 16px; border-radius: 8px; font-weight: bold;
        }
        #logoutBtn:hover { background-color: #dc2626; }
        QTabWidget::pane { border: none; background: #f8fafc; }
        QTabBar::tab {
            background: white; color: #64748b; padding: 12px 25px;
            margin-right: 10px; border-radius: 10px; border: 1px solid #e2e8f0;
            font-weight: 600; font-size: 13px;
        }
        QTabBar::tab:selected { background: #2563eb; color: white; border: none; }
        #offerCard { background-color: white; border: 1px solid #e2e8f0; border-radius: 20px; }
        #brandLabel { font-size: 28px; font-weight: bold; color: #1e293b; }
        #amountLabel {
            font-size: 18px; font-weight: bold; color: white;
            background-color: #22c55e; padding: 8px 20px; border-radius: 20px;
        }
        #descriptionLabel { font-size: 17px; color: #475569; line-height: 1.6; }
        #acceptBtn { background-color: #22c55e; color: white; border-radius: 12px; font-weight: bold; font-size: 15px; }
        #rejectBtn { background-color: #ef4444; color: white; border-radius: 12px; font-weight: bold; font-size: 15px; }
    )");
}

void InfluencerDashboard::setCurrentInfluencer(QString name) {
    currentInfluencerName = name;
    updateOfferDisplay();
    refreshTasks();
    refreshLogs();
}

void InfluencerDashboard::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    updateOfferDisplay();
    refreshTasks();
    refreshLogs();
}

void InfluencerDashboard::updateTaskCounter() {
    QLabel* sub = this->findChild<QLabel*>("dynamicTaskSubtitle");
    if (!sub) return;

    int activeCount = 0;
    QList<QProgressBar*> pbs = this->findChildren<QProgressBar*>();
    for(QProgressBar* pb : pbs) {
        if(pb->property("isTask").toBool() && pb->value() < 100) {
            activeCount++;
        }
    }
    sub->setText(QString("%1 active tasks").arg(activeCount));
}

void InfluencerDashboard::refreshTasks() {
    // Clear existing tasks
    QLayoutItem *child;
    while ((child = taskItemsLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Helper to add visual task
    auto addTask = [&](int cId, int tId, QString name, QString brand, int progress, bool completed) {
        QFrame *f = new QFrame();
        f->setObjectName("taskCard");
        
        auto applyVisuals = [f](bool isDone) {
             f->setStyleSheet(isDone ?
                 "QFrame#taskCard { background-color: #f0fdf4; border: 1px solid #22c55e; border-radius: 15px; padding: 20px; }" :
                 "QFrame#taskCard { background-color: white; border: 1px solid #e2e8f0; border-radius: 15px; padding: 20px; }");
        };
        applyVisuals(completed);

        QVBoxLayout *l = new QVBoxLayout(f);
        QHBoxLayout *h = new QHBoxLayout();
        QLabel *check = new QLabel(completed ? "✅" : "⭕");
        QLabel *title = new QLabel(name);
        title->setStyleSheet("font-weight: 700; color: #1e293b; font-size: 16px;");
        QLabel *bTag = new QLabel(brand);
        bTag->setStyleSheet("background-color: #f1f5f9; padding: 4px 8px; border-radius: 8px; font-size: 10px; font-weight: bold; color: #475569;");
        
        h->addWidget(check);
        h->addWidget(title);
        h->addStretch();
        h->addWidget(bTag);
        
        QHBoxLayout *act = new QHBoxLayout();
        QProgressBar *pb = new QProgressBar();
        pb->setProperty("isTask", true);
        pb->setValue(progress);
        pb->setFixedHeight(10);
        
        QPushButton *actionBtn = new QPushButton(completed ? "Completed" : "Mark Done");
        if(completed) {
            actionBtn->setEnabled(false);
            actionBtn->setStyleSheet("background-color: #cbd5e1; color: white; border: none; border-radius: 6px; padding: 6px 12px;");
        } else {
            actionBtn->setCursor(Qt::PointingHandCursor);
            actionBtn->setStyleSheet("background-color: #2563eb; color: white; border: none; border-radius: 6px; padding: 6px 12px; font-weight: bold;");
            
            connect(actionBtn, &QPushButton::clicked, [this, cId, tId, name, brand]() { // Capture name and brand
                // Logic to mark task complete in backend
                if(systemManager->markTaskComplete(cId, tId)) {
                   systemManager->addNotification("Task completed: " + name, "influencer", "TASK", currentInfluencerName);
                   systemManager->addNotification(currentInfluencerName + " completed task: " + name, "brand", "TASK", "ALL"); // Notify brand
                   
                   refreshTasks();
                   updateTaskCounter();
                   refreshLogs();
                }
            });
        }
        act->addWidget(pb);
        act->addWidget(actionBtn); // Replaced markBtn with actionBtn
        
        l->addLayout(h);
        l->addLayout(act);
        taskItemsLayout->addWidget(f);
    };

    QVector<Campaign*> campaigns = systemManager->getInfluencerCampaigns(currentInfluencerName);
    
    // Collect all tasks first
    struct TaskInfo { int cId; int tId; QString n; QString b; int p; bool done; };
    QVector<TaskInfo> pendingTasks;
    QVector<TaskInfo> completedTasks;

    for(Campaign* camp : campaigns) {
        QVector<QString> taskStrings = camp->tasks->getAllTasksAsStrings();
         for(QString tStr : taskStrings) {
            bool isCompleted = tStr.contains("[✓]");
            int progress = isCompleted ? 100 : 0;
            
            int taskIdStart = tStr.indexOf("Task ") + 5;
            int taskIdEnd = tStr.indexOf(":", taskIdStart);
            int taskId = 0;
            if (taskIdStart != -1 && taskIdEnd != -1) taskId = tStr.mid(taskIdStart, taskIdEnd - taskIdStart).toInt();
            
            QString desc = tStr.mid(tStr.indexOf(": ") + 2);
            // Remove deadline if exists in desc parsing
            int dueIndex = desc.lastIndexOf(" (Due:");
            if(dueIndex != -1) desc = desc.left(dueIndex);

            TaskInfo info = {camp->campaignId, taskId, desc, camp->brandName, progress, isCompleted};
            if(isCompleted) completedTasks.append(info);
            else pendingTasks.append(info);
         }
    }

    if(pendingTasks.isEmpty() && completedTasks.isEmpty()) {
        QLabel* empty = new QLabel("No active campaigns or tasks.");
        empty->setStyleSheet("color: #94a3b8; font-style: italic; margin-top: 20px;");
        empty->setAlignment(Qt::AlignCenter);
        taskItemsLayout->addWidget(empty);
    } else {
        // Pending Section
        if(!pendingTasks.isEmpty()) {
            QLabel* pHeader = new QLabel("📝 Pending Tasks");
            pHeader->setStyleSheet("font-size: 18px; font-weight: bold; color: #475569; margin-top: 10px; margin-bottom: 10px;");
            taskItemsLayout->addWidget(pHeader);
            for(const auto& t : pendingTasks) addTask(t.cId, t.tId, t.n, t.b, t.p, t.done);
        }

        // Completed Section
        if(!completedTasks.isEmpty()) {
            QLabel* cHeader = new QLabel("✅ Completed Tasks");
            cHeader->setStyleSheet("font-size: 18px; font-weight: bold; color: #166534; margin-top: 30px; margin-bottom: 10px;");
            taskItemsLayout->addWidget(cHeader);
            for(const auto& t : completedTasks) addTask(t.cId, t.tId, t.n, t.b, t.p, t.done);
        }
    }
    
    taskItemsLayout->addStretch();
    updateTaskCounter();
}

void InfluencerDashboard::refreshLogs() {
    // Clear existing logs
    QLayoutItem *child;
    while ((child = logListLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    auto addLog = [&](QString icon, QString msg, QString date) {
        QFrame *item = new QFrame();
        // Fixed height to prevent stretching
        item->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        item->setStyleSheet("background: white; border: 1px solid #f1f5f9; border-radius: 12px; padding: 15px;");
        QHBoxLayout *l = new QHBoxLayout(item);
        QLabel *i = new QLabel(icon);
        i->setFixedSize(40, 40);
        i->setAlignment(Qt::AlignCenter);
        i->setStyleSheet("background: #f8fafc; border-radius: 20px; font-size: 18px;");

        QVBoxLayout *txt = new QVBoxLayout();
        QLabel *m = new QLabel(msg);
        m->setStyleSheet("font-weight: 500; color: #334155;");
        QLabel *d = new QLabel(date);
        d->setStyleSheet("color: #94a3b8; font-size: 11px; font-weight: bold;");
        txt->addWidget(m);
        txt->addWidget(d);

        l->addWidget(i);
        l->addLayout(txt);
        logListLayout->addWidget(item);
    };

    QVector<QString> notifications = systemManager->getNotifications("influencer", currentInfluencerName);
    if (notifications.isEmpty()) {
        addLog("ℹ️", "No new notifications", QDate::currentDate().toString());
    } else {
        for(QString notif : notifications) {
            QStringList parts = notif.split("\n");
            QString content = parts.first();
            QString dateStr = (parts.size() > 1) ? parts[1] : "";
            
            QString icon = "📢";
            if (content.contains("[REQUEST]")) icon = "💼";
            else if (content.contains("[TASK]")) icon = "✅";
            else if (content.contains("[CAMPAIGN]")) icon = "🚀";
            
            addLog(icon, content, dateStr);
        }
    }
    
    // Crucial stretch to fix layout
    logListLayout->addStretch();
}
