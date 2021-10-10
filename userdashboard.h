#ifndef USERDASHBOARD_H
#define USERDASHBOARD_H

#include <QWidget>
#include "importview.h"
#include "plainflashcardaddition.h"
#include "vocabview.h"
#include "statsview.h"
#include "lessonlist.h"


namespace Ui {
class UserDashboard;
}

class UserDashboard : public QWidget
{
    Q_OBJECT

public:
    explicit UserDashboard(QString usr, CodexDatabase* db, QWidget *parent = nullptr);
    ~UserDashboard();
    CodexDatabase* const linkedDatabase;
    const QString username;
private slots:
    void on_tabWidget_currentChanged(int index);
    void on_profileButton_clicked();

    void on_settingsButton_clicked();

public:
    Ui::UserDashboard *ui;
    ImportView* importView;
    VocabView* vocabView;
    StatsView* statsView;
    LessonList* lessonList;
};

#endif // USERDASHBOARD_H
