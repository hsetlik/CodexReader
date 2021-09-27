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

}

