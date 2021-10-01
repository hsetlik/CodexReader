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
signals:
    void startFlashCards();
private slots:
    void on_viewAllButton_clicked();

    void on_addButton_clicked();

    void on_studyButton_clicked();

private:
    Ui::LessonView *ui;
};

#endif // LESSONVIEW_H
