#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->page);
    this->setWindowTitle("Smart home");
    this->setWindowIcon(QIcon(":/pic/panda.gif"));
    udp = new QUdpSocket(this);   //创建一个UDP网络对象
    bool ok = udp->bind(QHostAddress::LocalHost, 10010);   //绑定本机地址和端口号
    if(!ok)
        qDebug()<<"bind error"<<udp->errorString();
    connect(udp, SIGNAL(readyRead()), this, SLOT(netdata_recv()));
}

void MainWindow::netdata_recv(){
//    QString str;
//    str = udp->readAll();
//    qDebug()<<str<<endl;
    QByteArray  arr;
    arr.resize(udp->pendingDatagramSize());    //定义大小为网络收到的数据大小
    udp->readDatagram(arr.data(), arr.size());    //接收
    qDebug()<< "recv data: "<< arr  ;
    if( arr.contains("open door"))
    {
        ui->btnOpenDoor->click();
        qDebug()<< "close door success !"<< endl ;
    }else
    if( arr.contains("close door"))
    {
        ui->btnCloseDoor->click();
        qDebug()<< "close door success !"<< endl ;
    }
    else
    if( arr.contains("open windows"))
    {
        ui->btnOpenWin->click();
        qDebug()<< "close door success !"<< endl ;
    }
    else if( arr.contains("close windows"))
    {
        ui->btnCloseWin->click();
        qDebug()<< "close door success !"<< endl ;
    }
    else if( arr.contains("open led"))
    {
        ui->btnOpenLight->click();
        qDebug()<< "close door success !"<< endl ;
    }
    else if( arr.contains("close led"))
    {
        ui->btnCloseLight->click();
        qDebug()<< "close door success !"<< endl ;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_login_clicked()
{
        QMessageBox msg;
        if(ui->edit_user->text()=="root" && ui->edit_pwd->text()=="123456"){
            qDebug()<<"login seccess!"<<endl;
            ui->stackedWidget->setCurrentWidget(ui->page_2);
        }else{
            qDebug()<<"login failed!"<<endl;
            msg.setText("login failed!");
            msg.exec();
        }
}

void MainWindow::on_btnOpenDoor_clicked()
{
    QPixmap pix(":/pic/开门.jpg");
    ui->lb_door->setPixmap(pix);
}

void MainWindow::on_btnCloseDoor_clicked()
{
    QPixmap pix(":/pic/关门.jpg");
    ui->lb_door->setPixmap(pix);
}

void MainWindow::on_btnOpenWin_clicked()
{
    QPixmap pix(":/pic/开窗.jpg");
    ui->lb_win->setPixmap(pix);
}

void MainWindow::on_btnCloseWin_clicked()
{
    QPixmap pix(":/pic/关窗.jpg");
    ui->lb_win->setPixmap(pix);
}

void MainWindow::on_btnOpenLight_clicked()
{
    QPixmap pix(":/pic/开灯.jpg");
    ui->lb_light->setPixmap(pix);
}

void MainWindow::on_btnCloseLight_clicked()
{
    QPixmap pix(":/pic/关灯.jpg");
    ui->lb_light->setPixmap(pix);
}
