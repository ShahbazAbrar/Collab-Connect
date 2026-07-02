// BrandLoginPage.cpp

#include "BrandLoginPage.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QFont>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QRadialGradient> // Ensure QRadialGradient is included if used

// Custom widget for the gradient background with decorative shapes
class GradientBackground : public QWidget
{
public:
    explicit GradientBackground(QWidget *parent = nullptr) : QWidget(parent) {}

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Create gradient background
        QLinearGradient gradient(0, 0, width(), height());
        gradient.setColorAt(0, QColor(25, 118, 210));  // #1976D2
        gradient.setColorAt(0.5, QColor(30, 136, 229)); // #1E88E5
        gradient.setColorAt(1, QColor(13, 71, 161));   // #0D47A1
        painter.fillRect(rect(), gradient);

        // Draw decorative circles
        painter.setOpacity(0.15);

        // Top left circle
        QRadialGradient circle1(width() * 0.1, height() * 0.2, 200);
        circle1.setColorAt(0, QColor(100, 181, 246)); // Lighter blue
        circle1.setColorAt(1, Qt::transparent);
        painter.setBrush(circle1);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(QPointF(width() * 0.1, height() * 0.2), 200, 200);

        // Bottom right circle
        QRadialGradient circle2(width() * 0.9, height() * 0.9, 300);
        circle2.setColorAt(0, QColor(13, 71, 161)); // Darker blue
        circle2.setColorAt(1, Qt::transparent);
        painter.setBrush(circle2);
        painter.drawEllipse(QPointF(width() * 0.9, height() * 0.9), 300, 300);

        // Bottom center circle
        QRadialGradient circle3(width() * 0.3, height() * 0.95, 250);
        circle3.setColorAt(0, QColor(66, 165, 245)); // Medium blue
        circle3.setColorAt(1, Qt::transparent);
        painter.setBrush(circle3);
        painter.drawEllipse(QPointF(width() * 0.3, height() * 0.95), 250, 250);
    }
};

BrandLoginPage::BrandLoginPage(SystemManager *manager, QWidget *parent)
    : QWidget(parent), passwordVisible(false), systemManager(manager)
{
    // Main layout
    QVBoxLayout *mainContainer = new QVBoxLayout(this);
    mainContainer->setContentsMargins(0, 0, 0, 0);
    mainContainer->setSpacing(0);

    GradientBackground *background = new GradientBackground(this);

    QHBoxLayout *contentLayout = new QHBoxLayout(background);
    contentLayout->setContentsMargins(60, 40, 60, 40);
    contentLayout->setSpacing(40);

    // --- LEFT PANEL ---
    QWidget *leftPanel = new QWidget(background);
    leftPanel->setStyleSheet("background: transparent;");
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setSpacing(20);
    leftLayout->setContentsMargins(0,0,0,0);

    leftLayout->addStretch(); // Top stretch for vertical centering

    // Container for welcome text
    QWidget *welcomeContainer = new QWidget(leftPanel);
    QVBoxLayout *welcomeLayout = new QVBoxLayout(welcomeContainer);
    welcomeLayout->setSpacing(15);
    welcomeLayout->setAlignment(Qt::AlignCenter);

    QLabel *welcomeLabel = new QLabel("WELCOME", welcomeContainer);
    QFont welcomeFont;
    welcomeFont.setPointSize(48);
    welcomeFont.setBold(true);
    welcomeFont.setLetterSpacing(QFont::AbsoluteSpacing, 8);
    welcomeLabel->setFont(welcomeFont);
    welcomeLabel->setStyleSheet("color: white; background: transparent;");
    welcomeLabel->setAlignment(Qt::AlignCenter);

    QLabel *headlineLabel = new QLabel("Log In to manage your Campaigns", welcomeContainer);
    QFont headlineFont;
    headlineFont.setPointSize(16);
    headlineFont.setWeight(QFont::Medium);
    headlineLabel->setFont(headlineFont);
    headlineLabel->setStyleSheet("color: white; background: transparent;");
    headlineLabel->setAlignment(Qt::AlignCenter);

    QLabel *descLabel = new QLabel(
        "Sign in to explore top influencers, create tailored campaigns, and manage "
        "all your collaborations effortlessly. "
        "Your brand’s next successful campaign starts here.",
        welcomeContainer
        );
    descLabel->setWordWrap(true);
    descLabel->setMaximumWidth(400);
    QFont descFont;
    descFont.setPointSize(10);
    descLabel->setFont(descFont);
    descLabel->setStyleSheet("color: rgba(255, 255, 255, 200); background: transparent;");
    descLabel->setAlignment(Qt::AlignCenter);

    welcomeLayout->addWidget(welcomeLabel);
    welcomeLayout->addWidget(headlineLabel);
    welcomeLayout->addWidget(descLabel);

    leftLayout->addWidget(welcomeContainer);
    leftLayout->addStretch(); // Bottom stretch to center

    // Back button at bottom-left
    QPushButton *backButtonLeft = new QPushButton("← Back", leftPanel);
    backButtonLeft->setFixedWidth(120);
    backButtonLeft->setFixedHeight(40);
    backButtonLeft->setStyleSheet(
        "QPushButton { "
        "  background-color: rgba(13, 71, 161, 180); "
        "  color: white; "
        "  border: 2px solid white; "
        "  border-radius: 8px; "
        "  padding: 8px 16px; "
        "  font-weight: bold; "
        "  font-size: 14px; "
        "} "
        "QPushButton:hover { "
        "  background-color: white; "
        "  color: #1976D2; "
        "}"
        );
    leftLayout->addWidget(backButtonLeft, 0, Qt::AlignLeft);

    // --- RIGHT PANEL ---
    QWidget *rightPanel = new QWidget(background);
    rightPanel->setStyleSheet("background: transparent;");
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setAlignment(Qt::AlignCenter);

    QFrame *loginCard = new QFrame(rightPanel);
    loginCard->setFixedWidth(450);
    loginCard->setStyleSheet(
        "QFrame { background-color: white; border-radius: 24px; }"
        );

    QVBoxLayout *cardLayout = new QVBoxLayout(loginCard);
    cardLayout->setContentsMargins(50, 50, 50, 50);
    cardLayout->setSpacing(20);

    QLabel *titleLabel = new QLabel("Brand Sign in", loginCard);
    QFont titleFont;
    titleFont.setPointSize(28);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #1976D2;");
    titleLabel->setAlignment(Qt::AlignCenter);

    cardLayout->addWidget(titleLabel);
    cardLayout->addSpacing(20);

    // Email
    QWidget *emailContainer = new QWidget(loginCard);
    QHBoxLayout *emailLayout = new QHBoxLayout(emailContainer);
    emailLayout->setContentsMargins(12, 0, 12, 0);
    emailLayout->setSpacing(8);

    QLabel *userIcon = new QLabel("👤", emailContainer);
    userIcon->setStyleSheet("font-size: 18px; color: #666;");

    emailField = new QLineEdit(emailContainer);
    emailField->setPlaceholderText("Email or Username");
    emailField->setFixedHeight(48);
    emailField->setStyleSheet(
        "QLineEdit { border: none; background: #F5F5F5; font-size: 14px; padding: 0px; }"
        );

    emailLayout->addWidget(userIcon);
    emailLayout->addWidget(emailField);

    emailContainer->setStyleSheet("QWidget { background: #F5F5F5; border-radius: 8px; }");

    // Password
    QWidget *passwordContainer = new QWidget(loginCard);
    QHBoxLayout *passwordLayout = new QHBoxLayout(passwordContainer);
    passwordLayout->setContentsMargins(12, 0, 12, 0);
    passwordLayout->setSpacing(8);

    QLabel *lockIcon = new QLabel("🔒", passwordContainer);
    lockIcon->setStyleSheet("font-size: 18px; color: #666;");

    passwordField = new QLineEdit(passwordContainer);
    passwordField->setPlaceholderText("Password");
    passwordField->setEchoMode(QLineEdit::Password);
    passwordField->setFixedHeight(48);
    passwordField->setStyleSheet(
        "QLineEdit { border: none; background: #F5F5F5; font-size: 14px; padding: 0px; }"
        );

    showPasswordButton = new QPushButton("SHOW", passwordContainer);
    showPasswordButton->setFixedWidth(60);
    showPasswordButton->setStyleSheet(
        "QPushButton { background: transparent; border: none; color: #333; font-weight: bold; font-size: 11px; }"
        "QPushButton:hover { color: #1976D2; }"
        );

    passwordLayout->addWidget(lockIcon);
    passwordLayout->addWidget(passwordField);
    passwordLayout->addWidget(showPasswordButton);

    passwordContainer->setStyleSheet("QWidget { background: #F5F5F5; border-radius: 8px; }");

    cardLayout->addWidget(emailContainer);
    cardLayout->addWidget(passwordContainer);

    // Remember me + forgot
    QWidget *optionsRow = new QWidget(loginCard);
    QHBoxLayout *optionsLayout = new QHBoxLayout(optionsRow);
    optionsLayout->setContentsMargins(0, 0, 0, 0);

    rememberMeCheckbox = new QCheckBox("Remember me", optionsRow);
    rememberMeCheckbox->setStyleSheet("QCheckBox { font-size: 12px; color: #333; }");

    QPushButton *forgotButton = new QPushButton("Forgot Password?", optionsRow);
    forgotButton->setStyleSheet(
        "QPushButton { background: transparent; border: none; color: #1976D2; font-size: 12px; font-weight: bold; text-decoration: underline; }"
        );
    forgotButton->setCursor(Qt::PointingHandCursor);

    optionsLayout->addWidget(rememberMeCheckbox);
    optionsLayout->addStretch();
    optionsLayout->addWidget(forgotButton);

    cardLayout->addWidget(optionsRow);

    // Login button
    loginButton = new QPushButton("Sign in", loginCard);
    loginButton->setFixedHeight(48);
    loginButton->setStyleSheet(
        "QPushButton { background-color: #0D47A1; color: white; border: none; border-radius: 8px; font-weight: bold; font-size: 16px; }"
        "QPushButton:hover { background-color: #1976D2; }"
        );
    loginButton->setCursor(Qt::PointingHandCursor);
    cardLayout->addWidget(loginButton);

    errorLabel = new QLabel(loginCard);
    errorLabel->setStyleSheet("color: #D32F2F; font-weight: bold; font-size: 12px;");
    errorLabel->setAlignment(Qt::AlignCenter);
    errorLabel->setVisible(false);
    cardLayout->addWidget(errorLabel);

    rightLayout->addWidget(loginCard);

    // Add panels to content
    contentLayout->addWidget(leftPanel, 45);
    contentLayout->addWidget(rightPanel, 55);

    mainContainer->addWidget(background);

    // Connections
    connect(loginButton, &QPushButton::clicked, this, &BrandLoginPage::attemptLogin);
    connect(showPasswordButton, &QPushButton::clicked, this, &BrandLoginPage::togglePasswordVisibility);
    connect(backButtonLeft, &QPushButton::clicked, this, &BrandLoginPage::backToStart);
}

void BrandLoginPage::attemptLogin()
{
    QString email = emailField->text();
    QString password = passwordField->text();

    if (systemManager->verifyBrandLogin(email, password)) {
        errorLabel->setVisible(false);
        emit loginSuccess();
    } else {
        errorLabel->setText("Invalid credentials. Please check brands.txt");
        errorLabel->setVisible(true);
    }
}

void BrandLoginPage::togglePasswordVisibility()
{
    passwordVisible = !passwordVisible;

    if (passwordVisible) {
        // FIX: Changed misspelled QLisneEdit to correct QLineEdit
        passwordField->setEchoMode(QLineEdit::Normal);
        showPasswordButton->setText("HIDE");
    } else {
        passwordField->setEchoMode(QLineEdit::Password);
        showPasswordButton->setText("SHOW");
    }
}
