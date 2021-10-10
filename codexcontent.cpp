#include "codexcontent.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>

CodexContent::FullText::FullText(const QString& fullText) :
    fullSource(fullText)
{
    auto strings = fullSource.split(" ");

}
//===================================================================
CodexContent::CodexContent(QString contentName, CodexDatabase* db, QObject *parent) :
    QObject(parent),
    linkedDatabase(db)
{
    auto fullText = linkedDatabase->fullContentText(contentName);
    auto allWords = fullText.split(' ');
    for (auto& word : allWords)
    {
        auto term = linkedDatabase->getTerm(word);
        if (term != nullptr)
           seenTerms.push_back(term);
        else
            newTerms.push_back(word);
    }
}

