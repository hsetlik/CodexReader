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
    linkedDatabase(db),
    name(contentName)
{
    auto rec = linkedDatabase->getContentRecord(name);
    contentIdx = rec.value("content_idx").toInt();
    hasAudio = rec.value("has_audio").toBool();
    hasVideo = rec.value("has_video").toBool();
    url = rec.value("url").toString();
    auto fullText = rec.value("full_text").toString();
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


CodexContent::CodexContent(QSqlRecord& rec, CodexDatabase* db, QObject *parent) :
    QObject(parent),
    linkedDatabase(db)
{
    contentIdx = rec.value("content_idx").toInt();
    hasAudio = rec.value("has_audio").toBool();
    hasVideo = rec.value("has_video").toBool();
    url = rec.value("url").toString();
    auto fullText = rec.value("full_text").toString();
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
