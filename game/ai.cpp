#include "ai.h"
#include<QMouseEvent>
#include<QMessageBox>
#include<windows.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<QDebug>
#include "scorewindow.h"
Ai::Ai()
{
    b4.setParent(this);
    b4.setText("悔棋");
    b4.move(770,400);
    b4.resize(120,50);
    connect(&b4,&QPushButton::pressed,this,&Ai::replace);
    b5.setParent(this);
    b5.setText("投降");
    b5.move(770,500);
    b5.resize(120,50);
    connect(&b5,&QPushButton::pressed,this,&Ai::surrender);
    b6.setParent(this);
    b6.setText("查看得分");
    b6.move(770,700);
    b6.resize(120,50);
    connect(&b6,&QPushButton::pressed,mixx,&Scorewindow::show);
}

void Ai::mouseReleaseEvent(QMouseEvent *ev)
{
    click(ev->pos());
}
//玩家下棋
void Ai::click(QPoint pt)
{
    if(moshi==2)
    {
        int row, col;
        //无棋子时进行
        if(QpointToRowCol(pt,row,col)&&chess[row][col]==0)
        {
            placeTheChess(row,col);
            //如果此时已经出现胜方
            prow=row;
            pcol=col;
            //记录上一步的落子位置
            if(isWin(row,col))
            {
                if(side==2)
                {
                    wwhitewin+=100;
                    mixx->whitewin=wwhitewin;
                    QMessageBox message(QMessageBox::NoIcon, "结束", "白方胜");
                    message.exec();

                }
                else if(side==1)
                {
                    bblackwin+=100;
                    mixx->blackwin=bblackwin;
                    QMessageBox message(QMessageBox::NoIcon, "结束", "黑方胜");
                    message.exec();

                }
                return;
            }
            side=(side==1)?2:1;
            update();

            computerPlaceChess();

            side=(side==1)?2:1;
            update();
        }
    }
    else if(moshi==1)
    {
            computerPlaceChess();

            side=(side==1)?2:1;
            update();
    }
    else
        return;
}
//电脑置子
void Ai::computerPlaceChess()
{
    int row,col;

    if(level==1)
    {
        algorithm();
    }
    else if(level==2)
    {
        algorithmeasy();
    }
    row=10;
    col=10;
    for(int i=1;i<20;i++)
    {
        for(int j=1;j<20;j++)
        {
            if(score[i][j]>score[row][col])
            {
                row=i;
                col=j;
            }
        }
    }
    cprow=row;
    cpcol=col;
    placeTheChess(row,col);
    //如果此时已经出现胜方
    if(isWin(row,col))
    {
        if(side==2)
        {
            wwhitewin+=100;
            mixx->whitewin=wwhitewin;
            QMessageBox message(QMessageBox::NoIcon, "结束", "白方胜");
            message.exec();

        }
        else if(side==1)
        {
            bblackwin+=100;
            mixx->blackwin=bblackwin;
            QMessageBox message(QMessageBox::NoIcon, "结束", "黑方胜");
            message.exec();

        }
        return;
    }
}
//easy模式下得计算方法
void Ai::algorithmeasy()
{
    int defen=0;
    srand((int)time(NULL));// 产生随机种子
    for(int i=1;i<=19;i++)
        for(int j=1;j<=19;j++)
        {
            defen=0;
            if(chess[i][j]!=0)
            {
                defen=0;
            }
            else
            {
                defen+=1;

                defen+=rand()%300;
                //进攻一方且四子连线
                if((i>=5&&chess[i-1][j]==side&&chess[i-2][j]==side&&chess[i-3][j]==side&&chess[i-4][j]==side)||
                   (i<=15&&chess[i+1][j]==side&&chess[i+2][j]==side&&chess[i+3][j]==side&&chess[i+4][j]==side)||
                   (j>=5&&chess[i][j-1]==side&&chess[i][j-2]==side&&chess[i][j-3]==side&&chess[i][j-4]==side)||
                   (j<=15&&chess[i][j+1]==side&&chess[i][j+2]==side&&chess[i][j+3]==side&&chess[i][j+4]==side)||
                   (i>=5&&j>=5&&chess[i-1][j-1]==side&&chess[i-2][j-2]==side&&chess[i-3][j-3]==side&&chess[i-4][j-4]==side)||
                   (i>=5&&j<=15&&chess[i-1][j+1]==side&&chess[i-2][j+2]==side&&chess[i-3][j+3]==side&&chess[i-4][j+4]==side)||
                   (i<=15&&j>=5&&chess[i+1][j-1]==side&&chess[i+2][j-2]==side&&chess[i+3][j-3]==side&&chess[i+4][j-4]==side)||
                   (i<=15&&j<=15&&chess[i+1][j+1]==side&&chess[i+2][j+2]==side&&chess[i+3][j+3]==side&&chess[i+4][j+4]==side))
                    {
                        defen+=500000;

                    }
                //进攻一方有三子连线且两边空白
                if((i>=5&&chess[i-1][j]==side&&chess[i-2][j]==side&&chess[i-3][j]==side&&chess[i-4][j]==0)||
                   (i<=15&&chess[i+1][j]==side&&chess[i+2][j]==side&&chess[i+3][j]==side&&chess[i+4][j]==0)||
                   (j>=5&&chess[i][j-1]==side&&chess[i][j-2]==side&&chess[i][j-3]==side&&chess[i][j-4]==0)||
                   (j<=15&&chess[i][j+1]==side&&chess[i][j+2]==side&&chess[i][j+3]==side&&chess[i][j+4]==0)||
                   (i>=5&&j>=5&&chess[i-1][j-1]==side&&chess[i-2][j-2]==side&&chess[i-3][j-3]==side&&chess[i-4][j-4]==0)||
                   (i>=5&&j<=15&&chess[i-1][j+1]==side&&chess[i-2][j+2]==side&&chess[i-3][j+3]==side&&chess[i-4][j+4]==0)||
                   (i<=15&&j>=5&&chess[i+1][j-1]==side&&chess[i+2][j-2]==side&&chess[i+3][j-3]==side&&chess[i+4][j-4]==0)||
                   (i<=15&&j<=15&&chess[i+1][j+1]==side&&chess[i+2][j+2]==side&&chess[i+3][j+3]==side&&chess[i+4][j+4]==0))
                    {
                        defen+=40000;

                    }
                //进攻一方有三子连线无空白
                if((i>=4&&chess[i-1][j]==side&&chess[i-2][j]==side&&chess[i-3][j]==side)||
                   (i<=16&&chess[i+1][j]==side&&chess[i+2][j]==side&&chess[i+3][j]==side)||
                   (j>=4&&chess[i][j-1]==side&&chess[i][j-2]==side&&chess[i][j-3]==side)||
                   (j<=16&&chess[i][j+1]==side&&chess[i][j+2]==side&&chess[i][j+3]==side)||
                   (i>=4&&j>=4&&chess[i-1][j-1]==side&&chess[i-2][j-2]==side&&chess[i-3][j-3]==side)||
                   (i>=4&&j<=16&&chess[i-1][j+1]==side&&chess[i-2][j+2]==side&&chess[i-3][j+3]==side)||
                   (i<=16&&j>=4&&chess[i+1][j-1]==side&&chess[i+2][j-2]==side&&chess[i+3][j-3]==side)||
                   (i<=16&&j<=16&&chess[i+1][j+1]==side&&chess[i+2][j+2]==side&&chess[i+3][j+3]==side))
                    {
                        defen+=30000;

                    }
                //进攻一方附近有子就优先附近下棋
                if((i>=2&&chess[i-1][j]==side)||
                   (i<=18&&chess[i+1][j]==side)||
                   (j>=2&&chess[i][j-1]==side)||
                   (j<=18&&chess[i][j+1]==side)||
                   (i>=2&&j>=18&&chess[i-1][j-1]==side)||
                   (i>=2&&j<=18&&chess[i-1][j+1]==side)||
                   (i<=18&&j>=2&&chess[i+1][j-1]==side)||
                   (i<=18&&j<=18&&chess[i+1][j+1]==side))
                    {
                        defen+=500;

                    }
                //防守一方且四子连线
                if((i>=5&&chess[i-1][j]!=side&&chess[i-2][j]!=side&&chess[i-3][j]!=side&&chess[i-4][j]!=side
                    &&chess[i-1][j]!=0&&chess[i-2][j]!=0&&chess[i-3][j]!=0&&chess[i-4][j]!=0)||
                   (i<=15&&chess[i+1][j]!=side&&chess[i+2][j]!=side&&chess[i+3][j]!=side&&chess[i+4][j]!=side
                    &&chess[i+1][j]!=0&&chess[i+2][j]!=0&&chess[i+3][j]!=0&&chess[i+4][j]!=0)||
                   (j>=5&&chess[i][j-1]!=side&&chess[i][j-2]!=side&&chess[i][j-3]!=side&&chess[i][j-4]!=side
                    &&chess[i][j-1]!=0&&chess[i][j-2]!=0&&chess[i][j-3]!=0&&chess[i][j-4]!=0)||
                   (j<=15&&chess[i][j+1]!=side&&chess[i][j+2]!=side&&chess[i][j+3]!=side&&chess[i][j+4]!=side
                    &&chess[i][j+1]!=0&&chess[i][j+2]!=0&&chess[i][j+3]!=0&&chess[i][j+4]!=0)||
                   (i>=5&&j>=5&&chess[i-1][j-1]!=side&&chess[i-2][j-2]!=side&&chess[i-3][j-3]!=side&&chess[i-4][j-4]!=side
                    &&chess[i-1][j-1]!=0&&chess[i-2][j-2]!=0&&chess[i-3][j-3]!=0&&chess[i-4][j-4]!=0)||
                   (i>=5&&j<=15&&chess[i-1][j+1]!=side&&chess[i-2][j+2]!=side&&chess[i-3][j+3]!=side&&chess[i-4][j+4]!=side
                    &&chess[i-1][j+1]!=0&&chess[i-2][j+2]!=0&&chess[i-3][j+3]!=0&&chess[i-4][j+4]!=0)||
                   (i<=15&&j>=5&&chess[i+1][j-1]!=side&&chess[i+2][j-2]!=side&&chess[i+3][j-3]!=side&&chess[i+4][j-4]!=side
                    &&chess[i+1][j-1]!=0&&chess[i+2][j-2]!=0&&chess[i+3][j-3]!=0&&chess[i+4][j-4]!=0)||
                   (i<=15&&j<=15&&chess[i+1][j+1]!=side&&chess[i+2][j+2]!=side&&chess[i+3][j+3]!=side&&chess[i+4][j+4]!=side
                    &&chess[i+1][j+1]!=0&&chess[i+2][j+2]!=0&&chess[i+3][j+3]!=0&&chess[i+4][j+4]!=0))
                    {
                        defen+=450000;

                    }
                //防守一方有三子连线且两边空白
                if((i>=5&&chess[i-1][j]!=side&&chess[i-2][j]!=side&&chess[i-3][j]!=side&&chess[i-4][j]==0
                    &&chess[i-1][j]!=0&&chess[i-2][j]!=0&&chess[i-3][j]!=0)||
                   (i<=15&&chess[i+1][j]!=side&&chess[i+2][j]!=side&&chess[i+3][j]!=side&&chess[i+4][j]==0
                    &&chess[i+1][j]!=0&&chess[i+2][j]!=0&&chess[i+3][j]!=0)||
                   (j>=5&&chess[i][j-1]!=side&&chess[i][j-2]!=side&&chess[i][j-3]!=side&&chess[i][j-4]==0
                    &&chess[i][j-1]!=0&&chess[i][j-2]!=0&&chess[i][j-3]!=0)||
                   (j<=15&&chess[i][j+1]!=side&&chess[i][j+2]!=side&&chess[i][j+3]!=side&&chess[i][j+4]==0
                    &&chess[i][j+1]!=0&&chess[i][j+2]!=0&&chess[i][j+3]!=0)||
                   (i>=5&&j>=5&&chess[i-1][j-1]!=side&&chess[i-2][j-2]!=side&&chess[i-3][j-3]!=side&&chess[i-4][j-4]==0
                    &&chess[i-1][j-1]!=0&&chess[i-2][j-2]!=0&&chess[i-3][j-3]!=0)||
                   (i>=5&&j<=15&&chess[i-1][j+1]!=side&&chess[i-2][j+2]!=side&&chess[i-3][j+3]!=side&&chess[i-4][j+4]==0
                    &&chess[i-1][j+1]!=0&&chess[i-2][j+2]!=0&&chess[i-3][j+3]!=0)||
                   (i<=15&&j>=5&&chess[i+1][j-1]!=side&&chess[i+2][j-2]!=side&&chess[i+3][j-3]!=side&&chess[i+4][j-4]==0
                    &&chess[i+1][j-1]!=0&&chess[i+2][j-2]!=0&&chess[i+3][j-3]!=0)||
                   (i<=15&&j<=15&&chess[i+1][j+1]!=side&&chess[i+2][j+2]!=side&&chess[i+3][j+3]!=side&&chess[i+4][j+4]==0
                    &&chess[i+1][j+1]!=0&&chess[i+2][j+2]!=0&&chess[i+3][j+3]!=0))
                    {
                        defen+=35000;

                    }
                //防守一方有三子连线无空白
                if((i>=4&&chess[i-1][j]!=side&&chess[i-2][j]!=side&&chess[i-3][j]!=side
                    &&chess[i-1][j]!=0&&chess[i-2][j]!=0&&chess[i-3][j]!=0)||
                   (i<=16&&chess[i+1][j]!=side&&chess[i+2][j]!=side&&chess[i+3][j]!=side
                    &&chess[i+1][j]!=0&&chess[i+2][j]!=0&&chess[i+3][j]!=0)||
                   (j>=4&&chess[i][j-1]!=side&&chess[i][j-2]!=side&&chess[i][j-3]!=side
                    &&chess[i][j-1]!=0&&chess[i][j-2]!=0&&chess[i][j-3]!=0)||
                   (j<=16&&chess[i][j+1]!=side&&chess[i][j+2]!=side&&chess[i][j+3]!=side
                    &&chess[i][j+1]!=0&&chess[i][j+2]!=0&&chess[i][j+3]!=0)||
                   (i>=4&&j>=4&&chess[i-1][j-1]!=side&&chess[i-2][j-2]!=side&&chess[i-3][j-3]!=side
                    &&chess[i-1][j-1]!=0&&chess[i-2][j-2]!=0&&chess[i-3][j-3]!=0)||
                   (i>=4&&j<=16&&chess[i-1][j+1]!=side&&chess[i-2][j+2]!=side&&chess[i-3][j+3]!=side
                    &&chess[i-1][j+1]!=0&&chess[i-2][j+2]!=0&&chess[i-3][j+3]!=0)||
                   (i<=16&&j>=4&&chess[i+1][j-1]!=side&&chess[i+2][j-2]!=side&&chess[i+3][j-3]!=side
                    &&chess[i+1][j-1]!=0&&chess[i+2][j-2]!=0&&chess[i+3][j-3]!=0)||
                   (i<=16&&j<=16&&chess[i+1][j+1]!=side&&chess[i+2][j+2]!=side&&chess[i+3][j+3]!=side
                    &&chess[i+1][j+1]!=0&&chess[i+2][j+2]!=0&&chess[i+3][j+3]!=0))
                    {
                        defen+=25000;

                    }
                //防守一方附近有子则优先防守
                if((i>=2&&chess[i-1][j]!=side
                    &&chess[i-1][j]!=0)||
                   (i<=18&&chess[i+1][j]!=side
                    &&chess[i+1][j]!=0)||
                   (j>=2&&chess[i][j-1]!=side
                    &&chess[i][j-1]!=0)||
                   (j<=18&&chess[i][j+1]!=side
                    &&chess[i][j+1]!=0)||
                   (i>=2&&j>=18&&chess[i-1][j-1]!=side
                    &&chess[i-1][j-1]!=0)||
                   (i>=2&&j<=18&&chess[i-1][j+1]!=side
                    &&chess[i-1][j+1]!=0)||
                   (i<=18&&j>=2&&chess[i+1][j-1]!=side
                    &&chess[i+1][j-1]!=0)||
                   (i<=18&&j<=18&&chess[i+1][j+1]!=side
                    &&chess[i+1][j+1]!=0))
                    {
                        defen+=300;
                    }

            }
            score[i][j]=defen;
        }
}
//计算棋盘上选定点的分值
void Ai::algorithm()
{
    int defen=0;
    srand((unsigned)time(NULL));  // 产生随机种子
    for(int i=1;i<=19;i++)
        for(int j=1;j<=19;j++)
        {
            defen=0;
            if(chess[i][j]!=0)
            {
                defen=0;
            }
            else
            {
                defen+=1;

                defen+=rand()%300;
                //进攻一方且四子连线
                if((i>=5&&chess[i-1][j]==side&&chess[i-2][j]==side&&chess[i-3][j]==side&&chess[i-4][j]==side)||
                   (i<=15&&chess[i+1][j]==side&&chess[i+2][j]==side&&chess[i+3][j]==side&&chess[i+4][j]==side)||
                   (j>=5&&chess[i][j-1]==side&&chess[i][j-2]==side&&chess[i][j-3]==side&&chess[i][j-4]==side)||
                   (j<=15&&chess[i][j+1]==side&&chess[i][j+2]==side&&chess[i][j+3]==side&&chess[i][j+4]==side)||
                   (i>=5&&j>=5&&chess[i-1][j-1]==side&&chess[i-2][j-2]==side&&chess[i-3][j-3]==side&&chess[i-4][j-4]==side)||
                   (i>=5&&j<=15&&chess[i-1][j+1]==side&&chess[i-2][j+2]==side&&chess[i-3][j+3]==side&&chess[i-4][j+4]==side)||
                   (i<=15&&j>=5&&chess[i+1][j-1]==side&&chess[i+2][j-2]==side&&chess[i+3][j-3]==side&&chess[i+4][j-4]==side)||
                   (i<=15&&j<=15&&chess[i+1][j+1]==side&&chess[i+2][j+2]==side&&chess[i+3][j+3]==side&&chess[i+4][j+4]==side))
                    {
                        defen+=500000;

                    }
                //进攻一方有三子连线且两边空白
                if((i>=5&&chess[i-1][j]==side&&chess[i-2][j]==side&&chess[i-3][j]==side&&chess[i-4][j]==0)||
                   (i<=15&&chess[i+1][j]==side&&chess[i+2][j]==side&&chess[i+3][j]==side&&chess[i+4][j]==0)||
                   (j>=5&&chess[i][j-1]==side&&chess[i][j-2]==side&&chess[i][j-3]==side&&chess[i][j-4]==0)||
                   (j<=15&&chess[i][j+1]==side&&chess[i][j+2]==side&&chess[i][j+3]==side&&chess[i][j+4]==0)||
                   (i>=5&&j>=5&&chess[i-1][j-1]==side&&chess[i-2][j-2]==side&&chess[i-3][j-3]==side&&chess[i-4][j-4]==0)||
                   (i>=5&&j<=15&&chess[i-1][j+1]==side&&chess[i-2][j+2]==side&&chess[i-3][j+3]==side&&chess[i-4][j+4]==0)||
                   (i<=15&&j>=5&&chess[i+1][j-1]==side&&chess[i+2][j-2]==side&&chess[i+3][j-3]==side&&chess[i+4][j-4]==0)||
                   (i<=15&&j<=15&&chess[i+1][j+1]==side&&chess[i+2][j+2]==side&&chess[i+3][j+3]==side&&chess[i+4][j+4]==0))
                    {
                        defen+=40000;

                    }
                //进攻一方有三子连线无空白,边界情况除外
                if((i>=4&&i!=19&&chess[i-1][j]==side&&chess[i-2][j]==side&&chess[i-3][j]==side)||
                   (i<=16&&i!=1&&chess[i+1][j]==side&&chess[i+2][j]==side&&chess[i+3][j]==side)||
                   (j>=4&&j!=19&&chess[i][j-1]==side&&chess[i][j-2]==side&&chess[i][j-3]==side)||
                   (j<=16&&j!=1&&chess[i][j+1]==side&&chess[i][j+2]==side&&chess[i][j+3]==side)||
                   (i>=4&&j>=4&&i!=19&&j!=19&&chess[i-1][j-1]==side&&chess[i-2][j-2]==side&&chess[i-3][j-3]==side)||
                   (i>=4&&j<=16&&i!=19&&j!=1&&chess[i-1][j+1]==side&&chess[i-2][j+2]==side&&chess[i-3][j+3]==side)||
                   (i<=16&&j>=4&&i!=1&&j!=19&&chess[i+1][j-1]==side&&chess[i+2][j-2]==side&&chess[i+3][j-3]==side)||
                   (i<=16&&j<=16&&i!=1&&j!=1&&chess[i+1][j+1]==side&&chess[i+2][j+2]==side&&chess[i+3][j+3]==side))
                    {
                        defen+=30000;

                    }
                //进攻一方有两子连线且间隔一个空白又有一个子
                if((i>=5&&chess[i-1][j]==side&&chess[i-2][j]==side&&chess[i-3][j]==0&&chess[i-4][j]==side)||
                   (i<=15&&chess[i+1][j]==side&&chess[i+2][j]==side&&chess[i+3][j]==0&&chess[i+4][j]==side)||
                   (j>=5&&chess[i][j-1]==side&&chess[i][j-2]==side&&chess[i][j-3]==0&&chess[i][j-4]==side)||
                   (j<=15&&chess[i][j+1]==side&&chess[i][j+2]==side&&chess[i][j+3]==0&&chess[i][j+4]==side)||
                   (i>=5&&j>=5&&chess[i-1][j-1]==side&&chess[i-2][j-2]==side&&chess[i-3][j-3]==0&&chess[i-4][j-4]==side)||
                   (i>=5&&j<=15&&chess[i-1][j+1]==side&&chess[i-2][j+2]==side&&chess[i-3][j+3]==0&&chess[i-4][j+4]==side)||
                   (i<=15&&j>=5&&chess[i+1][j-1]==side&&chess[i+2][j-2]==side&&chess[i+3][j-3]==0&&chess[i+4][j-4]==side)||
                   (i<=15&&j<=15&&chess[i+1][j+1]==side&&chess[i+2][j+2]==side&&chess[i+3][j+3]==0&&chess[i+4][j+4]==side))
                    {
                        defen+=40000;

                    }
                //进攻一方有二子连线有空白
                if((i>=4&&chess[i-1][j]==side&&chess[i-2][j]==side&&chess[i-3][j]==0)||
                   (i<=16&&chess[i+1][j]==side&&chess[i+2][j]==side&&chess[i+3][j]==0)||
                   (j>=4&&chess[i][j-1]==side&&chess[i][j-2]==side&&chess[i][j-3]==0)||
                   (j<=16&&chess[i][j+1]==side&&chess[i][j+2]==side&&chess[i][j+3]==0)||
                   (i>=4&&j>=4&&chess[i-1][j-1]==side&&chess[i-2][j-2]==side&&chess[i-3][j-3]==0)||
                   (i>=4&&j<=16&&chess[i-1][j+1]==side&&chess[i-2][j+2]==side&&chess[i-3][j+3]==0)||
                   (i<=16&&j>=4&&chess[i+1][j-1]==side&&chess[i+2][j-2]==side&&chess[i+3][j-3]==0)||
                   (i<=16&&j<=16&&chess[i+1][j+1]==side&&chess[i+2][j+2]==side&&chess[i+3][j+3]==0))
                    {
                        defen+=2000;

                    }
                //进攻一方有二子连线无空白
                if((i>=3&&chess[i-1][j]==side&&chess[i-2][j]==side)||
                   (i<=17&&chess[i+1][j]==side&&chess[i+2][j]==side)||
                   (j>=3&&chess[i][j-1]==side&&chess[i][j-2]==side)||
                   (j<=17&&chess[i][j+1]==side&&chess[i][j+2]==side)||
                   (i>=3&&j>=17&&chess[i-1][j-1]==side&&chess[i-2][j-2]==side)||
                   (i>=3&&j<=17&&chess[i-1][j+1]==side&&chess[i-2][j+2]==side)||
                   (i<=17&&j>=3&&chess[i+1][j-1]==side&&chess[i+2][j-2]==side)||
                   (i<=17&&j<=17&&chess[i+1][j+1]==side&&chess[i+2][j+2]==side))
                    {
                        defen+=1000;

                    }
                //进攻一方附近有子就优先附近下棋
                if((i>=2&&chess[i-1][j]==side)||
                   (i<=18&&chess[i+1][j]==side)||
                   (j>=2&&chess[i][j-1]==side)||
                   (j<=18&&chess[i][j+1]==side)||
                   (i>=2&&j>=18&&chess[i-1][j-1]==side)||
                   (i>=2&&j<=18&&chess[i-1][j+1]==side)||
                   (i<=18&&j>=2&&chess[i+1][j-1]==side)||
                   (i<=18&&j<=18&&chess[i+1][j+1]==side))
                    {
                        defen+=500;

                    }
                //防守一方且四子连线
                if((i>=5&&chess[i-1][j]!=side&&chess[i-2][j]!=side&&chess[i-3][j]!=side&&chess[i-4][j]!=side
                    &&chess[i-1][j]!=0&&chess[i-2][j]!=0&&chess[i-3][j]!=0&&chess[i-4][j]!=0)||
                   (i<=15&&chess[i+1][j]!=side&&chess[i+2][j]!=side&&chess[i+3][j]!=side&&chess[i+4][j]!=side
                    &&chess[i+1][j]!=0&&chess[i+2][j]!=0&&chess[i+3][j]!=0&&chess[i+4][j]!=0)||
                   (j>=5&&chess[i][j-1]!=side&&chess[i][j-2]!=side&&chess[i][j-3]!=side&&chess[i][j-4]!=side
                    &&chess[i][j-1]!=0&&chess[i][j-2]!=0&&chess[i][j-3]!=0&&chess[i][j-4]!=0)||
                   (j<=15&&chess[i][j+1]!=side&&chess[i][j+2]!=side&&chess[i][j+3]!=side&&chess[i][j+4]!=side
                    &&chess[i][j+1]!=0&&chess[i][j+2]!=0&&chess[i][j+3]!=0&&chess[i][j+4]!=0)||
                   (i>=5&&j>=5&&chess[i-1][j-1]!=side&&chess[i-2][j-2]!=side&&chess[i-3][j-3]!=side&&chess[i-4][j-4]!=side
                    &&chess[i-1][j-1]!=0&&chess[i-2][j-2]!=0&&chess[i-3][j-3]!=0&&chess[i-4][j-4]!=0)||
                   (i>=5&&j<=15&&chess[i-1][j+1]!=side&&chess[i-2][j+2]!=side&&chess[i-3][j+3]!=side&&chess[i-4][j+4]!=side
                    &&chess[i-1][j+1]!=0&&chess[i-2][j+2]!=0&&chess[i-3][j+3]!=0&&chess[i-4][j+4]!=0)||
                   (i<=15&&j>=5&&chess[i+1][j-1]!=side&&chess[i+2][j-2]!=side&&chess[i+3][j-3]!=side&&chess[i+4][j-4]!=side
                    &&chess[i+1][j-1]!=0&&chess[i+2][j-2]!=0&&chess[i+3][j-3]!=0&&chess[i+4][j-4]!=0)||
                   (i<=15&&j<=15&&chess[i+1][j+1]!=side&&chess[i+2][j+2]!=side&&chess[i+3][j+3]!=side&&chess[i+4][j+4]!=side
                    &&chess[i+1][j+1]!=0&&chess[i+2][j+2]!=0&&chess[i+3][j+3]!=0&&chess[i+4][j+4]!=0))
                    {
                        defen+=450000;

                    }
                //防守一方有三子连线且两边空白
                if((i>=5&&chess[i-1][j]!=side&&chess[i-2][j]!=side&&chess[i-3][j]!=side&&chess[i-4][j]==0
                    &&chess[i-1][j]!=0&&chess[i-2][j]!=0&&chess[i-3][j]!=0)||
                   (i<=15&&chess[i+1][j]!=side&&chess[i+2][j]!=side&&chess[i+3][j]!=side&&chess[i+4][j]==0
                    &&chess[i+1][j]!=0&&chess[i+2][j]!=0&&chess[i+3][j]!=0)||
                   (j>=5&&chess[i][j-1]!=side&&chess[i][j-2]!=side&&chess[i][j-3]!=side&&chess[i][j-4]==0
                    &&chess[i][j-1]!=0&&chess[i][j-2]!=0&&chess[i][j-3]!=0)||
                   (j<=15&&chess[i][j+1]!=side&&chess[i][j+2]!=side&&chess[i][j+3]!=side&&chess[i][j+4]==0
                    &&chess[i][j+1]!=0&&chess[i][j+2]!=0&&chess[i][j+3]!=0)||
                   (i>=5&&j>=5&&chess[i-1][j-1]!=side&&chess[i-2][j-2]!=side&&chess[i-3][j-3]!=side&&chess[i-4][j-4]==0
                    &&chess[i-1][j-1]!=0&&chess[i-2][j-2]!=0&&chess[i-3][j-3]!=0)||
                   (i>=5&&j<=15&&chess[i-1][j+1]!=side&&chess[i-2][j+2]!=side&&chess[i-3][j+3]!=side&&chess[i-4][j+4]==0
                    &&chess[i-1][j+1]!=0&&chess[i-2][j+2]!=0&&chess[i-3][j+3]!=0)||
                   (i<=15&&j>=5&&chess[i+1][j-1]!=side&&chess[i+2][j-2]!=side&&chess[i+3][j-3]!=side&&chess[i+4][j-4]==0
                    &&chess[i+1][j-1]!=0&&chess[i+2][j-2]!=0&&chess[i+3][j-3]!=0)||
                   (i<=15&&j<=15&&chess[i+1][j+1]!=side&&chess[i+2][j+2]!=side&&chess[i+3][j+3]!=side&&chess[i+4][j+4]==0
                    &&chess[i+1][j+1]!=0&&chess[i+2][j+2]!=0&&chess[i+3][j+3]!=0))
                    {
                        defen+=35000;

                    }
                //防守一方有三子连线无空白,且不在边界
                if((i>=4&&i!=19&&chess[i-1][j]!=side&&chess[i-2][j]!=side&&chess[i-3][j]!=side
                    &&chess[i-1][j]!=0&&chess[i-2][j]!=0&&chess[i-3][j]!=0)||
                   (i<=16&&i!=1&&chess[i+1][j]!=side&&chess[i+2][j]!=side&&chess[i+3][j]!=side
                    &&chess[i+1][j]!=0&&chess[i+2][j]!=0&&chess[i+3][j]!=0)||
                   (j>=4&&j!=19&&chess[i][j-1]!=side&&chess[i][j-2]!=side&&chess[i][j-3]!=side
                    &&chess[i][j-1]!=0&&chess[i][j-2]!=0&&chess[i][j-3]!=0)||
                   (j<=16&&j!=1&&chess[i][j+1]!=side&&chess[i][j+2]!=side&&chess[i][j+3]!=side
                    &&chess[i][j+1]!=0&&chess[i][j+2]!=0&&chess[i][j+3]!=0)||
                   (i>=4&&j>=4&&i!=19&&j!=19&&chess[i-1][j-1]!=side&&chess[i-2][j-2]!=side&&chess[i-3][j-3]!=side
                    &&chess[i-1][j-1]!=0&&chess[i-2][j-2]!=0&&chess[i-3][j-3]!=0)||
                   (i>=4&&j<=16&&i!=19&&j!=1&&chess[i-1][j+1]!=side&&chess[i-2][j+2]!=side&&chess[i-3][j+3]!=side
                    &&chess[i-1][j+1]!=0&&chess[i-2][j+2]!=0&&chess[i-3][j+3]!=0)||
                   (i<=16&&j>=4&&i!=1&&j!=19&&chess[i+1][j-1]!=side&&chess[i+2][j-2]!=side&&chess[i+3][j-3]!=side
                    &&chess[i+1][j-1]!=0&&chess[i+2][j-2]!=0&&chess[i+3][j-3]!=0)||
                   (i<=16&&j<=16&&i!=1&&j!=1&&chess[i+1][j+1]!=side&&chess[i+2][j+2]!=side&&chess[i+3][j+3]!=side
                    &&chess[i+1][j+1]!=0&&chess[i+2][j+2]!=0&&chess[i+3][j+3]!=0))
                    {
                        defen+=25000;

                    }
                //防守一方有两子连线且间隔一个空白又有一个点
                if((i>=5&&chess[i-1][j]!=side&&chess[i-2][j]!=side&&chess[i-4][j]!=side&&chess[i-3][j]==0
                    &&chess[i-1][j]!=0&&chess[i-2][j]!=0&&chess[i-4][j]!=0)||
                   (i<=15&&chess[i+1][j]!=side&&chess[i+2][j]!=side&&chess[i+4][j]!=side&&chess[i+3][j]==0
                    &&chess[i+1][j]!=0&&chess[i+2][j]!=0&&chess[i+4][j]!=0)||
                   (j>=5&&chess[i][j-1]!=side&&chess[i][j-2]!=side&&chess[i][j-4]!=side&&chess[i][j-3]==0
                    &&chess[i][j-1]!=0&&chess[i][j-2]!=0&&chess[i][j-4]!=0)||
                   (j<=15&&chess[i][j+1]!=side&&chess[i][j+2]!=side&&chess[i][j+4]!=side&&chess[i][j+3]==0
                    &&chess[i][j+1]!=0&&chess[i][j+2]!=0&&chess[i][j+4]!=0)||
                   (i>=5&&j>=5&&chess[i-1][j-1]!=side&&chess[i-2][j-2]!=side&&chess[i-4][j-4]!=side&&chess[i-3][j-3]==0
                    &&chess[i-1][j-1]!=0&&chess[i-2][j-2]!=0&&chess[i-4][j-4]!=0)||
                   (i>=5&&j<=15&&chess[i-1][j+1]!=side&&chess[i-2][j+2]!=side&&chess[i-4][j+4]!=side&&chess[i-3][j+3]==0
                    &&chess[i-1][j+1]!=0&&chess[i-2][j+2]!=0&&chess[i-4][j+4]!=0)||
                   (i<=15&&j>=5&&chess[i+1][j-1]!=side&&chess[i+2][j-2]!=side&&chess[i+4][j-4]!=side&&chess[i+3][j-3]==0
                    &&chess[i+1][j-1]!=0&&chess[i+2][j-2]!=0&&chess[i+4][j-4]!=0)||
                   (i<=15&&j<=15&&chess[i+1][j+1]!=side&&chess[i+2][j+2]!=side&&chess[i+4][j+4]!=side&&chess[i+3][j+3]==0
                    &&chess[i+1][j+1]!=0&&chess[i+2][j+2]!=0&&chess[i+4][j+4]!=0))
                    {
                        defen+=35000;

                    }
                //防守一方有二子连线有空白
                if((i>=4&&chess[i-1][j]!=side&&chess[i-2][j]!=side&&chess[i-3][j]==0
                    &&chess[i-1][j]!=0&&chess[i-2][j]!=0)||
                   (i<=16&&chess[i+1][j]!=side&&chess[i+2][j]!=side&&chess[i+3][j]==0
                    &&chess[i+1][j]!=0&&chess[i+2][j]!=0)||
                   (j>=4&&chess[i][j-1]!=side&&chess[i][j-2]!=side&&chess[i][j-3]==0
                    &&chess[i][j-1]!=0&&chess[i][j-2]!=0)||
                   (j<=16&&chess[i][j+1]!=side&&chess[i][j+2]!=side&&chess[i][j+3]==0
                    &&chess[i][j+1]!=0&&chess[i][j+2]!=0)||
                   (i>=4&&j>=4&&chess[i-1][j-1]!=side&&chess[i-2][j-2]!=side&&chess[i-3][j-3]==0
                    &&chess[i-1][j-1]!=0&&chess[i-2][j-2]!=0)||
                   (i>=4&&j<=16&&chess[i-1][j+1]!=side&&chess[i-2][j+2]!=side&&chess[i-3][j+3]==0
                    &&chess[i-1][j+1]!=0&&chess[i-2][j+2]!=0)||
                   (i<=16&&j>=4&&chess[i+1][j-1]!=side&&chess[i+2][j-2]!=side&&chess[i+3][j-3]==0
                    &&chess[i+1][j-1]!=0&&chess[i+2][j-2]!=0)||
                   (i<=16&&j<=16&&chess[i+1][j+1]!=side&&chess[i+2][j+2]!=side&&chess[i+3][j+3]==0
                    &&chess[i+1][j+1]!=0&&chess[i+2][j+2]!=0))
                    {
                        defen+=1500;

                    }
                //防守一方有二子连线无空白
                if((i>=3&&chess[i-1][j]!=side&&chess[i-2][j]!=side
                    &&chess[i-1][j]!=0&&chess[i-2][j]!=0)||
                   (i<=17&&chess[i+1][j]!=side&&chess[i+2][j]!=side
                    &&chess[i+1][j]!=0&&chess[i+2][j]!=0)||
                   (j>=3&&chess[i][j-1]!=side&&chess[i][j-2]!=side
                    &&chess[i][j-1]!=0&&chess[i][j-2]!=0)||
                   (j<=17&&chess[i][j+1]!=side&&chess[i][j+2]!=side
                    &&chess[i][j+1]!=0&&chess[i][j+2]!=0)||
                   (i>=3&&j>=17&&chess[i-1][j-1]!=side&&chess[i-2][j-2]!=side
                    &&chess[i-1][j-1]!=0&&chess[i-2][j-2]!=0)||
                   (i>=3&&j<=17&&chess[i-1][j+1]!=side&&chess[i-2][j+2]!=side
                    &&chess[i-1][j+1]!=0&&chess[i-2][j+2]!=0)||
                   (i<=17&&j>=3&&chess[i+1][j-1]!=side&&chess[i+2][j-2]!=side
                    &&chess[i+1][j-1]!=0&&chess[i+2][j-2]!=0)||
                   (i<=17&&j<=17&&chess[i+1][j+1]!=side&&chess[i+2][j+2]!=side
                    &&chess[i+1][j+1]!=0&&chess[i+2][j+2]!=0))
                    {
                        defen+=500;
                    }
                //防守一方附近有子则优先防守
                if((i>=2&&chess[i-1][j]!=side
                    &&chess[i-1][j]!=0)||
                   (i<=18&&chess[i+1][j]!=side
                    &&chess[i+1][j]!=0)||
                   (j>=2&&chess[i][j-1]!=side
                    &&chess[i][j-1]!=0)||
                   (j<=18&&chess[i][j+1]!=side
                    &&chess[i][j+1]!=0)||
                   (i>=2&&j>=18&&chess[i-1][j-1]!=side
                    &&chess[i-1][j-1]!=0)||
                   (i>=2&&j<=18&&chess[i-1][j+1]!=side
                    &&chess[i-1][j+1]!=0)||
                   (i<=18&&j>=2&&chess[i+1][j-1]!=side
                    &&chess[i+1][j-1]!=0)||
                   (i<=18&&j<=18&&chess[i+1][j+1]!=side
                    &&chess[i+1][j+1]!=0))
                    {
                        defen+=300;
                    }

            }

            score[i][j]=defen;
        }
}
//悔棋
void Ai::replace()
{
    chess[prow][pcol]=0;
    chess[cprow][cpcol]=0;
    update();
}
//投降
void Ai::surrender()
{
    if(side==1)
    {
        wwhitewin+=100;
        mixx->whitewin=wwhitewin;
        QMessageBox message(QMessageBox::NoIcon, "结束", "白方胜");
        message.exec();
    }
    else if(side==2)
    {
        bblackwin+=100;
        mixx->blackwin=bblackwin;
        QMessageBox message(QMessageBox::NoIcon, "结束", "黑方胜");
        message.exec();
    }
}
