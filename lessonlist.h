#ifndef LESSONLIST_H
#define LESSONLIST_H

#include <QWidget>
#include <QtWidgets>
#include "codexcontent.h"
class ContentListEntry : public QWidget
{
    Q_OBJECT
public:
    explicit ContentListEntry(QString& name, QWidget* parent = nullptr);
    const QString contentName;
private:
    QVBoxLayout* vBox;
    QLabel* nameLabel;
};

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
    std::vector<ContentListEntry*> contentEntries;
};

#endif // LESSONLIST_H
