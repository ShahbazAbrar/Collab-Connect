#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "mainwindow.h"
#include "StartPage.h"
#include "BrandLoginPage.h"
#include "BrandDashboard.h"
#include "InfluencerLoginPage.h"  // <--- MUST HAVE THIS
#include "InfluencerDashboard.h" // <--- MUST HAVE THIS
#include "include/SystemManager.h" // <--- MUST HAVE THIS
// Forward declarations
class StartPage;
class BrandLoginPage;
class BrandDashboard;
class InfluencerLoginPage; // New
class InfluencerDashboard; // New
// class SystemManager; // Included directly

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(SystemManager *manager, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void navigateToLogin(const QString &userType);
    void navigateToDashboard();
    void navigateToStart();
    void navigateToInfluencerDashboard(QString username); // Added navigation slot

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;

    // Page pointers
    StartPage *startPage;
    BrandLoginPage *brandLoginPage;
    BrandDashboard *brandDashboard;
    InfluencerLoginPage *influencerLoginPage; // New
    InfluencerDashboard *influencerDashboard; // New
};

#endif // MAINWINDOW_H
