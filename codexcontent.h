#ifndef CODEXCONTENT_H
#define CODEXCONTENT_H

#include <QObject>
#include "codexdatabase.h"

class CodexContent : public QObject
{
    Q_OBJECT
public:
    explicit CodexContent(CodexDatabase* db, QObject *parent = nullptr);
    CodexDatabase* const linkedDatabase;

signals:

};

#endif // CODEXCONTENT_H
