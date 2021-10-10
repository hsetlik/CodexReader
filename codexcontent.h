#ifndef CODEXCONTENT_H
#define CODEXCONTENT_H

#include <QObject>
#include "codexdatabase.h"

class CodexContent : public QObject
{
    Q_OBJECT
public:
    struct FullText
    {
        FullText(const QString& fullText);
        const QString fullSource;
    };
    explicit CodexContent(QString contentName, CodexDatabase* db, QObject *parent = nullptr);
    explicit CodexContent(QSqlRecord& rec, CodexDatabase* db, QObject *parent = nullptr);
    CodexDatabase* const linkedDatabase;
signals:
private:
    QString name;
    int contentIdx;
    bool hasAudio;
    bool hasVideo;
    QString url;
    std::vector<Term*> seenTerms;
    std::vector<QString> newTerms; //save words that don't yet have associated terms in the DB

};

#endif // CODEXCONTENT_H
