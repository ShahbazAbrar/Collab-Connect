#ifndef INFLUENCERLOGINPAGE_H
#define INFLUENCERLOGINPAGE_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QLabel;
class QCheckBox;

#include "include/SystemManager.h"

class InfluencerLoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit InfluencerLoginPage(SystemManager *manager, QWidget *parent = nullptr);

signals:
    void loginSuccess(QString username);
    void backToStart();

private slots:
    void attemptLogin();
    void togglePasswordVisibility();

private:
    QLineEdit *userField;
    QLineEdit *passwordField;
    QPushButton *loginButton;
    QPushButton *showPasswordButton;
    QLabel *errorLabel;
    QCheckBox *rememberMeCheckbox;
    bool passwordVisible;
    SystemManager *systemManager;
};

#endif // INFLUENCERLOGINPAGE_H
