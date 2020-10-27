#ifndef XIEBPOARD_H
#define XIEBPARD_H
#include<QFrame>

namespace Ui {
class aiboard;
}

class Aiboard:public QFrame
{
    Q_OBJECT
public:
    Aiboard();
    int xchess[16][16];
    //棋子半径
    int xchessr;


}
//class xiebpard
//{
//public:
//    xiebpard();
//};

#endif // XIEBPARD_H
