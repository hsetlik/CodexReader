#ifndef VOCABVIEW_H
#define VOCABVIEW_H

#include <QWidget>
#include "codexcontent.h"
#include "flashcardview.h"
namespace Ui {
class VocabView;
}

class VocabView : public QWidget
{
    Q_OBJECT

public:
    explicit VocabView(CodexDatabase* db, QWidget *parent = nullptr);
    CodexDatabase* const linkedDatabase;
    ~VocabView();

private:
    Ui::VocabView *ui;

};

#endif // VOCABVIEW_H
