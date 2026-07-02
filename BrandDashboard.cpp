// BrandDashboard.cpp

#include "BrandDashboard.h"
#include <QTabWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QDebug>
#include <QToolBar>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFont>
#include <QSpacerItem>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QScrollArea>
#include <QMessageBox>

// Define primary colors
#define PRIMARY_BLUE "#4C69BA"
#define PRIMARY_GREEN "#2ECC71"
#define PRIMARY_RED "#D32F2F"
#define LIGHT_GREY "#F5F6FA"
#define CARD_WHITE "#FFFFFF"
#define TEXT_DARK "#343A40"
#define WARNING_YELLOW "#FFC107"
#define INFO_CYAN "#17A2B8"
#define ACCENT_LIGHT_BLUE "#E8F0FE"
#define BORDER_COLOR "#E0E4E8"

// --- STYLING HELPERS ---
QString inputStyle = "QLineEdit, QComboBox, QTextEdit { "
                     "  border: 1px solid " BORDER_COLOR "; "
                     "  border-radius: 8px; "
                     "  padding: 10px 12px; "
                     "  background-color: " CARD_WHITE "; "
                     "  font-size: 14px; "
                     "  color: " TEXT_DARK "; "
                     "} "
                     "QLineEdit:focus, QComboBox:focus, QTextEdit:focus { "
                     "  border: 2px solid " PRIMARY_BLUE "; "
                     "} "
                     "QLineEdit:read-only { "
                     "  background-color: #E9ECEF; "
                     "  font-weight: bold; "
                     "}";

QString cardStyle = "QFrame#card { "
                    "  background-color: " CARD_WHITE "; "
                    "  border-radius: 12px; "
                    "  border: 1px solid " BORDER_COLOR "; "
                    "}";

BrandDashboard::BrandDashboard(SystemManager *manager, QWidget *parent) : QMainWindow(parent), systemManager(manager)
{
    setWindowTitle("Brand Dashboard - Collab Connect");
    resize(1200, 800);

    setStyleSheet("QMainWindow { background-color: " LIGHT_GREY "; }");

    // TAB WIDGET
    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->setStyleSheet(
        "QTabWidget::pane { "
        "  border: none; "
        "  background-color: " LIGHT_GREY "; "
        "} "
        "QTabBar::tab { "
        "  background: " CARD_WHITE "; "
        "  color: " TEXT_DARK "; "
        "  padding: 14px 32px; "
        "  border: 1px solid " BORDER_COLOR "; "
        "  border-bottom: none; "
        "  border-top-left-radius: 10px; "
        "  border-top-right-radius: 10px; "
        "  margin-right: 4px; "
        "  font-weight: 500; "
        "  font-size: 14px; "
        "} "
        "QTabBar::tab:selected { "
        "  background: " LIGHT_GREY "; "
        "  color: " PRIMARY_BLUE "; "
        "  font-weight: bold; "
        "  border-bottom: 3px solid " PRIMARY_BLUE "; "
        "} "
        "QTabBar::tab:hover:!selected { "
        "  background: #F0F2F5; "
        "}"
        );

    tabWidget->addTab(createSearchInfluencersTab(), "🔍 1. Search Influencers");
    tabWidget->addTab(createCampaignCreationTab(), "📝 2. Create Campaign");
    tabWidget->addTab(createCampaignHistoryTab(), "📋 3. Campaign History");
    tabWidget->addTab(createManageInfluencersTab(), "⚙️ 4. Manage Influencers");

    setCentralWidget(tabWidget);

    // TOOLBAR / HEADER
    QToolBar *toolBar = new QToolBar(this);
    toolBar->setMovable(false);
    toolBar->setStyleSheet(
        "QToolBar { "
        "  background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 " PRIMARY_BLUE ", stop:1 #6B7FD7); "
        "  border: none; "
        "  padding: 12px 20px; "
        "}"
        );

    QLabel *title = new QLabel("✨ Collab Connect", this);
    QFont titleFont("Georgia", 22);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setStyleSheet("color: white; background: transparent;");

    QPushButton *logoutBtn = new QPushButton("↪ Logout", this);
    logoutBtn->setStyleSheet(
        "QPushButton { "
        "  background-color: " PRIMARY_RED "; "
        "  color: white; "
        "  padding: 10px 24px; "
        "  border-radius: 8px; "
        "  font-weight: bold; "
        "  font-size: 14px; "
        "} "
        "QPushButton:hover { background-color: #E53E3E; }"
        );
    logoutBtn->setCursor(Qt::PointingHandCursor);

    toolBar->addWidget(title);
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    toolBar->addWidget(spacer);
    toolBar->addWidget(logoutBtn);
    addToolBar(Qt::TopToolBarArea, toolBar);

    connect(logoutBtn, &QPushButton::clicked, this, &BrandDashboard::logoutClicked);
}

// --- TAB 1: Search Influencers ---
QWidget *BrandDashboard::createSearchInfluencersTab()
{
    QWidget *tab = new QWidget();
    tab->setStyleSheet("background-color: " LIGHT_GREY ";");

    QVBoxLayout *mainLayout = new QVBoxLayout(tab);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(20);

    // Search Form Card
    QFrame *formCard = new QFrame();
    formCard->setObjectName("card");
    formCard->setStyleSheet(cardStyle + inputStyle);

    QVBoxLayout *formLayout = new QVBoxLayout(formCard);
    formLayout->setContentsMargins(25, 25, 25, 25);
    formLayout->setSpacing(20);

    // Header with icon
    QHBoxLayout *headerLayout = new QHBoxLayout();
    QLabel *iconLabel = new QLabel("🔍");
    iconLabel->setStyleSheet("font-size: 24px; background: " ACCENT_LIGHT_BLUE "; padding: 8px; border-radius: 8px;");
    QLabel *heading = new QLabel("Influencer Search Parameters");
    heading->setStyleSheet("font-size: 20px; font-weight: bold; color: " TEXT_DARK ";");
    headerLayout->addWidget(iconLabel);
    headerLayout->addWidget(heading);
    headerLayout->addStretch();
    formLayout->addLayout(headerLayout);

    // Form Grid
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setHorizontalSpacing(20);
    gridLayout->setVerticalSpacing(15);

    // Niche
    QLabel *nicheLabel = new QLabel("Niche");
    nicheLabel->setStyleSheet("font-size: 13px; font-weight: 500; color: #6B7280;");
    nicheCombo = new QComboBox();
    nicheCombo->addItems({"All", "Fitness", "Tech", "Fashion", "Gaming", "Beauty", "Vlog", "Travel", "Food", "Lifestyle"});
    nicheCombo->setFixedHeight(44);

    // Followers
    QLabel *followersLabel = new QLabel("Min. Followers");
    followersLabel->setStyleSheet("font-size: 13px; font-weight: 500; color: #6B7280;");
    followersField = new QLineEdit();
    followersField->setPlaceholderText("e.g., 10000");
    followersField->setFixedHeight(44);

    // Region
    QLabel *regionLabel = new QLabel("Region");
    regionLabel->setStyleSheet("font-size: 13px; font-weight: 500; color: #6B7280;");
    regionField = new QLineEdit();
    regionField->setPlaceholderText("e.g., North America");
    regionField->setFixedHeight(44);

    gridLayout->addWidget(nicheLabel, 0, 0);
    gridLayout->addWidget(nicheCombo, 1, 0);
    gridLayout->addWidget(followersLabel, 0, 1);
    gridLayout->addWidget(followersField, 1, 1);
    gridLayout->addWidget(regionLabel, 0, 2);
    gridLayout->addWidget(regionField, 1, 2);
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setColumnStretch(1, 1);
    gridLayout->setColumnStretch(2, 1);

    formLayout->addLayout(gridLayout);

    // Search Button - Full width below form
    QPushButton *searchBtn = new QPushButton("🔎 Search Influencers");
    searchBtn->setFixedHeight(48);
    searchBtn->setCursor(Qt::PointingHandCursor);
    searchBtn->setStyleSheet(
        "QPushButton { "
        "  background-color: " PRIMARY_GREEN "; "
        "  color: white; "
        "  border-radius: 10px; "
        "  font-weight: bold; "
        "  font-size: 16px; "
        "} "
        "QPushButton:hover { background-color: #27AE60; }"
        );
    formLayout->addWidget(searchBtn);

    mainLayout->addWidget(formCard);

    // Results Card
    QFrame *resultsCard = new QFrame();
    resultsCard->setObjectName("card");
    resultsCard->setStyleSheet(cardStyle);

    QVBoxLayout *resultsLayout = new QVBoxLayout(resultsCard);
    resultsLayout->setContentsMargins(25, 25, 25, 25);
    resultsLayout->setSpacing(15);

    QHBoxLayout *resultsHeader = new QHBoxLayout();
    QLabel *resultsIcon = new QLabel("👥");
    resultsIcon->setStyleSheet("font-size: 24px; background: " ACCENT_LIGHT_BLUE "; padding: 8px; border-radius: 8px;");
    QLabel *resultsTitle = new QLabel("Search Results (BST)");
    resultsTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: " TEXT_DARK ";");
    resultsHeader->addWidget(resultsIcon);
    resultsHeader->addWidget(resultsTitle);
    resultsHeader->addStretch();
    resultsLayout->addLayout(resultsHeader);

    influencerResultsList = new QListWidget();
    influencerResultsList->setStyleSheet(
        "QListWidget { "
        "  border: 1px solid " BORDER_COLOR "; "
        "  border-radius: 10px; "
        "  padding: 8px; "
        "  background-color: #FAFBFC; "
        "  min-height: 200px; "
        "} "
        "QListWidget::item { "
        "  padding: 12px; "
        "  border-bottom: 1px solid #F0F0F0; "
        "  border-radius: 6px; "
        "  margin: 2px; "
        "} "
        "QListWidget::item:selected { "
        "  background: " PRIMARY_BLUE "; "
        "  color: white; "
        "} "
        "QListWidget::item:hover:!selected { "
        "  background: " ACCENT_LIGHT_BLUE "; "
        "}"
        );
    resultsLayout->addWidget(influencerResultsList);

    mainLayout->addWidget(resultsCard);
    mainLayout->addStretch();

    connect(searchBtn, &QPushButton::clicked, this, &BrandDashboard::handleSearch);
    
    // Connect list selection to fill the influencer field in next tab
    connect(influencerResultsList, &QListWidget::itemClicked, this, [this](QListWidgetItem *item) {
       // Since we are using custom widgets, the text might be empty on the item itself if not set
       // But we set it via member data or we can just find it in the combo
       int id = item->data(Qt::UserRole).toInt();
       Influencer* inf = systemManager->getInfluencerById(id);
       if(inf) {
           selectedInfluencerField->setCurrentText(inf->name);
       }
       // Switch to campaign tab for UX
       this->window()->findChild<QTabWidget*>()->setCurrentIndex(1); // Assuming 0-based index 1 is create campaign
    });

    return tab;
}

// --- TAB 2: Create Campaign (More Prominent Sections) ---
QWidget *BrandDashboard::createCampaignCreationTab()
{
    QWidget *tab = new QWidget();
    tab->setStyleSheet("background-color: " LIGHT_GREY ";");

    // Use scroll area to handle overflow
    QScrollArea *scrollArea = new QScrollArea(tab);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("background-color: transparent;");

    QWidget *scrollContent = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(scrollContent);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(25);

    // Page Header
    QLabel *pageTitle = new QLabel("Campaign Creation & Task Management");
    pageTitle->setAlignment(Qt::AlignCenter);
    pageTitle->setStyleSheet(
        "font-size: 26px; "
        "font-weight: bold; "
        "color: " PRIMARY_BLUE "; "
        "font-family: Georgia; "
        "margin-bottom: 5px;"
        );
    mainLayout->addWidget(pageTitle);

    QLabel *pageSubtitle = new QLabel("Set up your collaboration details and manage campaign tasks");
    pageSubtitle->setAlignment(Qt::AlignCenter);
    pageSubtitle->setStyleSheet("font-size: 14px; color: #6B7280; margin-bottom: 10px;");
    mainLayout->addWidget(pageSubtitle);

    // ========== SECTION 1: Collaboration Details ==========
    QFrame *section1Card = new QFrame();
    section1Card->setObjectName("card");
    section1Card->setStyleSheet(cardStyle + inputStyle);
    section1Card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    QVBoxLayout *section1Layout = new QVBoxLayout(section1Card);
    section1Layout->setContentsMargins(25, 25, 25, 25);
    section1Layout->setSpacing(12);

    // Section Header with Number Badge
    QHBoxLayout *section1Header = new QHBoxLayout();
    section1Header->setSpacing(10);

    QLabel *badge1 = new QLabel("1");
    badge1->setFixedSize(32, 32);
    badge1->setAlignment(Qt::AlignCenter);
    badge1->setStyleSheet(
        "background-color: " PRIMARY_BLUE "; "
        "color: white; "
        "border-radius: 16px; "
        "font-weight: bold; "
        "font-size: 14px;"
        );

    QLabel *section1Title = new QLabel("📄 Collaboration Details");
    section1Title->setStyleSheet("font-size: 18px; font-weight: bold; color: " TEXT_DARK ";");
    section1Title->setMinimumHeight(32);

    section1Header->addWidget(badge1);
    section1Header->addWidget(section1Title);
    section1Header->addStretch();
    section1Layout->addLayout(section1Header);

    // Separator Line
    QFrame *separator1 = new QFrame();
    separator1->setFrameShape(QFrame::HLine);
    separator1->setFrameShadow(QFrame::Plain);
    separator1->setFixedHeight(1);
    separator1->setStyleSheet("background-color: " BORDER_COLOR ";");
    section1Layout->addWidget(separator1);

    // Influencer Field
    QLabel *influencerLabel = new QLabel("👤 Selected Influencer");
    influencerLabel->setStyleSheet("font-size: 13px; font-weight: 500; color: #6B7280;");
    influencerLabel->setMinimumHeight(20);
    section1Layout->addWidget(influencerLabel);

    selectedInfluencerField = new QComboBox();
    selectedInfluencerField->addItem("No influencer selected");
    // Populate with all influencers
    QVector<Influencer*> allInfs = systemManager->getAllInfluencers();
    for(Influencer* inf : allInfs) {
        selectedInfluencerField->addItem(inf->name);
    }
    selectedInfluencerField->setFixedHeight(44);
    section1Layout->addWidget(selectedInfluencerField);

    // Add spacing
    section1Layout->addSpacing(8);

    // Description
    QLabel *descLabel = new QLabel("Campaign Description");
    descLabel->setStyleSheet("font-size: 13px; font-weight: 500; color: #6B7280;");
    descLabel->setMinimumHeight(20);
    section1Layout->addWidget(descLabel);

    campaignDescription = new QTextEdit();
    campaignDescription->setPlaceholderText("Enter campaign goals, deliverables, and description...");
    campaignDescription->setMinimumHeight(100);
    campaignDescription->setMaximumHeight(150);
    section1Layout->addWidget(campaignDescription);

    mainLayout->addWidget(section1Card);

    // ========== SECTION 2: Campaign Tasks ==========
    QFrame *tasksCard = new QFrame();
    tasksCard->setObjectName("card");
    tasksCard->setStyleSheet(cardStyle);
    tasksCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    QVBoxLayout *tasksMainLayout = new QVBoxLayout(tasksCard);
    tasksMainLayout->setContentsMargins(25, 25, 25, 25);
    tasksMainLayout->setSpacing(12);

    // Section Header with number badge
    QHBoxLayout *section2Header = new QHBoxLayout();
    section2Header->setSpacing(10);

    QLabel *badge2 = new QLabel("2");
    badge2->setFixedSize(32, 32);
    badge2->setAlignment(Qt::AlignCenter);
    badge2->setStyleSheet(
        "background-color: " PRIMARY_BLUE "; "
        "color: white; "
        "border-radius: 16px; "
        "font-weight: bold; "
        "font-size: 14px;"
        );

    QLabel *section2Title = new QLabel("📋 Campaign Tasks (Linked List)");
    section2Title->setStyleSheet("font-size: 18px; font-weight: bold; color: " TEXT_DARK ";");
    section2Title->setMinimumHeight(32);

    section2Header->addWidget(badge2);
    section2Header->addWidget(section2Title);
    section2Header->addStretch();
    tasksMainLayout->addLayout(section2Header);

    // Separator line
    QFrame *separator2 = new QFrame();
    separator2->setFrameShape(QFrame::HLine);
    separator2->setFrameShadow(QFrame::Plain);
    separator2->setFixedHeight(1);
    separator2->setStyleSheet("background-color: " BORDER_COLOR ";");
    tasksMainLayout->addWidget(separator2);

    // Task List
    taskListWidget = new QListWidget();
    taskListWidget->addItem("⏳ To be accepted: Post a story");
    taskListWidget->setMinimumHeight(120);
    taskListWidget->setMaximumHeight(200);
    taskListWidget->setStyleSheet(
        "QListWidget { border: 1px solid #E0E0E0; border-radius: 8px; padding: 10px; background-color: #F8F9FA; }"
        "QListWidget::item { padding: 12px; border-bottom: 1px solid #E9ECEF; border-radius: 6px; margin: 2px; background-color: white; }"
        );
    tasksMainLayout->addWidget(taskListWidget);

    // Task Input Row
    QHBoxLayout *taskInputLayout = new QHBoxLayout();
    taskInputLayout->setSpacing(12);

    newTaskField = new QLineEdit();
    newTaskField->setPlaceholderText("New Task (e.g., Go live on Friday)");
    newTaskField->setFixedHeight(44);
    newTaskField->setStyleSheet(
        "QLineEdit { border: 1px solid #D0D0D0; border-radius: 8px; padding: 10px 15px; background-color: white; font-size: 14px; }"
        "QLineEdit:focus { border: 2px solid " PRIMARY_BLUE "; }"
        );
    taskInputLayout->addWidget(newTaskField, 1);

    QPushButton *addTaskBtn = new QPushButton("➕ Add Task");
    addTaskBtn->setFixedSize(120, 44);
    addTaskBtn->setStyleSheet(
        "QPushButton { background-color: #17A2B8; color: white; padding: 10px 20px; border-radius: 8px; font-weight: bold; font-size: 14px; }"
        "QPushButton:hover { background-color: #138496; }"
        );
    addTaskBtn->setCursor(Qt::PointingHandCursor);
    taskInputLayout->addWidget(addTaskBtn);

    tasksMainLayout->addLayout(taskInputLayout);

    mainLayout->addWidget(tasksCard);

    // ========== SECTION 3: Action Button ==========
    QPushButton *sendInviteBtn = new QPushButton("📧 Send Collaboration Invite");
    sendInviteBtn->setFixedHeight(56);
    sendInviteBtn->setStyleSheet(
        "QPushButton { background-color: #FFC107; color: " TEXT_DARK "; padding: 15px; border-radius: 8px; font-weight: bold; font-size: 16px; }"
        "QPushButton:hover { background-color: #E0A800; }"
        );
    sendInviteBtn->setCursor(Qt::PointingHandCursor);
    mainLayout->addWidget(sendInviteBtn);

    mainLayout->addStretch();

    // Set scroll area content
    scrollArea->setWidget(scrollContent);

    // Main tab layout
    QVBoxLayout *tabLayout = new QVBoxLayout(tab);
    tabLayout->setContentsMargins(0, 0, 0, 0);
    tabLayout->addWidget(scrollArea);

    // Connections
    connect(addTaskBtn, &QPushButton::clicked, this, &BrandDashboard::addCampaignTask);
    connect(sendInviteBtn, &QPushButton::clicked, this, &BrandDashboard::handleCreateCampaign);

    return tab;
}


// --- TAB 3: Campaign History ---
QWidget *BrandDashboard::createCampaignHistoryTab()
{
    QWidget *tab = new QWidget();
    tab->setStyleSheet("background-color: " LIGHT_GREY ";");

    QVBoxLayout *mainLayout = new QVBoxLayout(tab);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(20);

    QFrame *card = new QFrame();
    card->setObjectName("card");
    card->setStyleSheet(cardStyle);

    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(25, 25, 25, 25);
    cardLayout->setSpacing(15);

    QHBoxLayout *headerLayout = new QHBoxLayout();
    QLabel *iconLabel = new QLabel("📜");
    iconLabel->setStyleSheet("font-size: 24px; background: " ACCENT_LIGHT_BLUE "; padding: 8px; border-radius: 8px;");
    QLabel *heading = new QLabel("Invite History & Task Status (Linked List)");
    heading->setStyleSheet("font-size: 20px; font-weight: bold; color: " PRIMARY_BLUE ";");
    headerLayout->addWidget(iconLabel);
    headerLayout->addWidget(heading);
    headerLayout->addStretch();
    cardLayout->addLayout(headerLayout);

    campaignHistoryList = new QListWidget();
    campaignHistoryList->addItem("✅ Invite Sent to John (Status: Completed)");
    campaignHistoryList->addItem("⏳ Invite Sent to Jane (Status: Pending)");
    campaignHistoryList->setStyleSheet(
        "QListWidget { "
        "  border: 1px solid " BORDER_COLOR "; "
        "  border-radius: 10px; "
        "  padding: 10px; "
        "  background-color: " CARD_WHITE "; "
        "  min-height: 300px; "
        "} "
        "QListWidget::item { "
        "  padding: 14px; "
        "  border-bottom: 1px solid #F0F0F0; "
        "  border-radius: 6px; "
        "  margin: 2px; "
        "} "
        "QListWidget::item:selected { "
        "  background: #E0E4E8; "
        "  color: " TEXT_DARK "; "
        "} "
        "QListWidget::item:hover:!selected { "
        "  background: " ACCENT_LIGHT_BLUE "; "
        "}"
        );
    cardLayout->addWidget(campaignHistoryList);

    mainLayout->addWidget(card);
    mainLayout->addStretch();

    return tab;
}

// --- Slot Implementations ---
void BrandDashboard::handleSearch()
{
    QString niche = nicheCombo->currentText();
    QString followersText = followersField->text();
    int minFollowers = followersText.isEmpty() ? 0 : followersText.toInt();
    // Default max to very high if not specified, or just search > min
    int maxFollowers = 10000000; 

    influencerResultsList->clear();
    
    // Call backend
    QVector<Influencer*> results = systemManager->searchInfluencers(minFollowers, maxFollowers, niche);

    if (results.isEmpty()) {
        influencerResultsList->addItem("No influencers found matching criteria.");
    } else {
        for (Influencer* inf : results) {
            QListWidgetItem* item = new QListWidgetItem(influencerResultsList);
            
            // Create custom widget
            QFrame* wid = new QFrame();
            wid->setStyleSheet("background-color: white; border: 1px solid #e2e8f0; border-radius: 8px; padding: 5px;");
            QHBoxLayout* lay = new QHBoxLayout(wid);
            lay->setContentsMargins(10, 10, 10, 10);
            
            // Avatar Placeholder
            QLabel* avatar = new QLabel(inf->name.left(1)); 
            avatar->setFixedSize(40, 40);
            avatar->setAlignment(Qt::AlignCenter);
            avatar->setStyleSheet("background-color: #3b82f6; color: white; border-radius: 20px; font-weight: bold; font-size: 18px;");
            
            // Info
            QVBoxLayout* infoLay = new QVBoxLayout();
            QLabel* nameLbl = new QLabel(inf->name);
            nameLbl->setStyleSheet("font-weight: bold; font-size: 16px; color: #1e293b;");
            QLabel* detailLbl = new QLabel(QString("%1 | %2 Followers").arg(inf->niche).arg(inf->followers));
            detailLbl->setStyleSheet("color: #64748b; font-size: 12px;");
            infoLay->addWidget(nameLbl);
            infoLay->addWidget(detailLbl);
            
            // Engagement Badge
            QLabel* engBadge = new QLabel(QString("⚡ %1%").arg(inf->engagementRate));
            engBadge->setStyleSheet("background-color: #dcfce7; color: #166534; padding: 4px 8px; border-radius: 6px; font-weight: bold; font-size: 12px;");
            
            lay->addWidget(avatar);
            lay->addLayout(infoLay);
            lay->addStretch();
            lay->addWidget(engBadge);
            
            item->setSizeHint(QSize(0, 130)); // Fixed height explicitly, width auto
            influencerResultsList->addItem(item);
            influencerResultsList->setItemWidget(item, wid);
            
            // Store ID
            item->setData(Qt::UserRole, inf->id); 
        }
    }
}

void BrandDashboard::addCampaignTask()
{
    QString task = newTaskField->text();
    if (!task.isEmpty()) {
        taskListWidget->addItem("⬜ To be accepted: " + task);
        newTaskField->clear();
    }
}

void BrandDashboard::handleCreateCampaign()
{
    QString influencer = selectedInfluencerField->currentText();
    QString description = campaignDescription->toPlainText();
    
    // Hardcoded current brand for demo
    QString brandName = "Nike"; 
    
    // Create Campaign
    // Create Campaign
    // Pass empty influencer name initially so it doesn't show in dashboard until accepted
    int campaignId = systemManager->createCampaign(description, brandName, 5000.0, "");
    
    // Add tasks from the UI list widget
    for(int i = 0; i < taskListWidget->count(); ++i) {
        QString taskDesc = taskListWidget->item(i)->text();
        // Clean up the UI text prefix if present
        taskDesc = taskDesc.replace("⏳ To be accepted: ", "").replace("⬜ To be accepted: ", "");
        systemManager->addTaskToCampaign(campaignId, taskDesc);
    }
    
    // Send Request to Queue
    if (!influencer.isEmpty() && influencer != "No influencer selected") {
        systemManager->sendCollaborationRequest(brandName, description, influencer, campaignId);
        systemManager->addNotification("Sent request to " + influencer, "brand", "REQUEST");
        
        campaignHistoryList->addItem("✅ Request sent to " + influencer + " (Campaign ID: " + QString::number(campaignId) + ")");
    } else {
        // Just create campaign locally if no influencer
        campaignHistoryList->addItem("✅ Campaign created: " + description);
    }
    
    // Clear form
    campaignDescription->clear();
    taskListWidget->clear();
}

// --- TAB 4: Manage Influencers ---
QWidget *BrandDashboard::createManageInfluencersTab()
{
    QWidget *tab = new QWidget();
    tab->setStyleSheet("background-color: " LIGHT_GREY ";");

    QVBoxLayout *mainLayout = new QVBoxLayout(tab);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(20);

    QFrame *card = new QFrame();
    card->setStyleSheet(cardStyle + inputStyle);
    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(30, 30, 30, 30);
    cardLayout->setSpacing(15);

    // Header
    QLabel *title = new QLabel("👤 Manage Influencers");
    title->setStyleSheet("font-size: 22px; font-weight: bold; color: " TEXT_DARK "; margin-bottom: 10px;");
    cardLayout->addWidget(title);

    // Selector
    QLabel *selLabel = new QLabel("Select Influencer to Edit (or 'Create New')");
    selLabel->setStyleSheet("font-weight: 500; color: #6B7280;");
    mgmtSelectInfluencer = new QComboBox();
    mgmtSelectInfluencer->addItem("➕ Create New Influencer");
    // Populate
    QVector<Influencer*> all = systemManager->getAllInfluencers();
    for(Influencer* inf : all) {
        mgmtSelectInfluencer->addItem(QString("%1 (ID: %2)").arg(inf->name).arg(inf->id), inf->id);
    }
    mgmtSelectInfluencer->setFixedHeight(45);
    connect(mgmtSelectInfluencer, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &BrandDashboard::loadInfluencerForEdit);
    cardLayout->addWidget(selLabel);
    cardLayout->addWidget(mgmtSelectInfluencer);
    
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("background: " BORDER_COLOR "; margin: 10px 0;");
    cardLayout->addWidget(line);

    // Form
    QGridLayout *form = new QGridLayout();
    form->setVerticalSpacing(15);
    
    mgmtNameField = new QLineEdit(); mgmtNameField->setPlaceholderText("Full Name");
    mgmtNicheField = new QLineEdit(); mgmtNicheField->setPlaceholderText("Niche (e.g. Tech, Beauty)");
    mgmtFollowersField = new QLineEdit(); mgmtFollowersField->setPlaceholderText("Follower Count");
    mgmtEngagementField = new QLineEdit(); mgmtEngagementField->setPlaceholderText("Engagement Rate (0-100)");
    mgmtEmailField = new QLineEdit(); mgmtEmailField->setPlaceholderText("Email Address");
    
    // Passwords are hidden directly, but user asked for "ALL THEIR DATA EVEN PASS"
    // So we assume we can edit password transparently or keep default if empty.
    
    form->addWidget(new QLabel("Name:"), 0, 0); form->addWidget(mgmtNameField, 0, 1);
    form->addWidget(new QLabel("Niche:"), 1, 0); form->addWidget(mgmtNicheField, 1, 1);
    form->addWidget(new QLabel("Followers:"), 2, 0); form->addWidget(mgmtFollowersField, 2, 1);
    form->addWidget(new QLabel("Engagement %:"), 3, 0); form->addWidget(mgmtEngagementField, 3, 1);
    form->addWidget(new QLabel("Email:"), 4, 0); form->addWidget(mgmtEmailField, 4, 1);

    cardLayout->addLayout(form);

    mgmtSaveBtn = new QPushButton("💾 Save Influencer Data");
    mgmtSaveBtn->setStyleSheet("background-color: " PRIMARY_GREEN "; color: white; font-weight: bold; padding: 12px; border-radius: 8px; font-size: 16px; margin-top: 20px;");
    mgmtSaveBtn->setCursor(Qt::PointingHandCursor);
    connect(mgmtSaveBtn, &QPushButton::clicked, this, &BrandDashboard::handleSaveInfluencer);
    cardLayout->addWidget(mgmtSaveBtn);

    cardLayout->addStretch();
    mainLayout->addWidget(card);
    mainLayout->addStretch();

    return tab;
}

void BrandDashboard::loadInfluencerForEdit() {
    int index = mgmtSelectInfluencer->currentIndex();
    if (index <= 0) {
        // Create New mode
        mgmtNameField->clear();
        mgmtNicheField->clear();
        mgmtFollowersField->clear();
        mgmtEngagementField->clear();
        mgmtEmailField->clear();
        mgmtSaveBtn->setText("➕ Create Influencer");
        return;
    }
    
    int id = mgmtSelectInfluencer->currentData().toInt();
    Influencer* inf = systemManager->getInfluencerById(id);
    if(inf) {
        mgmtNameField->setText(inf->name);
        mgmtNicheField->setText(inf->niche);
        mgmtFollowersField->setText(QString::number(inf->followers));
        mgmtEngagementField->setText(QString::number(inf->engagementRate));
        mgmtEmailField->setText(inf->email);
        mgmtSaveBtn->setText("💾 Update Influencer");
    }
}

void BrandDashboard::handleSaveInfluencer() {
    QString name = mgmtNameField->text();
    QString niche = mgmtNicheField->text();
    int followers = mgmtFollowersField->text().toInt();
    float engagement = mgmtEngagementField->text().toFloat();
    QString email = mgmtEmailField->text();
    
    if(name.isEmpty() || niche.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Name and Niche are required.");
        return;
    }

    int id;
    if (mgmtSelectInfluencer->currentIndex() <= 0) {
        // New ID: Find max + 1
        int maxId = 0;
        QVector<Influencer*> all = systemManager->getAllInfluencers();
        for(Influencer* inf : all) if(inf->id > maxId) maxId = inf->id;
        id = maxId + 1;
        
        systemManager->addInfluencer(id, name, niche, followers, engagement, email, "pass123"); 
        QMessageBox::information(this, "Success", "Influencer created successfully!");
    } else {
        // Update
        id = mgmtSelectInfluencer->currentData().toInt();
        // Since we don't have password field in UI, keep old one?
        // Use a generic logic or existing.
        Influencer* existing = systemManager->getInfluencerById(id);
        QString pass = existing ? existing->password : "pass123";
        
        systemManager->updateInfluencer(id, name, niche, followers, engagement, email, pass);
        QMessageBox::information(this, "Success", "Influencer updated successfully!");
    }
    
    // Refresh Dropdowns
    mgmtSelectInfluencer->blockSignals(true);
    mgmtSelectInfluencer->clear();
    mgmtSelectInfluencer->addItem("➕ Create New Influencer");
    QVector<Influencer*> all = systemManager->getAllInfluencers();
    for(Influencer* inf : all) {
        mgmtSelectInfluencer->addItem(QString("%1 (ID: %2)").arg(inf->name).arg(inf->id), inf->id);
    }
    mgmtSelectInfluencer->blockSignals(false);
    
    // Refresh the other dropdown (Campaign Tab)
    selectedInfluencerField->clear();
    selectedInfluencerField->addItem("No influencer selected");
    for(Influencer* inf : all) {
        selectedInfluencerField->addItem(inf->name);
    }
    
    // Reset form to "New" mode
    mgmtSelectInfluencer->setCurrentIndex(0);
    loadInfluencerForEdit();
}
