#include "codexcontent.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

Term::Term (CodexDatabase* db, QString target, QString translation) :
    linkedDb(db),
    targetStr(target),
    ease(2.5f),
    reps(0)
{
    translations.push_back(translation);
}

Term::Term (CodexDatabase* db, QSqlRecord rec) : linkedDb(db)
{
    targetStr = rec.value("target").toString();
    ease = rec.value("ease").toDouble();
    reps = rec.value("reps").toInt();
    auto numTranslations = rec.value("numTranslations").toInt();
    for (int i = 0; i < numTranslations; ++i)
    {
        QString name = "tran" + QString::number(i);
        auto value = rec.value(name).toString();
        translations.push_back(value);
    }
}

// syntax:
// INSERT INTO terms(target, numTranslations, tran0, ease, reps);
// VALUES(target, numTranslations, tran0, ease, reps);
QString Term::sqlInsertCommand()
{
    QString insertStr = "INSERT INTO terms(target, numTranslations,";
    for (int i = 0; i < (int)translations.size(); ++i)
    {
        QString tStr = "tran" + QString::number(i);
        insertStr += tStr + ", ";
    }
    insertStr += "ease, reps)";
    QString valueStr = "VALUES(";
    valueStr += ":target, :numTranslations, ";
    for (int i = 0; i < (int)translations.size(); ++i)
    {
        auto tStr = ":tran" + QString::number(i) + ", ";
        valueStr += tStr;
    }
    valueStr += ":ease, :reps);";
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
 }

//===================================================================
CodexContent::CodexContent(CodexDatabase* db, QObject *parent) :
    QObject(parent),
    linkedDatabase(db)
{

}

