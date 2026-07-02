#include "StartPage.h"
#include <QGridLayout>
#include <QFont>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFontMetrics>

StartPage::StartPage(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QWidget *contentWidget = new QWidget(this);
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setAlignment(Qt::AlignCenter);
    contentLayout->setSpacing(20);
    contentLayout->setContentsMargins(100, 150, 100, 100);
    contentWidget->setStyleSheet("background: transparent;");

    this->setStyleSheet("background-color: #F8F8F8;");

    // 1. --- Heading --- //
    brandingLabel = new QLabel("Influencer Collab Manager", this);
    QFont headingFont("Times New Roman", 48, QFont::Bold);
    brandingLabel->setFont(headingFont);
    brandingLabel->setStyleSheet("color: #333333; letter-spacing: 2px; background: transparent;");
    brandingLabel->setAlignment(Qt::AlignCenter);

    // 2. --- Introduction Text --- //
    QString fullText = "Our system is designed to be the ultimate, hassle-free tool for managing brand partnerships, "
                       "drawing inspiration from industry leaders like Meta's Brand Collab Manager, but focusing on clean efficiency.";

    introLabel = new QLabel(fullText, this);
    introLabel->setWordWrap(true);
    introLabel->setAlignment(Qt::AlignCenter);
    introLabel->setStyleSheet("color: #666666; font-size: 17px; background: transparent;");

    int textMaxWidth = 700;
    introLabel->setFixedWidth(textMaxWidth);
    introLabel->setMinimumHeight(80);

    // 3. --- Button Section --- //
    QWidget *buttonContainer = new QWidget(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->setSpacing(20);
    buttonLayout->setAlignment(Qt::AlignCenter);
    buttonContainer->setStyleSheet("background: transparent;");

    brandButton = new QPushButton("Sign in as Brand", this);
    influencerButton = new QPushButton("Sign in as Influencer", this);

    QString buttonStyleBase = "QPushButton { "
                              "padding: 15px 40px; font-size: 18px; font-weight: bold; border-radius: 30px; "
                              "min-width: 180px; }";

    brandButton->setStyleSheet(buttonStyleBase +
                               "background-color: #4C69BA; color: white; border: none; }"
                               "QPushButton:hover { background-color: #5D7ACB; }");

    influencerButton->setStyleSheet(buttonStyleBase +
                                    "background-color: white; color: #4C69BA; border: 2px solid #4C69BA; }"
                                    "QPushButton:hover { background-color: #E0F7FA; border-color: #4C69BA; }");

    brandButton->setCursor(Qt::PointingHandCursor);
    influencerButton->setCursor(Qt::PointingHandCursor);

    buttonLayout->addWidget(brandButton);
    buttonLayout->addWidget(influencerButton);

    // 4. --- Add Widgets into Layout --- //
    contentLayout->addWidget(brandingLabel);
    contentLayout->addSpacing(15);
    contentLayout->addWidget(introLabel, 0, Qt::AlignCenter);
    contentLayout->addSpacing(100);
    contentLayout->addWidget(buttonContainer, 0, Qt::AlignCenter);
    contentLayout->addStretch();

    mainLayout->addWidget(contentWidget);

    // --- Connections --- //
    connect(brandButton, &QPushButton::clicked, this, &StartPage::onBrandClicked);
    // FIXED: Added connection for Influencer button
    connect(influencerButton, &QPushButton::clicked, this, &StartPage::onInfluencerClicked);
}

void StartPage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int w = width();
    int h = height();

    QLinearGradient gradient(0, h * 0.4, w, h);
    gradient.setColorAt(0.0, QColor("#6A89FF"));
    gradient.setColorAt(1.0, QColor("#4C69BA"));

    QPainterPath path;
    path.moveTo(0, h * 0.55);
    path.cubicTo(w * 0.25, h * 0.3, w * 0.5, h * 0.75, w * 0.8, h * 0.6);
    path.cubicTo(w * 0.9, h * 0.5, w * 1.0, h * 0.75, w, h * 0.7);
    path.lineTo(w, h);
    path.lineTo(0, h);
    path.closeSubpath();

    painter.fillPath(path, QBrush(gradient));

    QWidget::paintEvent(event);
}

void StartPage::onBrandClicked()
{
    emit userTypeSelected("Brand");
}

// FIXED: Implemented slot to navigate to Influencer Login
void StartPage::onInfluencerClicked()
{
    emit userTypeSelected("Influencer");
}
