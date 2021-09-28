#ifndef CODEXDATABASE_H
#define CODEXDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
//the base data structure for words and phrases (analogous to LingQs)
class CodexDatabase;
class Term
{
public:
    Term (CodexDatabase* db, QString target, QString translation);
    Term (CodexDatabase* db, QSqlRecord rec);
    CodexDatabase* const linkedDb;
    QString sqlInsertCommand();
    QSqlQuery preparedInsertQuery(QSqlDatabase& db);
private:
    QString targetStr;
    void bindValuesToQuery(QSqlQuery& query);
    //coeff for figuring out srs stuff
    double ease;
    int reps;
    std::vector<QString> translations;
};

class CodexDatabase
{
public:
    CodexDatabase();
    ~CodexDatabase();
    bool attemptLogin(QString username, QString pasword);
    void addTerm(QString target, QString translation);
private:
    void setUserDatabase(QString username);
    std::unique_ptr<QSqlDatabase> db;
    std::unique_ptr<QSqlDatabase> userDb;
};

#endif // CODEXDATABASE_H
