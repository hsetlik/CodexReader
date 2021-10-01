#include "srsviewers.h"
#include <QtWidgets>
SrsViewer::SrsViewer(Term* src, QWidget *parent) :
    QWidget(parent),
    sourceTerm(src)
{
    layout = new QVBoxLayout;
    setLayout(layout);
}

SrsType SrsViewer::getSrsType()
{
    //seed random number generator
    std::srand(std::time(nullptr));
    float rBasic, rTypeIn, rCloze;
    if (sourceTerm->isSingleWord()) // don't have cloze as an option for single words
    {
        rBasic = ((float) arc4random() / (float)RAND_MAX) * 0.7f;
        rTypeIn = ((float) arc4random() /(float) RAND_MAX) * 0.3f;
        return (rBasic > rTypeIn) ? SrsType::Basic : SrsType::TypeIn;
    }
    else
    {
        rBasic = ((float) arc4random() / (float)RAND_MAX) * 0.5f;
        rTypeIn = ((float) arc4random() / (float)RAND_MAX) * 0.2f;
        rCloze = ((float) arc4random() / (float)RAND_MAX) * 0.3f;
        if (rBasic > rTypeIn && rBasic > rCloze)
            return Basic;
        else if (rTypeIn > rBasic && rTypeIn > rCloze)
            return TypeIn;
        else
            return Cloze;

    }
}
//=============================================================
BasicViewer::BasicViewer(Term* term, QWidget* parent) : SrsViewer(term, parent)
{
    auto targetWord = term->getTarget();
    auto targetLabel = new QLabel(targetWord, this);
    layout->addWidget(targetLabel);
}

void BasicViewer::flip()
{
    auto translations = sourceTerm->getTranslations();
    QString tStr = "";
    for (auto& t : translations)
    {
        tStr += t + ", ";
    }
    tStr.chop(2);
    auto tLabel = new QLabel(tStr, this);
    layout->addWidget(tLabel);
    emit cardFlipped();
}
//=============================================================
TypeInViewer::TypeInViewer(Term* term, QWidget* parent) : SrsViewer(term, parent)
{

}
void TypeInViewer::flip()
{

}
//=============================================================
ClozeViewer::ClozeViewer(Term* term, QWidget* parent) : SrsViewer(term, parent)
{

}
void ClozeViewer::flip()
{

}
