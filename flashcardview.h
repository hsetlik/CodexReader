#ifndef FLASHCARDVIEW_H
#define FLASHCARDVIEW_H

#include <QWidget>
#include "srsviewers.h"

namespace Ui {
class FlashCardView;
}

class FlashCardView : public QWidget
{
    Q_OBJECT

public:
    explicit FlashCardView(CodexDatabase* db, QWidget *parent = nullptr);
    CodexDatabase* const linkedDatabase;
    ~FlashCardView();
    void toNextTerm();
    void flipCurrentCard();
    void answerCurrentTerm(int grade);
private slots:
    void on_ans1_clicked();
    void on_ans5_clicked();
    void on_ans4_clicked();
    void on_ans3_clicked();
    void on_ans2_clicked();
private:
    void keyPressEvent(QKeyEvent* event) override;
    Ui::FlashCardView *ui;
    std::vector<Term> termsToReview;
    std::unique_ptr<SrsViewer> viewer;
    void setButtonsVisible(bool shouldBeVisible);

};

#endif // FLASHCARDVIEW_H
