#include "codexdatabase.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QPluginLoader>



CodexDatabase::CodexDatabase() :
    db (QSqlDatabase::addDatabase("QMYSQL")),
    userDb (nullptr)
{
    db.setHostName ("127.0.0.1");
    db.setUserName ("root");
    db.setPassword ("Nebuchadnezzar21");
    db.setDatabaseName ("codex_vocab");
    if(db.open())
        printf ("database opened\n");
    else
        printf( "Error: database not opened\n");
}

CodexDatabase::~CodexDatabase()
{
    if(db.isOpen())
        db.close();
}

bool CodexDatabase::attemptLogin(QString username, QString password)
{
    printf ("attempting login...\n");
    QSqlQuery query("SELECT * FROM users", db);
    while (query.next())
    {
        QString usr = query.value(0).toString();
        QString pswd = query.value(1).toString();
        if (usr == username && password == pswd)
        {
            printf ("user found\n");
            setUserDatabase(username);
            return true;
        }
    }
    printf ("no matching user found\n");
    return false;
}

void CodexDatabase::setUserDatabase(QString username)
{
    userDb = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
    userDb->setHostName ("127.0.0.1");
    userDb->setUserName ("root");
    userDb->setPassword ("Nebuchadnezzar21");
    userDb->setDatabaseName (username);
    if (userDb->open())
        printf("User database opened\n");
    else
        printf("no user database!");

}

void CodexDatabase::addTerm(QString target, QString translation)
{
    auto term = new Term(this, target, translation);
    auto query = term->preparedInsertQuery(*userDb);
    if(query.exec())
        printf ("Term added\n");
    delete term;
}

