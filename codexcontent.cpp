#include "codexcontent.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

Term::Term (CodexDatabase* db, QString target, QString translation) :
    linkedDb(db),
    targetStr(target),
    ease(2.5f)
{
    translations.push_back(translation);
}

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


CodexContent::CodexContent(CodexDatabase* db, QObject *parent) :
    QObject(parent),
    linkedDatabase(db)
{

}

