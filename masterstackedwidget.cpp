#include "masterstackedwidget.h"

MasterStackedWidget::MasterStackedWidget(QWidget* parent) :
    QStackedWidget(parent),
    loginForm(new LoginForm(&database, this))
{
    addWidget(loginForm);
    setCurrentWidget(loginForm);
}
