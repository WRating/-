#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_ok_clicked()
{
    QMessageBox msg;
    if(ui->edit_user->text()=="root" && ui->edit_pwd->text()=="123456"){
        qDebug()<<"login seccess!"<<endl;
        msg.setText("login seccess!");

    }else{
        qDebug()<<"login failed!"<<endl;
        msg.setText("login failed!");
    }
     msg.exec();
}
