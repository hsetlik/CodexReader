#ifndef MASTERSTACKEDWIDGET_H
#define MASTERSTACKEDWIDGET_H

#include <QStackedWidget>
#include <QObject>
#include <QWidget>
#include "loginform.h"
#include "userdashboard.h"
#include "flashcardview.h"
#include "contentreaderwidget.h"

class MasterStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    MasterStackedWidget(QWidget* parent = nullptr);
private:
    CodexDatabase database;
    LoginForm* loginForm;
    UserDashboard* dashboard;
    FlashCardView* cardView;
    CodexContent* currentContent;
    ContentReaderWidget* reader;
    void loadContent(QString name);
private slots:
    void goToUserDashboard(QString username);
    void finishFlashCards();
    void startCardView()
    {
        cardView = new FlashCardView(&database, this);
        addWidget(cardView);
        setCurrentWidget(cardView);
        connect(cardView, &FlashCardView::finishStudying, this, &MasterStackedWidget::finishFlashCards);
    }
    void openContentBrowser(QString name);
    void openContent(CodexContent* cont);
};

#endif // MASTERSTACKEDWIDGET_H
