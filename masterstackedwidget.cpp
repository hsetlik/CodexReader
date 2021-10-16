#include "masterstackedwidget.h"
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

MasterStackedWidget::MasterStackedWidget(QWidget* parent) :
    QStackedWidget(parent),
    loginForm(new LoginForm(&database, this)),
    currentContent(nullptr),
    reader(nullptr)
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

void MasterStackedWidget::loadContent(QString name)
{
    if (currentContent != nullptr)
        delete currentContent;
    auto rec = database.getContentRecord(name);
    currentContent = new CodexContent(rec, &database, this);
    printf("Content Loaded\n");
    openContent(currentContent);
}
void MasterStackedWidget::goToUserDashboard(QString username)
{
    dashboard = new UserDashboard(username, &database, this);
    addWidget(dashboard);
    connect(dashboard->lessonList, &LessonList::openContentBrowser, this, &MasterStackedWidget::openContentBrowser);
    setCurrentWidget(dashboard);

}
void MasterStackedWidget::finishFlashCards()
{
    setCurrentWidget(dashboard);
}

void MasterStackedWidget::openContentBrowser(QString name)
{
    loadContent(name);

}
void MasterStackedWidget::openContent(CodexContent* cont)
{
   if (reader != nullptr)
       delete reader;
   reader = new ContentReaderWidget(cont, this);
   addWidget(reader);
   setCurrentWidget(reader);
}
