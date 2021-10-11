#ifndef LESSONLIST_H
#define LESSONLIST_H

#include <QWidget>
#include <QtWidgets>
#include "codexcontent.h"
class ContentNameLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ContentNameLabel(const QString& text, QWidget* parent = nullptr);
    void mousePressEvent(QMouseEvent* e) override;
    void enterEvent(QEvent* e) override;
    void leaveEvent(QEvent* e) override;
    void paintEvent(QPaintEvent* e) override;
signals:
    void labelClicked();
private:
    QColor highlightColor;
    QColor normalColor;
    bool mouseIsOver;
};

class ContentListEntry : public QWidget
{
    Q_OBJECT
public:
    explicit ContentListEntry(QString& name, QWidget* parent = nullptr);
    const QString contentName;
    ContentNameLabel* label;
private:
    QVBoxLayout* vBox;
};

namespace Ui {
class LessonList;
}

class LessonList : public QWidget
{
    Q_OBJECT

public:
    explicit LessonList(CodexDatabase* db, QWidget *parent = nullptr);
    CodexDatabase* const linkedDatabase;
    ~LessonList();
signals:
    void openContentBrowser(QString name);
private slots:
    void contentClicked();
private:
    Ui::LessonList *ui;
    std::vector<ContentListEntry*> contentEntries;
};

#endif // LESSONLIST_H
