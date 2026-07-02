#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class StartPage : public QWidget
{
    Q_OBJECT

public:
    explicit StartPage(QWidget *parent = nullptr);

signals:
    void userTypeSelected(const QString &userType);

private slots:
    void onBrandClicked();
    void onInfluencerClicked(); // Added this slot

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QLabel *brandingLabel;
    QPushButton *brandButton;
    QPushButton *influencerButton;
    QLabel *introLabel;
};

#endif // STARTPAGE_H
