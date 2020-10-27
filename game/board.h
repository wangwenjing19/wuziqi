#ifndef BOARD_H
#define BOARD_H
#include<QFrame>

namespace Ui {
class board;
}

class Board:public QFrame
{
    Q_OBJECT
public:

    Board();

    int chess[16][16];//棋盘棋子数据，0为空，1为黑，2为白
    int chessRadius;//棋子半径
    QPoint point;//平面上的一个点,坐标基点
    int firstSide;//先出棋子的那一方
    int side;//当前出棋的一方

    void startSetting(int _firstSide);

    //操作函数
    void placeTheChess(int row,int col);
    void clearChess();//清空棋子
    //是否赢了
    bool isWin(int row,int col);

    virtual void paintEvent(QPaintEvent *);//绘制棋盘
    void DrawBackground(); // 设置背景颜色
    void drawPlate(QPainter& p); // 绘制棋盘
    void drawChess(QPainter &p); // 绘制棋子

    //绘制棋子坐标计算的函数
    QPoint center(int row, int col); // 返回棋盘行列对应的像素坐标
    QPoint topLeft(int row, int col);
    QRect cell(int row, int col);
    bool QpointToRowCol(QPoint pt, int &row, int &col);

private slots:

private:

};

#endif // BOARD_H
