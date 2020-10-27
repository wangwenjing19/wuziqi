#ifndef AIBOA_H
#define AIBOA_H
#include<QFrame>

namespace Ui {
class aiboa;
}

class Aiboa:public QFrame
{
    Q_OBJECT
public:

    Aiboa();

    int chess[20][20];//棋盘棋子数据，0为空，1为黑，2为白
    int chessr;//棋子半径
    QPoint point;//平面上的一个点,坐标基点
    int firstSide;//先出棋子的那一方
    int side;//当前出棋的一方

void xstartSetting(int _firstSide);

    //操作函数
    void xplaceTheChess(int row,int col);
    void xclearChess();//清空棋子
    //是否赢了
    bool xisWin(int row,int col);

    virtual void xpaintEvent(QPaintEvent *);//绘制棋盘
    void xDrawBackground(); // 设置背景颜色
    void xdrawPlate(QPainter& p); // 绘制棋盘
    void xdrawChess(QPainter &p); // 绘制棋子

    //绘制棋子坐标计算的函数
    QPoint xcenter(int row, int col); // 返回棋盘行列对应的像素坐标
    QPoint xtopLeft(int row, int col);
    QRect xcell(int row, int col);
    bool xQpointToRowCol(QPoint pt, int &row, int &col);

private slots:

private:

};

#endif // AIBOA_H
