#ifndef SCOREWINDOW_H
#define SCOREWINDOW_H
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class Scorewindow: public QWidget
{
    Q_OBJECT
public:
    //explicit Scorewindow(QWidget *parent = nullptr);
    explicit Scorewindow(QWidget *parent = nullptr);
    int blackwin=0;
    int whitewin=0;
    void shuaxin();
private:
    QPushButton z1;
    QLineEdit k1;
    QLineEdit k2;
    QLabel k3;
    QLabel k4;
signals:

public slots:
};

#endif // SCOREWINDOW_H
