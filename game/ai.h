#ifndef AI_H
#define AI_H
#include"aboard.h"
#include "scorewindow.h"

class Ai:public Aboard
{
public:
    Ai();
    virtual void mouseReleaseEvent(QMouseEvent *ev); // 鼠标点击象棋并释放鼠标时候触发
    void click(QPoint pt);
    void computerPlaceChess();
    void algorithm();
    void algorithmeasy();//简单模式下的分值计算
    void positionValue(int row,int col);
    void replace();//悔棋
    void surrender();//投降
    void turnto();//切换到得分窗口
    int score[20][20];
    int prow,pcol;
    int cprow,cpcol;//机器的上一步棋子
    int wwhitewin=0;
    int bblackwin=0;
private:
    QPushButton b4;
    QPushButton b5;
    QPushButton b6;
    Scorewindow *mixx= new Scorewindow(nullptr);
};

#endif // AI_H
