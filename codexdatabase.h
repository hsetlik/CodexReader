#ifndef CODEXDATABASE_H
#define CODEXDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDateTime>
#define MAX_EASE 3.5f
//forward declare so terms can be liked to a parent
class CodexDatabase;
//the base data structure for words and phrases (analogous to LingQs)
class Term
{
public:
    Term (CodexDatabase* db, QString target, QString translation);
    Term (CodexDatabase* db, QSqlRecord rec);
    Term (const Term& other);
    CodexDatabase* linkedDb;
    QString sqlInsertCommand();

    QSqlQuery preparedInsertQuery(QSqlDatabase& db);
    void answerSM2(int grade); // implements SuperMemo SM-2 algorithm as described https://en.wikipedia.org/wiki/SuperMemo#Description_of_SM-2_algorithm
    bool isSingleWord() {return !targetStr.contains(' ');}
    QString getTarget() {return targetStr; }
    QSqlQuery preparedUpdateQuery(QSqlDatabase& db);
    std::vector<QString> getTranslations() {return translations; }
    float getNormalizedEase();
private:
    QString targetStr;
    void bindValuesToQuery(QSqlQuery& query);
    int getIntervalFor(int grade);
    void setDueAfter(int days);
    //coeff for figuring out srs stuff
    double ease; //ease factor for algorithm
    int reps; //number of times this term has been repeated
    int interval; //last delay interval in # of days
    std::vector<QString> translations;
    QDate dateDue;
};
struct SqlUtil
{
    static void setSafeMode(QSqlDatabase& db, bool isSafe);
};

class CodexDatabase
{
public:
    CodexDatabase();
    ~CodexDatabase();
    bool attemptLogin(QString username, QString pasword);
    void addTerm(QString target, QString translation);
    QString sqlSelectCommand(const QString& word);
    Term* getTerm(const QString& word);
    void termsDueNow(std::vector<Term>& terms);
    void updateTerm(Term* term);
    QString sqlSelectDueTerms();
    QSqlDatabase& currentDatabase() {return db; }
    QSqlDatabase& currentUserDatabase() {return *userDb; }
    QString fullContentText(QString name);
    std::vector<QString> getContentNames();
    QSqlRecord getContentRecord(const QString& name);
    std::vector<QSqlRecord> allLessonRecords();
private:
    std::vector<Term*> getAllTerms();
    void setUserDatabase(QString username);
    QSqlDatabase db;
    QSqlDatabase* userDb;
};

#endif // CODEXDATABASE_H
