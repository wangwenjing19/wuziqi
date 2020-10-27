#include "scorewindow.h"
#include <qstring.h>
#include "ai.h"

Scorewindow::Scorewindow(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(250,250);//窗口大小
    setMaximumSize(250,250);
    z1.setText("刷新分数");
    z1.move(0,100);
    z1.resize(75,45);
    z1.setParent(this);
    connect(&z1,&QPushButton::pressed,this,&Scorewindow::shuaxin);
    k1.move(50,0);
    k1.resize(75,25);
    k1.setParent(this);
    k3.move(0,0);
    k3.resize(50,25);
    k3.setText("黑");
    k3.setParent(this);
    k2.move(50,50);
    k2.resize(75,25);
    k2.setParent(this);
    k4.move(0,50);
    k4.resize(50,25);
    k4.setText("白");
    k4.setParent(this);
}
//刷新分数
void Scorewindow::shuaxin()
{
     k1.setText(QString::number(blackwin));
     k2.setText(QString::number(whitewin));
}
