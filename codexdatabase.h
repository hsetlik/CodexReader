#ifndef CODEXDATABASE_H
#define CODEXDATABASE_H

#include <QObject>
#include <QSqlDatabase>

//forward declare this
class CodexDatabase;

//the base data structure for words and phrases (analogous to LingQs)
class Term
{
public:
    Term (CodexDatabase* db, QString target, QString translation);
    Term (CodexDatabase* db, QSqlRecord rec);
    CodexDatabase* const linkedDb;
private:
    QString targetStr;
    //coeff for figuring out srs stuff
    double ease;
    std::vector<QString> translations;
};


class CodexDatabase
{
public:
    CodexDatabase();
    ~CodexDatabase();
    bool attemptLogin(QString username, QString pasword);
    void addTerm(QString target, QString translation);
    //Term termFromRecord(QSqlRecord rec) { return Term(this, rec); }
private:
    void setUserDatabase(QString username);
    std::unique_ptr<QSqlDatabase> db;
    std::unique_ptr<QSqlDatabase> userDb;
};

#endif // CODEXDATABASE_H
