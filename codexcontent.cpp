#include "codexcontent.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>


CodexContent::Transcript::Transcript(const QString& fullText) :
    fullSource(fullText)
{
    auto strings = fullSource.split(" ");

}
//===================================================================
CodexContent::CodexContent(CodexDatabase* db, QObject *parent) :
    QObject(parent),
    linkedDatabase(db)
{

}

