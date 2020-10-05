#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include"indow.h"//子窗口
#include"board.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_buttonstart_clicked();


    void on_pushButton_pvsc_clicked();

private:
    Ui::MainWindow *ui;
    indow w;

};

#endif // MAINWINDOW_H
