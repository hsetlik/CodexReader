#ifndef CODEXCONTENT_H
#define CODEXCONTENT_H

#include <QObject>
#include "codexdatabase.h"
#include <unordered_map>
typedef std::vector<std::pair<QString, Term*>> OrderedTranscript;
class FullText
    {
    public:
        FullText(const QString& fullText);
        const QString fullSource;
        OrderedTranscript getTranscript(CodexDatabase* db);
private:
        OrderedTranscript fullTranscript;
    };

class CodexContent : public QObject
{
    Q_OBJECT
public:
    explicit CodexContent(QString contentName, CodexDatabase* db, QObject *parent = nullptr);
    explicit CodexContent(QSqlRecord& rec, CodexDatabase* db, QObject *parent = nullptr);
    CodexDatabase* const linkedDatabase;
    QStringList allWords();
    std::map<QString, Term*> getFullTranscript();
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
