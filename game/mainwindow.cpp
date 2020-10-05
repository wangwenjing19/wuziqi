#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"peoplevscomputer.h"
#include<QPainter>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setGeometry(0,0,500,500);
    //设置图片
    ui->label->setPixmap(QPixmap(":/new/prefix1/image/初始界面.jpg"));
    //适应大小
    ui->label->setScaledContents(true);
    ui->buttonstart->move(550,100);
    ui->buttonexit->move(550,300);
    ui->pushButton_pvsc->move(550,200);
    ui->buttonstart->setFont(QFont("宋体", 18));
    ui->buttonexit->setFont(QFont("宋体", 18));
    ui->pushButton_pvsc->setFont(QFont("宋体", 18));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonstart_clicked()
{
    //this->hide();
    w.show();
}

void MainWindow::on_pushButton_pvsc_clicked()
{

    PeopleVsComputer* pvsc= new PeopleVsComputer();
   // this->hide();
    pvsc->show();
  //  this->show();
}
