#ifndef PEOPLEVSCOMPUTER_H
#define PEOPLEVSCOMPUTER_H
#include"board.h"

class PeopleVsComputer:public Board
{
public:
    PeopleVsComputer();

    //人下棋子函数
    virtual void mouseReleaseEvent(QMouseEvent *ev); // 鼠标点击象棋并释放鼠标时候触发
    void click(QPoint pt);


    //机器下棋子函数
    void computerPlaceChess();
    void AI(int *p, int *q);
    int positionValue(int row, int col) ;
    int chessType(int n, int p, int q) ;
    void goStep(int n, int *i, int *j);
};

#endif // PEOPLEVSCOMPUTER_H
