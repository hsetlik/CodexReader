#ifndef CODEXCONTENT_H
#define CODEXCONTENT_H

#include <QObject>
#include "codexdatabase.h"

class CodexContent : public QObject
{
    Q_OBJECT
public:
    struct Transcript
    {
        Transcript(const QString& fullText);
        const QString fullSource;

    };
    explicit CodexContent(CodexDatabase* db, QObject *parent = nullptr);
    CodexDatabase* const linkedDatabase;
signals:
private:
    std::vector<Term*> allTerms;

};

#endif // CODEXCONTENT_H
