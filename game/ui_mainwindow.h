/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_2;
    QWidget *centralWidget;
    QPushButton *buttonstart;
    QPushButton *buttonexit;
    QLabel *label;
    QPushButton *pushButton_pvsc;
    QPushButton *pushButton_ai;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(544, 383);
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        buttonstart = new QPushButton(centralWidget);
        buttonstart->setObjectName(QStringLiteral("buttonstart"));
        buttonstart->setGeometry(QRect(300, 0, 181, 71));
        buttonexit = new QPushButton(centralWidget);
        buttonexit->setObjectName(QStringLiteral("buttonexit"));
        buttonexit->setGeometry(QRect(300, 240, 181, 71));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 251, 231));
        label->setMinimumSize(QSize(141, 141));
        label->setStyleSheet(QString::fromUtf8("background-image :url(:/new/prefix1/image/\345\210\235\345\247\213\347\225\214\351\235\242.jpg)"));
        pushButton_pvsc = new QPushButton(centralWidget);
        pushButton_pvsc->setObjectName(QStringLiteral("pushButton_pvsc"));
        pushButton_pvsc->setGeometry(QRect(300, 80, 181, 71));
        pushButton_ai = new QPushButton(centralWidget);
        pushButton_ai->setObjectName(QStringLiteral("pushButton_ai"));
        pushButton_ai->setGeometry(QRect(300, 160, 181, 71));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 544, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addSeparator();
        menu->addAction(action_2);
        menu->addSeparator();

        retranslateUi(MainWindow);
        QObject::connect(buttonexit, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        action_2->setText(QApplication::translate("MainWindow", "\350\220\275\345\255\220\346\227\266\351\227\264", Q_NULLPTR));
        buttonstart->setText(QApplication::translate("MainWindow", "\344\272\272\344\272\272\345\257\271\345\274\210", Q_NULLPTR));
        buttonexit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272\346\270\270\346\210\217", Q_NULLPTR));
        label->setText(QString());
        pushButton_pvsc->setText(QApplication::translate("MainWindow", "\344\272\272\346\234\272\345\257\271\345\274\210", Q_NULLPTR));
        pushButton_ai->setText(QApplication::translate("MainWindow", "\346\233\264\345\244\232\345\257\271\345\245\225", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\346\270\270\346\210\217\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
