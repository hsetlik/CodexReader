#include "flashcardview.h"
#include "ui_flashcardview.h"

FlashCardView::FlashCardView(CodexDatabase *db, QWidget *parent) :
    QWidget(parent),
    linkedDatabase(db),
    ui(new Ui::FlashCardView)
{
    ui->setupUi(this);
    linkedDatabase->termsDueNow(termsToReview);
}

FlashCardView::~FlashCardView()
{
    delete ui;
}

bool FlashCardView::toNextTerm() // returns true if 1 or more due terms left
{
    termsToReview.erase(termsToReview.begin());
    if (termsToReview.begin() == termsToReview.end())
        return false;
    else
    {

    }
}

void FlashCardView::on_ans1_clicked()
{

}
void FlashCardView::on_ans2_clicked()
{

}
void FlashCardView::on_ans3_clicked()
{

}
void FlashCardView::on_ans4_clicked()
{

}
void FlashCardView::on_ans5_clicked()
{

}



