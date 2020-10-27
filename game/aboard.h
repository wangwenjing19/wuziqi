#ifndef ABOARD_H
#define ABOARD_H
#include<QFrame>
#include<QPushButton>
#include<QRadioButton>
namespace Ui {
class aboard;
}

class Aboard:public QFrame
{
    Q_OBJECT
public:

    Aboard();

    int chess[20][20];//棋盘棋子数据，0为空，1为黑，2为白
    int chessRadius;//棋子半径
    QPoint point;//平面上的一个点,坐标基点
    int firstSide;//先出棋子的那一方
    int side;//当前出棋的一方
    int iside;//不是当前出棋的那一方
    int moshi=1;//用于切换模式
    int level=1;//用于切换难度

    void startSetting(int _firstSide);

    //操作函数
    void placeTheChess(int row,int col);
    void clearChess();//清空棋子
    bool isWin(int row,int col);//判断胜负

    //绘制函数
    virtual void paintEvent(QPaintEvent *);//绘制棋盘
    void DrawBackground();//设置背景颜色
    void drawPlate(QPainter& p);//绘制棋盘
    void drawChess(QPainter &p);//绘制棋子

    //绘制棋子坐标计算的函数
    QPoint center(int row, int col);//返回棋盘行列对应的像素坐标
    QPoint topLeft(int row, int col);
    QRect cell(int row, int col);
    bool QpointToRowCol(QPoint pt, int &row, int &col);

    //切换到人机的函数
    void makechange();
    //切换难度的函数
    void levelchange();
    void levelchange2();

private slots:

private:
    QPushButton b1;
    QPushButton b2;
    QPushButton b3;

    QRadioButton p1;
    QRadioButton p2;
};

#endif // ABOARD_H
