#include "masterstackedwidget.h"

MasterStackedWidget::MasterStackedWidget(QWidget* parent) :
    QStackedWidget(parent),
    loginForm(new LoginForm(&database, this))
{
    connect(loginForm,
            &LoginForm::loginWithUser,
            this,
            &MasterStackedWidget::goToUserDashboard);
    addWidget(loginForm);
    setCurrentWidget(loginForm);
}


void MasterStackedWidget::goToUserDashboard(QString username)
{
    dashboard = new UserDashboard(username, &database, this);
    addWidget(dashboard);
    setCurrentWidget(dashboard);
}

