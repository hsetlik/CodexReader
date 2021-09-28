#ifndef MASTERSTACKEDWIDGET_H
#define MASTERSTACKEDWIDGET_H

#include <QStackedWidget>
#include <QObject>
#include <QWidget>
#include "loginform.h"
#include "userdashboard.h"

class MasterStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    MasterStackedWidget(QWidget* parent = nullptr);
private:
    CodexDatabase database;
    LoginForm* loginForm;
    UserDashboard* dashboard;
private slots:
    void goToUserDashboard(QString username);
};

#endif // MASTERSTACKEDWIDGET_H
