#ifndef BRANDLOGINPAGE_H
#define BRANDLOGINPAGE_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QLabel;
class QCheckBox;

#include "include/SystemManager.h"

class BrandLoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit BrandLoginPage(SystemManager *manager, QWidget *parent = nullptr);

signals:
    void loginSuccess();
    void backToStart();

private slots:
    void attemptLogin();
    void togglePasswordVisibility();

private:
    QLineEdit *emailField;
    QLineEdit *passwordField;
    QPushButton *loginButton;
    QPushButton *showPasswordButton;
    QLabel *errorLabel;
    QCheckBox *rememberMeCheckbox;
    bool passwordVisible;
    SystemManager *systemManager;
};

#endif // BRANDLOGINPAGE_H
