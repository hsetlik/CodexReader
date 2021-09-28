#ifndef LESSONVIEW_H
#define LESSONVIEW_H

#include <QWidget>
#include "codexcontent.h"

namespace Ui {
class LessonView;
}

class LessonView : public QWidget
{
    Q_OBJECT

public:
    explicit LessonView(CodexDatabase* db, QWidget *parent = nullptr);
    CodexDatabase* const linkedDatabase;
    ~LessonView();

private:
    Ui::LessonView *ui;
};

#endif // LESSONVIEW_H
