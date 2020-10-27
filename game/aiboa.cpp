#include "aiboa.h"
#include<QPainter>
#include<QMouseEvent>
#include<QDebug>
#include<QMessageBox>

Aiboa::Aiboa()
{
    xclearChess();
    chessr=20;//设置棋子大小
    setMinimumSize(chessr*19*2+1,chessr*19*2+1);//窗口大小
    xstartSetting(1);//黑先下棋子


}

void Aiboa::xstartSetting(int _firstSide)
{
    firstSide=_firstSide;//设置先下一方
    side=_firstSide;//设置当前一方
    update();//qt的东西，自动绘制棋盘
}

void Aiboa::xplaceTheChess(int row, int col)
{
    if(row<1||row>19||col<1||col>19)
        return;
    if(chess[row][col]!=0)
        return;
    chess[row][col]=side;
}

void Aiboa::xclearChess()
{
    for(int i=1;i<=19;i++)//棋盘清空，没有棋子
        for(int j=1;j<=19;j++)
            chess[i][j]=0;
}

bool Aiboa::xisWin(int row, int col)
{
    int dx[8]={0,1,1,1,0,-1,-1,-1};
    int dy[8]={1,1,0,-1,-1,-1,0,1};

    int currentSide=chess[row][col];

    int cnt,r,c,i;
    for(i=0;i<4;i++){
        int dir=i;
        cnt=0;
        r=row;
        c=col;
        while(chess[r][c]==currentSide){
            cnt++;
            r+=dy[dir];
            c+=dx[dir];
        }
        dir+=4;
        r=row;
        c=col;
        while(chess[r][c]==currentSide){
            cnt++;
            r+=dy[dir];
            c+=dx[dir];
        }
        if(cnt>5){

            return true;
        }


    }
    return false;
}

void Aiboa::xpaintEvent(QPaintEvent *)
{
    xDrawBackground();//绘制背景
    int r = height() / (19*2);//设置半径
    chessr=r;
    point=QPoint(chessr+1,chessr+1);
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    xdrawPlate(p);
    xdrawChess(p);

}

void Aiboa::xDrawBackground()
{
    QPalette p = this->palette();
    p.setColor(QPalette::Window, QColor("#C4834B"));
    this->setPalette(p);
}

void Aiboa::xdrawPlate(QPainter &p)
{
    // 绘制15条横线
    for (int i = 1; i <= 19; ++i) {
        if (i == 1 || i == 19) { // 上下边框画笔设置的粗一些
            p.setPen(QPen(Qt::black, 3, Qt::SolidLine));
        }
        else {
            p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        }
        p.drawLine(xcenter(i, 1), xcenter(i, 15));
    }

    // 绘制15条竖线
    for (int i = 1; i <=19; ++i) {
        p.setPen(QPen(Qt::black, 3, Qt::SolidLine));
        p.drawLine(xcenter(1, i), xcenter(19, i));
    }
}

void Aiboa::xdrawChess(QPainter &p)
{
    QColor color;
    for(int i=1;i<=19;i++){
        for(int j=1;j<=19;j++){
            if(chess[i][j]==2){//白方
                color=Qt::white;
                p.setBrush(Qt::white);
                p.setPen(QPen(QBrush(color), 2));
                p.drawEllipse(xcell(i,j));
            }
            else if(chess[i][j]==1){//黑方
                color=Qt::black;
                p.setBrush(Qt::black);
                p.setPen(QPen(QBrush(color), 2));
                p.drawEllipse(xcell(i,j));
            }
        }

    }
}

QPoint Aiboa::xcenter(int row, int col)
{
    QPoint pt(chessr * (col-1) * 2, chessr * (row-1) * 2);
    return pt + point;
}

QPoint Aiboa::xtopLeft(int row, int col)
{
    return xcenter(row, col) - QPoint(chessr, chessr);
}

QRect Aiboa::xcell(int row, int col)
{
    return QRect(xtopLeft(row, col), QSize(chessr * 2 - 1, chessr * 2 - 1));
}

bool Aiboa::xQpointToRowCol(QPoint pt, int &row, int &col)
{
    row = pt.y() / (2 * chessr)+1 ;
    col = pt.x() / (2 * chessr)+1 ;

    QPoint c = xcenter(row, col);
    int dx = c.x() - pt.x();
    int dy = c.y() - pt.y();
    int dist = dx * dx + dy * dy; // 和鼠标所处矩形左上顶点的距离
    if (dist < chessr * chessr) {
        return true;
    }

    row += 1;
    c = xcenter(row, col);
    dx = c.x() - pt.x();
    dy = c.y() - pt.y();
    dist = dx * dx + dy * dy; // 和鼠标所处矩形左下顶点的距离
    if (dist < chessr * chessr) {
        return true;
    }

    row -= 1;
    col += 1;
    c = xcenter(row, col);
    dx = c.x() - pt.x();
    dy = c.y() - pt.y();
    dist = dx * dx + dy * dy; // 和鼠标所处矩形右上顶点的距离
    if (dist < chessr * chessr) {
        return true;
    }

    row += 1;
    c = xcenter(row, col);
    dx = c.x() - pt.x();
    dy = c.y() - pt.y();
    dist = dx * dx + dy * dy; // 和鼠标所处矩形右下顶点的距离
    if (dist < chessr * chessr) {
        return true;
    }

    return false;
}
