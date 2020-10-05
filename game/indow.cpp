#include "indow.h"
#include "ui_indow.h"
#include<QPainter>
#include<QPen>
#include<QBrush>
#include<QMouseEvent>
#include<QPaintEvent>
#include<QPalette>
indow::indow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::indow)
{
    this->xPressed = 0;
    this->yPressed = 0;
    this->numCounts = 0;
    for(int i=0;i<9;i++)
    {
        //遍历
        for(int j=0;j<9;j++)
        {
            checkBoard[i][j] = 0;
        }
     }
     this->setFixedSize(600,600);
     ui->setupUi(this);
     this->setWindowTitle("游戏");
     //设置标题

}
indow::~indow()
{
    delete ui;
}
void indow::paintEvent(QPaintEvent*)
{
    QPalette palette;
    //设置背景颜色
    palette.setColor(QPalette::Background,QColor("#C4834B"));
    this->setPalette(palette);

    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);
    //画线
    for(int i=60;i<600;)
    {
        //画横线
        QPoint pointOne(0,i);
        QPoint pointTwo(600,i);
        painter.drawLine(pointOne,pointTwo);
        i = i + 60;
     }
        for(int i=60;i<=600;)
        {
            //画竖线
            QPoint pointOne(i,0);
            QPoint pointTwo(i,600);
            painter.drawLine(pointOne,pointTwo);
            i = i + 60;
        }

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        for(int i=0;i<this->numCounts;i++)
        {
            if(i%2 == 0)
            {
                brush.setColor(Qt::black);
            }
            else
            {
                brush.setColor(Qt::white);
            }
            painter.setBrush(brush);
            painter.drawEllipse(this->counts[i][0]-20,this->counts[i][1]-20,40,40);
        }
}
void indow::tie()
{
    if(QMessageBox::information(NULL,"Game Over","Tie","Again","Exit")==1)
    {
         close();
    }
    for(int i=0;i<9;i++)
    {
        //清空棋盘
         for(int j=0;j<9;j++)
         {
              this->checkBoard[i][j]=0;
         }
    }
    this->numCounts = 0;//下子数目为0，即下一个子从黑子开始
}
void indow::winShow(int colorCenter)
{
    QString infoShow;
    if(colorCenter == 1)
    {
        //中心点是黑色
        infoShow = "Black Win!";
        //输出黑子赢
    }
    else if(colorCenter == -1)
    {
        infoShow = "White Win!";
        //输出白子赢
    }
    if(QMessageBox::information(NULL,"Game Over",infoShow,"Again","Exit")==1)
    {
        close();
    }
    for(int i=0;i<9;i++)
    {
        //清空棋盘
        for(int j=0;j<9;j++)
        {
            this->checkBoard[i][j]=0;
        }
    }
    this->numCounts = 0;//下子数目为0，即下一个子从黑子开始
}

void indow::checkWin(int x, int y)
{
    int row = y/60-1; //显示第几行
        int col = x/60-1; //显示第几列
        int colorCenter = this->checkBoard[row][col];//中间点的颜色
        ///////////列
        if(row>=4&&this->checkBoard[row-4][col]==colorCenter&&this->checkBoard[row-3][col]==colorCenter&&this->checkBoard[row-2][col]==colorCenter&&this->checkBoard[row-1][col]==colorCenter)
        {
            //该点上面
            winShow(colorCenter);
        }
        else if(row>=3&&row<=7&&this->checkBoard[row+1][col]==colorCenter&&this->checkBoard[row-3][col]==colorCenter&&this->checkBoard[row-2][col]==colorCenter&&this->checkBoard[row-1][col]==colorCenter)
        {
            winShow(colorCenter);
        }
        else if(row>=2&&row<=6&&this->checkBoard[row+2][col]==colorCenter&&this->checkBoard[row+1][col]==colorCenter&&this->checkBoard[row-2][col]==colorCenter&&this->checkBoard[row-1][col]==colorCenter)
        {
            winShow(colorCenter);
        }
        else if(row>=1&&row<=5&&this->checkBoard[row+3][col]==colorCenter&&this->checkBoard[row+2][col]==colorCenter&&this->checkBoard[row+1][col]==colorCenter&&this->checkBoard[row-1][col]==colorCenter)
        {
            winShow(colorCenter);
        }
        else if(row<=4&&this->checkBoard[row+4][col]==colorCenter&&this->checkBoard[row+3][col]==colorCenter&&this->checkBoard[row+2][col]==colorCenter&&this->checkBoard[row+1][col]==colorCenter)
        {
            //该点下面
            winShow(colorCenter);
        }
        //////////行
        else if(col>=4&&this->checkBoard[row][col-4]==colorCenter&&this->checkBoard[row][col-3]==colorCenter&&this->checkBoard[row][col-2]==colorCenter&&this->checkBoard[row][col-1]==colorCenter)
        {
            //该点左边
            winShow(colorCenter);
        }
        else if(col>=3&&col<=7&&this->checkBoard[row][col+1]==colorCenter&&this->checkBoard[row][col-3]==colorCenter&&this->checkBoard[row][col-2]==colorCenter&&this->checkBoard[row][col-1]==colorCenter)
        {
            winShow(colorCenter);
        }
        else if(col>=2&&col<=6&&this->checkBoard[row][col+2]==colorCenter&&this->checkBoard[row][col+1]==colorCenter&&this->checkBoard[row][col-2]==colorCenter&&this->checkBoard[row][col-1]==colorCenter)
        {
            winShow(colorCenter);
        }
        else if(col>=1&&col<=5&&this->checkBoard[row][col+3]==colorCenter&&this->checkBoard[row][col+2]==colorCenter&&this->checkBoard[row][col+1]==colorCenter&&this->checkBoard[row][col-1]==colorCenter)
        {
            winShow(colorCenter);
        }
        else if(col<=4&&this->checkBoard[row][col+4]==colorCenter&&this->checkBoard[row][col+3]==colorCenter&&this->checkBoard[row][col+2]==colorCenter&&this->checkBoard[row][col+1]==colorCenter)
        {
            //该点右边
            winShow(colorCenter);
        }
        //////////左上到右下
        else if(row>=4&&col>=4&&this->checkBoard[row-4][col-4]==colorCenter&&this->checkBoard[row-3][col-3]==colorCenter&&this->checkBoard[row-2][col-2]==colorCenter&&this->checkBoard[row-1][col-1]==colorCenter)
        {
            //该点左上
            winShow(colorCenter);
        }
        else if(row>=3&&col>=3&&row<=7&&col<=7&&this->checkBoard[row+1][col+1]==colorCenter&&this->checkBoard[row-3][col-3]==colorCenter&&this->checkBoard[row-2][col-2]==colorCenter&&this->checkBoard[row-1][col-1]==colorCenter)
        {
            winShow(colorCenter);
        }
        else if(row>=2&&col>=2&&row<=6&&col<=6&&this->checkBoard[row+2][col+2]==colorCenter&&this->checkBoard[row+1][col+1]==colorCenter&&this->checkBoard[row-2][col-2]==colorCenter&&this->checkBoard[row-1][col-1]==colorCenter)
        {
            winShow(colorCenter);
        }
        else if(row>=1&&col>=1&&row<=5&&col<=5&&this->checkBoard[row+3][col+3]==colorCenter&&this->checkBoard[row+2][col+2]==colorCenter&&this->checkBoard[row+1][col+1]==colorCenter&&this->checkBoard[row-1][col-1]==colorCenter)
        {
            winShow(colorCenter);
        }
        else if(row<=4&&col<=4&&this->checkBoard[row+4][col+4]==colorCenter&&this->checkBoard[row+3][col+3]==colorCenter&&this->checkBoard[row+2][col+2]==colorCenter&&this->checkBoard[row+1][col+1]==colorCenter)
        {
            //该点右下
            winShow(colorCenter);
        }
        /////////右上到左下
        else if(row>=4&&col<=4&&this->checkBoard[row-4][col+4]==colorCenter&&this->checkBoard[row-3][col+3]==colorCenter&&this->checkBoard[row-2][col+2]==colorCenter&&this->checkBoard[row-1][col+1]==colorCenter)
        {
            //该点左下
            winShow(colorCenter);
        }
        else if(row>=3&&col<=5&&row<=7&&col>=1&&this->checkBoard[row+1][col-1]==colorCenter&&this->checkBoard[row-3][col+3]==colorCenter&&this->checkBoard[row-2][col+2]==colorCenter&&this->checkBoard[row-1][col+1]==colorCenter)
        {
            winShow(colorCenter);
        }
        else if(row>=2&&col<=6&&row<=6&&col>=2&&this->checkBoard[row+2][col-2]==colorCenter&&this->checkBoard[row+1][col-1]==colorCenter&&this->checkBoard[row-2][col+2]==colorCenter&&this->checkBoard[row-1][col+1]==colorCenter)
        {
            winShow(colorCenter);
        }
        else if(row>=1&&col<=7&&row<=5&&col>=3&&this->checkBoard[row+3][col-3]==colorCenter&&this->checkBoard[row+2][col-2]==colorCenter&&this->checkBoard[row+1][col-1]==colorCenter&&this->checkBoard[row-1][col+1]==colorCenter)
        {
            winShow(colorCenter);
        }
        else if(row<=4&&col>=4&&this->checkBoard[row+4][col-4]==colorCenter&&this->checkBoard[row+3][col-3]==colorCenter&&this->checkBoard[row+2][col-2]==colorCenter&&this->checkBoard[row+1][col-1]==colorCenter)
        {
            //该点右上
            winShow(colorCenter);
        }
        else if(numCounts==81)
        {
            tie();
        }
}
void indow::mousePressEvent(QMouseEvent *mouseEvent)
{
    int x = int(float(mouseEvent->x())/60+0.5)*60;
        int y = int(float(mouseEvent->y())/60+0.5)*60;

        //按下的位置在棋盘内
        if(x>0&&x<600&&y>0&&y<600&&this->checkBoard[y/60-1][x/60-1]==0)//当前按键位置在棋盘内并且当前位置没有棋子
        {
            this->numCounts += 1;//棋子数目加一
            if(this->numCounts%2 != 0)
            {
                //棋局矩阵构造
                this->checkBoard[y/60-1][x/60-1] = 1; //1表示黑色
            }
            else
            {
                this->checkBoard[y/60-1][x/60-1] = -1;//-1表示白色
            }
            this->counts[this->numCounts-1][0] = x;
            this->counts[this->numCounts-1][1] = y;
            this->counts[this->numCounts-1][2] = this->numCounts%2;
            checkWin(x,y);
            this->update();      //用于绘图
        }
}

