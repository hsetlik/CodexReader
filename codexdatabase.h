#ifndef CODEXDATABASE_H
#define CODEXDATABASE_H

#include <QObject>
#include <QSqlDatabase>




class CodexDatabase
{
public:
    CodexDatabase();
    ~CodexDatabase();
    bool attemptLogin(QString username, QString pasword);
private:
    void setUserDatabase(QString username);
    std::unique_ptr<QSqlDatabase> db;
    std::unique_ptr<QSqlDatabase> userDb;
};

#endif // CODEXDATABASE_H
