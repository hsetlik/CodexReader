#ifndef USERDASHBOARD_H
#define USERDASHBOARD_H

#include <QWidget>
#include "codexdatabase.h"

namespace Ui {
class UserDashboard;
}

class UserDashboard : public QWidget
{
    Q_OBJECT

public:
    explicit UserDashboard(QString usr, CodexDatabase* db, QWidget *parent = nullptr);
    ~UserDashboard();
    CodexDatabase* const linkedDatabase;
    const QString username;

private slots:
    void on_tabWidget_currentChanged(int index);

private:
    Ui::UserDashboard *ui;
};

#endif // USERDASHBOARD_H
