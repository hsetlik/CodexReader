#ifndef WORDLABEL_H
#define WORDLABEL_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QColor>
#include "codexcontent.h"
//Word Statuses range from 1 (unknown) to 5 (perfect recall)
class CodexLabelBase : public QLabel
{
    Q_OBJECT
public:
    explicit CodexLabelBase(QWidget* parent = nullptr) : QLabel(parent)
    {
       setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    }
signals:
    void wordClicked(QString text);
protected:
    QColor background;

};

class SeenTermLabel : public CodexLabelBase
{
    Q_OBJECT
public:
    SeenTermLabel(Term* term,QWidget* parent = nullptr);
    Term* const parentTerm;
    void paintEvent (QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* e) override;
    static QColor colorForEase(float ease);
public slots:
    void setEase(int ease);
signals:
    void easeChanged(int ease);
private:
   float ease;
};
class NewTermLabel : public CodexLabelBase
{
    Q_OBJECT
public:
    explicit NewTermLabel(const QString& word, QWidget* parent = nullptr);
    void paintEvent (QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* e) override;

};

#endif // WORDLABEL_H
