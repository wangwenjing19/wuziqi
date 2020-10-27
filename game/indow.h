#ifndef INDOW_H
#define INDOW_H
#include<vector>
#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
namespace Ui {
class indow;
}

class indow : public QMainWindow
{
    Q_OBJECT

public:
    explicit indow(QWidget *parent = 0);
    ~indow();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *mouseEvent);
    void checkWin(int x,int y);
    void winShow(int colorCenter);
    void tie();
    int xPressed;
    int yPressed;
    int numCounts;
    int counts[81][3];
    int checkBoard[15][15];//模拟棋盘，1表示黑色，-1表示白色
private slots:

private:
    Ui::indow *ui;
};

#endif // INDOW_H
