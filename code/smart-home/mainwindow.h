#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include  <QUdpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_login_clicked();

    void on_btnOpenDoor_clicked();

    void on_btnCloseDoor_clicked();

    void on_btnOpenWin_clicked();

    void on_btnCloseWin_clicked();

    void on_btnOpenLight_clicked();

    void on_btnCloseLight_clicked();
    void netdata_recv();

private:
    Ui::MainWindow *ui;
    QUdpSocket  *udp;
};

#endif // MAINWINDOW_H
