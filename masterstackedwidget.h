#ifndef MASTERSTACKEDWIDGET_H
#define MASTERSTACKEDWIDGET_H

#include <QStackedWidget>
#include <QObject>
#include <QWidget>
#include "loginform.h"

class MasterStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    MasterStackedWidget(QWidget* parent = nullptr);
private:
    CodexDatabase database;
    LoginForm* loginForm;

};

#endif // MASTERSTACKEDWIDGET_H
