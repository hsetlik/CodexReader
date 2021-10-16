#include "codexcontent.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
FullText::FullText(const QString& fullText) :
    fullSource(fullText)
{

}
OrderedTranscript FullText::getTranscript(CodexDatabase* db)
{
    OrderedTranscript transcript;
    auto strings = fullSource.split(" ");
    for (auto& word : strings)
    {
        auto trm = db->getTerm(word);
        auto pair = std::make_pair(word, trm);
        transcript.push_back(pair);

    }
    return transcript;
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
    name = rec.value("content_name").toString();
    qDebug() << "Content URL: " << url;
    auto fullText = rec.value("full_text").toString();
    auto fullTextType = rec.value("full_text").type();
    if (rec.isNull("full_text"))
        printf("SQL Record is null!\n");
    qDebug() << "Full Text Type: " << fullTextType;
    qDebug() << "Full Content Text: " << fullText;
    auto allWords = fullText.split(' ');
    for (auto& word : allWords)
    {
        auto term = linkedDatabase->getTerm(word);
        if (term != nullptr)
        {
           seenTerms.push_back(term);
           qDebug() << "Seen Term: " << word;
        }
        else
        {
            qDebug() << "New Term: " << word;
            newTerms.push_back(word);
        }
    }
}

QStringList CodexContent::allWords()
{
    auto rec = linkedDatabase->getContentRecord(name);
    auto fullText = rec.value("full_text").toString();
    return fullText.split(' ');
}

std::map<QString, Term*> CodexContent::getFullTranscript()
{
    std::map<QString, Term*> uMap;
    auto words = allWords();
    for (auto& word : words)
    {
        auto term = linkedDatabase->getTerm(word);
        uMap[word] = term;
    }
    return uMap;
}
