#include "InfluencerLoginPage.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QFont>
#include <QPainter>

// Reusing the gradient background logic for visual identity
class InfluencerBackground : public QWidget {
public:
    explicit InfluencerBackground(QWidget *parent = nullptr) : QWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        QLinearGradient gradient(0, 0, width(), height());
        gradient.setColorAt(0, QColor(25, 118, 210));
        gradient.setColorAt(1, QColor(13, 71, 161));
        painter.fillRect(rect(), gradient);
    }
};

InfluencerLoginPage::InfluencerLoginPage(SystemManager *manager, QWidget *parent)
    : QWidget(parent), passwordVisible(false), systemManager(manager)
{
    QVBoxLayout *mainContainer = new QVBoxLayout(this);
    mainContainer->setContentsMargins(0, 0, 0, 0);

    InfluencerBackground *background = new InfluencerBackground(this);
    QHBoxLayout *contentLayout = new QHBoxLayout(background);
    contentLayout->setContentsMargins(60, 40, 60, 40);

    // --- LEFT PANEL ---
    QWidget *leftPanel = new QWidget();
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->addStretch();

    QLabel *welcomeLabel = new QLabel("WELCOME");
    welcomeLabel->setStyleSheet("color: white; font-size: 48pt; font-weight: bold; letter-spacing: 8px;");

    QLabel *headlineLabel = new QLabel("Log In to manage your Brand Deals");
    headlineLabel->setStyleSheet("color: white; font-size: 16pt;");

    QLabel *descLabel = new QLabel("Sign in to view your latest collaboration offers, "
                                   "track your campaign milestones, and manage your earnings.");
    descLabel->setWordWrap(true);
    descLabel->setStyleSheet("color: rgba(255, 255, 255, 200); font-size: 10pt;");
    descLabel->setMaximumWidth(400);

    leftLayout->addWidget(welcomeLabel);
    leftLayout->addWidget(headlineLabel);
    leftLayout->addWidget(descLabel);
    leftLayout->addStretch();

    QPushButton *backBtn = new QPushButton("← Back");
    backBtn->setFixedSize(120, 40);
    backBtn->setStyleSheet("QPushButton { background: rgba(13, 71, 161, 180); border: 2px solid white; color: white; border-radius: 8px; font-weight: bold; } "
                           "QPushButton:hover { background: white; color: #1976D2; }");
    leftLayout->addWidget(backBtn);

    // --- RIGHT PANEL (The Login Card) ---
    QWidget *rightPanel = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setAlignment(Qt::AlignCenter);

    QFrame *loginCard = new QFrame();
    loginCard->setFixedWidth(450);
    loginCard->setStyleSheet("QFrame { background-color: white; border-radius: 24px; }");
    QVBoxLayout *cardLayout = new QVBoxLayout(loginCard);
    cardLayout->setContentsMargins(50, 50, 50, 50);
    cardLayout->setSpacing(20);

    QLabel *titleLabel = new QLabel("Influencer Sign in");
    titleLabel->setStyleSheet("color: #1976D2; font-size: 28pt; font-weight: bold;");
    titleLabel->setAlignment(Qt::AlignCenter);

    userField = new QLineEdit();
    userField->setPlaceholderText("Influencer Username");
    userField->setFixedHeight(48);
    userField->setStyleSheet("QLineEdit { background: #F5F5F5; border-radius: 8px; padding: 10px; border: none; }");

    passwordField = new QLineEdit();
    passwordField->setPlaceholderText("Password");
    passwordField->setEchoMode(QLineEdit::Password);
    passwordField->setFixedHeight(48);
    passwordField->setStyleSheet("QLineEdit { background: #F5F5F5; border-radius: 8px; padding: 10px; border: none; }");

    loginButton = new QPushButton("Sign in");
    loginButton->setFixedHeight(48);
    loginButton->setStyleSheet("QPushButton { background-color: #0D47A1; color: white; border-radius: 8px; font-weight: bold; font-size: 16px; } "
                               "QPushButton:hover { background-color: #1976D2; }");

    errorLabel = new QLabel();
    errorLabel->setStyleSheet("color: #D32F2F; font-weight: bold;");
    errorLabel->setVisible(false);

    cardLayout->addWidget(titleLabel);
    cardLayout->addSpacing(20);
    cardLayout->addWidget(userField);
    cardLayout->addWidget(passwordField);
    cardLayout->addWidget(loginButton);
    cardLayout->addWidget(errorLabel);

    rightLayout->addWidget(loginCard);

    contentLayout->addWidget(leftPanel, 45);
    contentLayout->addWidget(rightPanel, 55);
    mainContainer->addWidget(background);

    // --- CONNECTIONS ---
    connect(loginButton, &QPushButton::clicked, this, &InfluencerLoginPage::attemptLogin);
    connect(backBtn, &QPushButton::clicked, this, &InfluencerLoginPage::backToStart);
}

void InfluencerLoginPage::attemptLogin() {
    // Check credentials against backend
    if (systemManager->verifyInfluencerLogin(userField->text(), passwordField->text())) {
        emit loginSuccess(userField->text());
    } else {
        errorLabel->setText("Invalid credentials or influencer not found.");
        errorLabel->setVisible(true);
    }
}

void InfluencerLoginPage::togglePasswordVisibility()
{
    passwordVisible = !passwordVisible;

    if (passwordVisible) {
        passwordField->setEchoMode(QLineEdit::Normal);
        showPasswordButton->setText("HIDE");
    } else {
        passwordField->setEchoMode(QLineEdit::Password);
        showPasswordButton->setText("SHOW");
    }
}
