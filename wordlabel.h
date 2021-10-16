#ifndef WORDLABEL_H
#define WORDLABEL_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QColor>
#include "codexcontent.h"
//Word Statuses range from 1 (unknown) to 5 (perfect recall)
class WordLabel : public QLabel
{
    Q_OBJECT
public:
    WordLabel(Term* term,QWidget* parent = nullptr);
    Term* const parentTerm;
    void paintEvent (QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* e) override;
    static QColor colorForEase(float ease);
public slots:
    void setEase(int ease);
signals:
    void easeChanged(int ease);
    void wordClicked(QString str);
private:
   float ease;
   QColor background;



};

#endif // WORDLABEL_H
