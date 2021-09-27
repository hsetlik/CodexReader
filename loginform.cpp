#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(CodexDatabase* db, QWidget *parent) :
    QWidget(parent),
    linkedDatabase(db),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_login_btn_clicked()
{
    auto usrString = ui->usr_edit->text();
    auto pswdString = ui->pswd_edit->text();
    if (linkedDatabase->attemptLogin(usrString, pswdString))
    {
        printf ("login successful\n");
        //TODO: emit a signal to the master view to switch to the user view
    }

}

