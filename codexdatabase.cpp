#include "codexdatabase.h"
#include <QSqlQuery>
#include <QVariant>
#include <QPluginLoader>



CodexDatabase::CodexDatabase() :
    db (QSqlDatabase::addDatabase("QMYSQL")),
    userDb (nullptr)
{
    auto driverName = db.driverName().toStdString().c_str();
    printf("Driver is: %s\n", driverName);
    QPluginLoader loader;
    loader.setFileName("/Users/hayden/Qt/5.15.2/clang_64/plugins/sqldrivers/libqsqlmysql");
    if (loader.load())
        printf("Plugin loaded\n");
    else
    {
       auto errorStr = loader.errorString().toStdString();
       printf("Failed with error: %s\n", errorStr.c_str());
    }

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
    QSqlQuery query(db);
    if (query.prepare("USE :dbName;"))
    {
        query.bindValue(":dbName", username);
        if (query.exec())
            printf("User database set\n");
    }
    else
        printf("query not prepared\n");

}

void CodexDatabase::addTerm(QString target, QString translation)
{
    auto term = new Term(this, target, translation);
    auto query = term->preparedInsertQuery(db);
    if(query.exec())
        printf ("Term added\n");
    delete term;
}

