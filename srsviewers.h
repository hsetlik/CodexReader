#ifndef SRSVIEWERS_H
#define SRSVIEWERS_H

#include <QObject>
#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include "codexcontent.h"

//abstract base class for card viewers
enum SrsType
{
    Basic,
    TypeIn,
    Cloze  //make sure only terms w/ multiple words get cloze cards
};

class SrsViewer : public QWidget
{
    Q_OBJECT
public:
    explicit SrsViewer(Term* src, QWidget *parent = nullptr);
    virtual ~SrsViewer();
    Term* const sourceTerm;
    static SrsType getSrsType(Term* term);
    //note: this always needs to emit cardFlipped();
    virtual void flip()=0;
signals:
    void cardFlipped();
protected:
    QVBoxLayout* layout;
};

class BasicViewer : public SrsViewer
{
    Q_OBJECT
public:
    explicit BasicViewer(Term* term, QWidget* parent = nullptr);
    void flip() override;
};

class TypeInViewer : public SrsViewer
{
    Q_OBJECT
public:
    explicit TypeInViewer(Term* term, QWidget* parent = nullptr);
    void flip() override;
private:
    QLineEdit* editBox;
};
class ClozeViewer : public SrsViewer
{
    Q_OBJECT
public:
    explicit ClozeViewer(Term* term, QWidget* parent = nullptr);
    void flip() override;
private:
    QString clozeWord;
    QLineEdit* editBox;
    QLabel* fullLabel;
    QLabel* userLabel;
    QLabel* clozeLabel;
};

struct ViewerFactory
{
    static SrsViewer* viewerFor(Term* term, QWidget* parent=nullptr);
};


#endif // SRSVIEWERS_H
