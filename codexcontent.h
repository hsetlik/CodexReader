#ifndef CODEXCONTENT_H
#define CODEXCONTENT_H

#include <QObject>
#include "codexdatabase.h"

//the base data structure for words and phrases (analogous to LingQs)
class Term
{
public:
    Term (CodexDatabase* db, QString target, QString translation);
    Term (CodexDatabase* db, QSqlRecord rec);
    CodexDatabase* const linkedDb;
private:
    QString targetStr;
    //coeff for figuring out srs stuff
    double ease;
    std::vector<QString> translations;
};

class CodexContent : public QObject
{
    Q_OBJECT
public:
    explicit CodexContent(CodexDatabase* db, QObject *parent = nullptr);
    CodexDatabase* const linkedDatabase;

signals:

};

#endif // CODEXCONTENT_H
