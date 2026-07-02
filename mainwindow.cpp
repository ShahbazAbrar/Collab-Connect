#include "mainwindow.h"
#include "StartPage.h"
#include "BrandLoginPage.h"
#include "BrandDashboard.h"
#include "InfluencerLoginPage.h"
#include "InfluencerDashboard.h"
#include <QApplication>
#include <QStackedWidget>

MainWindow::MainWindow(SystemManager *manager, QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Collab Connect Application");
    resize(1000, 700); // Increased default size for better dashboard visibility

    // 1. Setup QStackedWidget
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // 2. Instantiate All Pages
    startPage = new StartPage();
    brandLoginPage = new BrandLoginPage(manager);
    brandDashboard = new BrandDashboard(manager); // Pass manager
    influencerLoginPage = new InfluencerLoginPage(manager);
    influencerDashboard = new InfluencerDashboard(manager); // Pass manager

    // 3. Add Pages to the Stack
    stackedWidget->addWidget(startPage);           // Index 0
    stackedWidget->addWidget(brandLoginPage);       // Index 1
    stackedWidget->addWidget(brandDashboard);       // Index 2
    stackedWidget->addWidget(influencerLoginPage);  // Index 3
    stackedWidget->addWidget(influencerDashboard);  // Index 4

    // ---------------------------------------------------------
    // 4. UPDATED GLOBAL STYLING (QSS)
    // Matches image_cb1486.png, image_cb174f.png, and image_cb178f.png
    // ---------------------------------------------------------
    this->setStyleSheet(R"(
        /* --- General Background --- */
        QMainWindow { background-color: #f8f9fa; }

        /* --- Header Bar (Matching blue banner) --- */
        QWidget#headerBar {
            background-color: #3b82f6;
            min-height: 70px;
        }

        QLabel#headerLogo {
            color: white;
            font-size: 24px;
            font-weight: bold;
            padding-left: 20px;
        }

        QPushButton#logoutBtn {
            background-color: #f87171;
            color: white;
            border-radius: 8px;
            padding: 8px 18px;
            font-weight: bold;
            margin-right: 20px;
        }

        /* --- Tab Widget Styling (Pill-shaped tabs) --- */
        QTabWidget::pane { border: none; background: transparent; padding: 10px; }

        QTabBar::tab {
            background: white;
            color: #64748b;
            padding: 12px 25px;
            margin: 5px;
            border-radius: 12px;
            border: 1px solid #e2e8f0;
            font-weight: 600;
        }

        QTabBar::tab:selected {
            background: #3b82f6;
            color: white;
            border: 1px solid #3b82f6;
        }

        /* --- Main Dashboard Cards --- */
        QFrame#whiteCard {
            background: white;
            border-radius: 20px;
            border: 1px solid #f1f5f9;
        }

        /* --- Inner Content Cards (Nested look) --- */
        QFrame#innerGrayCard {
            background-color: #ffffff;
            border: 1px solid #e2e8f0;
            border-radius: 15px;
            padding: 10px;
        }

        /* --- Icon Circles --- */
        QLabel#blueIconCircle {
            background-color: #dbeafe;
            border-radius: 20px;
            min-width: 40px;
            min-height: 40px;
            alignment: center;
        }

        QLabel#greenIconCircle {
            background-color: #dcfce7;
            border-radius: 15px;
            min-width: 30px;
            min-height: 30px;
            alignment: center;
        }

        /* --- Progress Bars (Task Tab) --- */
        QProgressBar {
            background-color: #f1f5f9;
            border-radius: 6px;
            text-align: center;
            height: 12px;
            border: none;
        }
        QProgressBar::chunk {
            background-color: #3b82f6;
            border-radius: 6px;
        }

        /* --- Buttons & Tags --- */
        QLabel#amountTag {
            background-color: #22c55e;
            color: white;
            border-radius: 15px;
            padding: 5px 15px;
            font-weight: bold;
        }

        QPushButton#acceptBtn {
            background-color: #22c55e;
            color: white;
            font-weight: bold;
            border-radius: 12px;
            height: 45px;
        }

        QPushButton#rejectBtn {
            background-color: #ef4444;
            color: white;
            font-weight: bold;
            border-radius: 12px;
            height: 45px;
        }
    )");

    // 5. Initial Navigation
    stackedWidget->setCurrentWidget(startPage);

    // 6. Connect Navigation Signals
    connect(startPage, &StartPage::userTypeSelected, this, &MainWindow::navigateToLogin);
    connect(brandLoginPage, &BrandLoginPage::loginSuccess, this, &MainWindow::navigateToDashboard);
    connect(brandLoginPage, &BrandLoginPage::backToStart, this, &MainWindow::navigateToStart);
    connect(brandDashboard, &BrandDashboard::logoutClicked, this, &MainWindow::navigateToStart);
    connect(influencerLoginPage, &InfluencerLoginPage::loginSuccess, this, &MainWindow::navigateToInfluencerDashboard);
    connect(influencerLoginPage, &InfluencerLoginPage::backToStart, this, &MainWindow::navigateToStart);
    connect(influencerDashboard, &InfluencerDashboard::logoutClicked, this, &MainWindow::navigateToStart);
}

MainWindow::~MainWindow() {}

void MainWindow::navigateToLogin(const QString &userType) {
    if (userType == "Brand") stackedWidget->setCurrentWidget(brandLoginPage);
    else if (userType == "Influencer") stackedWidget->setCurrentWidget(influencerLoginPage);
}

void MainWindow::navigateToDashboard() { stackedWidget->setCurrentWidget(brandDashboard); }
void MainWindow::navigateToInfluencerDashboard(QString username) { 
    influencerDashboard->setCurrentInfluencer(username);
    stackedWidget->setCurrentWidget(influencerDashboard); 
}
void MainWindow::navigateToStart() { stackedWidget->setCurrentWidget(startPage); }
