#include "aboard.h"
#include<QPainter>
#include<QMouseEvent>
#include<QDebug>
#include<QMessageBox>

Aboard::Aboard()
{

    clearChess();
    setWindowTitle("混合对弈");
    chessRadius=20;//设置棋子大小
    setMinimumSize(chessRadius*19*2,chessRadius*19*2+1);//窗口大小
    setMaximumSize(900,761);
    startSetting(1);//黑先下棋子
    b1.setParent(this);
    b1.setText("结束游戏");
    b1.move(770,100);
    b1.resize(120,50);
    connect(&b1,&QPushButton::pressed,this,&Aboard::close);
    b2.setParent(this);
    b2.setText("清盘");
    b2.move(770,200);
    b2.resize(120,50);
    connect(&b2,&QPushButton::pressed,this,&Aboard::clearChess);
    b3.setParent(this);
    b3.setText("接手");
    b3.move(770,300);
    b3.resize(120,50);
    connect(&b3,&QPushButton::pressed,this,&Aboard::makechange);
    p1.setParent(this);
    p1.setText("normal");
    p1.move(770,600);
    p1.resize(120,50);
    connect(&p1,&QRadioButton::clicked,this,&Aboard::levelchange);
    p2.setParent(this);
    p2.setText("easy");
    p2.move(770,650);
    p2.resize(120,50);
    connect(&p2,&QRadioButton::clicked,this,&Aboard::levelchange2);
}

void Aboard::startSetting(int _firstSide)
{
    firstSide=_firstSide;//设置先下一方
    side=_firstSide;//设置当前一方
    update();//自动绘制棋盘
}
//安置棋子
void Aboard::placeTheChess(int row,int col)
{
    if(row<1||row>19||col<1||col>19)
        return;
    if(chess[row][col]!=0)
        return;
    chess[row][col]=side;
}
//切换至人机模式,1为机机，2为人机
void Aboard::makechange()
{
    moshi=(moshi==1)?2:1;
}
//切换难度,1为正常，2为简单
void Aboard::levelchange()
{
    level=1;
}
void Aboard::levelchange2()
{
    level=2;
}
//清空棋盘
void Aboard::clearChess()
{
    for(int i=1;i<=19;i++)
        for(int j=1;j<=19;j++)
            chess[i][j]=0;
    update();
}
//判断输赢
bool Aboard::isWin(int row, int col)
{
    //两个数组代表八个方向，判断棋子的分布
    int dx[8]={0,1,1,1,0,-1,-1,-1};
    int dy[8]={1,1,0,-1,-1,-1,0,1};
    //currentSide表示本颗棋子的花色
    int currentSide=chess[row][col];
    int cnt,r,c,i;
    //开始判断八个方向
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
        //cnt大于五即为获胜
        if(cnt>5){
            return true;
        }
    }
    return false;
}
//绘制棋盘
void Aboard::paintEvent(QPaintEvent *)
{
    DrawBackground();//绘制背景
    int r = height()/(19*2);//设置棋子半径
    chessRadius=r;
    point=QPoint(chessRadius+1,chessRadius+1);
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawPlate(p);
    drawChess(p);

}
//绘制背景
void Aboard::DrawBackground()
{
    QPalette p = this->palette();
    p.setColor(QPalette::Window, QColor("#FFF8DC"));
    this->setPalette(p);
}

void Aboard::drawPlate(QPainter &p)
{
    // 绘制15条横线
    for (int i = 1; i <= 19; ++i) {
        //边框加粗
        if (i == 1 || i == 19) {
            p.setPen(QPen(Qt::black, 3, Qt::SolidLine));
        }
        else {
            p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        }
        p.drawLine(center(i, 1), center(i, 19));
    }
    // 绘制15条竖线
    for (int i = 1; i <=19; ++i) {
        if (i == 1 || i == 19) {
            p.setPen(QPen(Qt::black, 3, Qt::SolidLine));
        }
        else {
            p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        }
        p.drawLine(center(1, i), center(19, i));
    }
}
//绘制棋子
void Aboard::drawChess(QPainter &p)
{
    QColor color;
    for(int i=1;i<=19;i++){
        for(int j=1;j<=19;j++){
            if(chess[i][j]==2){//白方
                color=Qt::white;
                p.setBrush(Qt::white);
                p.setPen(QPen(QBrush(color), 2));
                p.drawEllipse(cell(i,j));
            }
            else if(chess[i][j]==1){//黑方
                color=Qt::black;
                p.setBrush(Qt::black);
                p.setPen(QPen(QBrush(color), 2));
                p.drawEllipse(cell(i,j));
            }
        }
    }
}
//返回棋盘行列对应的像素坐标
QPoint Aboard::center(int row, int col)
{
    QPoint pt(chessRadius * (col-1) * 2, chessRadius * (row-1) * 2);
    return pt + point;
}

QPoint Aboard::topLeft(int row, int col)
{
    return center(row, col) - QPoint(chessRadius, chessRadius);
}

QRect Aboard::cell(int row, int col)
{
    return QRect(topLeft(row, col), QSize(chessRadius * 2 - 1, chessRadius * 2 - 1));
}

bool Aboard::QpointToRowCol(QPoint pt, int &row, int &col)
{
    row = pt.y() / (2 * chessRadius)+1 ;
    col = pt.x() / (2 * chessRadius)+1 ;

    QPoint c = center(row, col);
    int dx = c.x() - pt.x();
    int dy = c.y() - pt.y();
    int dist = dx * dx + dy * dy; // 和鼠标所处矩形左上顶点的距离
    if (dist < chessRadius * chessRadius) {
        return true;
    }

    row += 1;
    c = center(row, col);
    dx = c.x() - pt.x();
    dy = c.y() - pt.y();
    dist = dx * dx + dy * dy; // 和鼠标所处矩形左下顶点的距离
    if (dist < chessRadius * chessRadius) {
        return true;
    }

    row -= 1;
    col += 1;
    c = center(row, col);
    dx = c.x() - pt.x();
    dy = c.y() - pt.y();
    dist = dx * dx + dy * dy; // 和鼠标所处矩形右上顶点的距离
    if (dist < chessRadius * chessRadius) {
        return true;
    }

    row += 1;
    c = center(row, col);
    dx = c.x() - pt.x();
    dy = c.y() - pt.y();
    dist = dx * dx + dy * dy; // 和鼠标所处矩形右下顶点的距离
    if (dist < chessRadius * chessRadius) {
        return true;
    }
    return false;
}
