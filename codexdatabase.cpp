#include "codexdatabase.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QPluginLoader>

Term::Term (CodexDatabase* db, QString target, QString translation) :
    linkedDb(db),
    targetStr(target),
    ease(2.5f),
    reps(0),
    interval(1),
    dateDue(QDate::currentDate())
{
    translations.push_back(translation);
}

Term::Term (CodexDatabase* db, QSqlRecord rec) : linkedDb(db)
{
    targetStr = rec.value("target").toString();
    ease = rec.value("ease").toDouble();
    reps = rec.value("reps").toInt();
    interval = rec.value("interval").toInt();
    dateDue = rec.value("date_due").toDate();
    qDebug() << "Due Date is: " << dateDue;
    auto numTranslations = rec.value("numTranslations").toInt();
    for (int i = 0; i < numTranslations; ++i)
    {
        QString name = "tran" + QString::number(i);
        auto value = rec.value(name).toString();
        translations.push_back(value);
    }
}

// syntax:
// INSERT INTO terms(target, numTranslations, tran0, ease, reps, delay_interval, date_due);
// VALUES(target, numTranslations, tran0, ease, reps, delay_interval, date_due);
QString Term::sqlInsertCommand()
{
    QString insertStr = "INSERT INTO terms(target, numTranslations, ";
    for (int i = 0; i < (int)translations.size(); ++i)
    {
        QString tStr = "tran" + QString::number(i);
        insertStr += tStr + ", ";
    }
    insertStr += "ease, reps, delay_interval, date_due)";
    QString valueStr = "VALUES(";
    valueStr += ":target, :numTranslations, ";
    for (int i = 0; i < (int)translations.size(); ++i)
    {
        auto tStr = ":tran" + QString::number(i) + ", ";
        valueStr += tStr;
    }
    valueStr += ":ease, :reps, :delay_interval, :date_due);";
    return insertStr + valueStr;
}
 QSqlQuery Term::preparedInsertQuery(QSqlDatabase& db)
 {
     QSqlQuery query(db);
     query.prepare(sqlInsertCommand());
     bindValuesToQuery(query);
     return query;
 }

 void Term::bindValuesToQuery(QSqlQuery& query)
 {
     query.bindValue(":target", targetStr);
     query.bindValue(":numTranslations", (int)translations.size());
     for (int i = 0; i < (int)translations.size(); ++i)
     {
         auto str = ":tran" + QString::number(i);
         query.bindValue(str, translations[i]);
     }
     query.bindValue(":ease", ease);
     query.bindValue("reps", reps);
     query.bindValue(":delay_interval", interval);
     query.bindValue(":date_due", dateDue);
 }
 //returns the SM-2's delay length for a certain grade without updating the term's variables
 int Term::getIntervalFor(int grade)
 {
     if (grade >= 3)
     {
         if (reps == 0)
             return 1;
         else if (reps == 1)
             return 5;
         else
             return (int)std::floor((double)interval * ease);
     }
     return 1;
 }
 QString CodexDatabase::sqlSelectCommand(const QString& word)
 {
     return "SELECT * FROM terms WHERE target = " + word + ";";
 }

 void Term::answerSM2(int grade)
 {
     interval = getIntervalFor(grade);
     if (grade >= 3)
         ++reps;
     else
         reps = 0;
     auto dEase = (0.1f - (float)(5.0f - grade) * (0.08f + (float)(5 - grade) * 0.02f));
     ease += dEase;
 }


//============================================================

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
    auto term = new Term (this, target, translation);
    auto query = term->preparedInsertQuery (*userDb);
    if (query.exec())
        printf ("Term added\n");
    delete term;
}
//don't call this on an actual big database ofc
std::vector<Term*> CodexDatabase::getAllTerms()
{
    std::vector<Term*> output;
    QSqlQuery query("SELECT * FROM terms;", db);
    while (query.next())
    {
        auto record = query.record();
        output.push_back(new Term(this, record));
    }
    return output;
}

Term* CodexDatabase::getTerm(const QString& word)
{
    //TODO: figure out whether this is fast enough and what can be done if not
    auto cmd = sqlSelectCommand(word);
    QSqlQuery query(cmd, db);
    while (query.next())
    {
        auto rec = query.record();
        if (rec.value("target").toString() == word)
        {
            return new Term(this, rec);
        }
    }
    return nullptr;
}


