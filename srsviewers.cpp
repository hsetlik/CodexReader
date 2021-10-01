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
    auto translations = sourceTerm->getTranslations();
    QString tStr = "";
    for (auto& t : translations)
    {
        tStr += t + ", ";
    }
    tStr.chop(2);
    auto tLabel = new QLabel(tStr, this);
    layout->addWidget(tLabel);
    editBox = new QLineEdit(this);
    layout->addWidget(editBox);
}
void TypeInViewer::flip()
{
    auto usrWord = editBox->text();
    auto usrLabel = new QLabel(usrWord, this);
    layout->removeWidget(editBox);
    layout->addWidget(usrLabel);
    auto targetLabel = new QLabel(sourceTerm->getTarget(), this);
    layout->addWidget(targetLabel);
}
//=============================================================
ClozeViewer::ClozeViewer(Term* term, QWidget* parent) : SrsViewer(term, parent)
{
    auto fullPhrase = sourceTerm->getTarget();
    auto allWords = fullPhrase.split(' ');
    auto clozeIdx = arc4random() % (int)(allWords.size() - 1);
    clozeWord = allWords[clozeIdx];
    auto clozeBytes = clozeWord.toLatin1();
    auto spaceString = clozeWord;
    spaceString.fill(' ');
    fullPhrase.replace(clozeWord, spaceString);
    fullLabel = new QLabel(fullPhrase, this);
    layout->addWidget(fullLabel);
    editBox = new QLineEdit(this);
    layout->addWidget(editBox);
}
void ClozeViewer::flip()
{
    auto userStr = editBox->text();
    layout->removeWidget(editBox);
    userLabel = new QLabel(userStr, this);
    clozeLabel = new QLabel(clozeWord, this);
    layout->addWidget(userLabel);
    layout->addWidget(clozeLabel);
}
