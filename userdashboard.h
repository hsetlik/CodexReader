#ifndef USERDASHBOARD_H
#define USERDASHBOARD_H

#include <QWidget>
#include "importview.h"
#include "lessonview.h"
#include "vocabview.h"
#include "statsview.h"


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
signals:
    void flashCardStart();

private slots:
    void on_tabWidget_currentChanged(int index);
    void sendFlashCardStart()
    {
        emit flashCardStart();
    }

public:
    Ui::UserDashboard *ui;
    ImportView* importView;
    LessonView* lessonView;
    VocabView* vocabView;
    StatsView* statsView;
};

#endif // USERDASHBOARD_H
