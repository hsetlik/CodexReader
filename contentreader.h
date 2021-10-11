#ifndef CONTENTREADER_H
#define CONTENTREADER_H
#include "codexcontent.h"
#include <QWidget>

class ContentReader : public QWidget
{
    Q_OBJECT
public:
    explicit ContentReader(CodexContent* cont, QWidget *parent = nullptr);
    CodexContent* const linkedContent;

signals:

};

#endif // CONTENTREADER_H
