#include "masterstackedwidget.h"
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

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
    if (loginForm->hasKeychain())
    {
        auto dir = QDir::current();
        auto path = dir.filePath("codex_keychain.json");
        QFile file(path);
        file.open(QIODevice::ReadWrite);
        QByteArray bytes = file.readAll();
        file.close();
        auto doc = QJsonDocument::fromJson(bytes);
        auto obj = doc.object();
        auto usr = obj["User"].toString();
        auto pswd = obj["Password"].toString();
        if (obj["UseKeychain"].toBool()
                &&
                database.attemptLogin(usr, pswd))
            goToUserDashboard(usr);
    }
}


void MasterStackedWidget::goToUserDashboard(QString username)
{
    dashboard = new UserDashboard(username, &database, this);
    addWidget(dashboard);
    setCurrentWidget(dashboard);
}

