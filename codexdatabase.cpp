#include "codexdatabase.h"
#include <QSqlQuery>
#include <QVariant>

Term::Term (CodexDatabase* db, QString target, QString translation) :
    linkedDb(db),
    targetStr(target),
    ease(2.5f)
{
    translations.push_back(translation);
}
/*
Term::Term (CodexDatabase* db, QSqlRecord rec) : linkedDb(db)
{
    targetStr = rec.value("target").toString();
    ease = rec.value("ease").toDouble();
    auto numTranslations = rec.value("numTranslations").toInt();
    for (int i = 0; i < numTranslations; ++i)
    {
        QString name = "tran" + QString::number(i);
        auto value = rec.value(name).toString();
        translations.push_back(value);
    }

}
*/


CodexDatabase::CodexDatabase() :
    db (nullptr),
    userDb (nullptr)
{
    db.reset (new QSqlDatabase(QSqlDatabase::addDatabase ("QMYSQL")));
    db->setHostName ("127.0.0.1");
    db->setUserName ("root");
    db->setPassword ("Nebuchadnezzar21");
    db->setDatabaseName ("codex_vocab");
    if(db->open())
        printf ("database opened\n");
}

CodexDatabase::~CodexDatabase()
{
    if(db->isOpen())
        db->close();
}

bool CodexDatabase::attemptLogin(QString username, QString password)
{
    printf ("attempting login...\n");
    QSqlQuery query("SELECT * FROM users", *db);
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
    userDb.reset(new QSqlDatabase(QSqlDatabase::addDatabase(username)));
}

void CodexDatabase::addTerm(QString target, QString translation)
{
    /*
    QSqlQuery query(*userDb);
    auto command = "INSERT INTO terms(target, numTranslations, tran0, ease) VALUES(?, ?, ?)";
    query.prepare(command);
    query.addBindValue(target);
    query.addBindValue(1);
    query.addBindValue(translation);
    query.addBindValue(2.5f);
    query.exec();
    */
}
