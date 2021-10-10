#ifndef LESSONVIEW_H
#define LESSONVIEW_H

#include <QWidget>
#include "codexcontent.h"

namespace Ui {
class PlainFlashcardAddition;
}

class PlainFlashcardAddition : public QWidget
{
    Q_OBJECT

public:
    explicit PlainFlashcardAddition(CodexDatabase* db, QWidget *parent = nullptr);
    CodexDatabase* const linkedDatabase;
    ~PlainFlashcardAddition();
signals:
    void startFlashCards();
private slots:
    void on_viewAllButton_clicked();

    void on_addButton_clicked();

    void on_studyButton_clicked();

private:
    Ui::PlainFlashcardAddition *ui;
};

#endif // LESSONVIEW_H
