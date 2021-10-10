#ifndef LESSONLIST_H
#define LESSONLIST_H

#include <QWidget>
#include "codexdatabase.h"

namespace Ui {
class LessonList;
}

class LessonList : public QWidget
{
    Q_OBJECT

public:
    explicit LessonList(CodexDatabase* db, QWidget *parent = nullptr);
    CodexDatabase* const linkedDatabase;
    ~LessonList();

private:
    Ui::LessonList *ui;
};

#endif // LESSONLIST_H
