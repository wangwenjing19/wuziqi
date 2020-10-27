/********************************************************************************
** Form generated from reading UI file 'indow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INDOW_H
#define UI_INDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_indow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *indow)
    {
        if (indow->objectName().isEmpty())
            indow->setObjectName(QStringLiteral("indow"));
        indow->resize(800, 600);
        centralwidget = new QWidget(indow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        indow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(indow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 17));
        indow->setMenuBar(menubar);
        statusbar = new QStatusBar(indow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        indow->setStatusBar(statusbar);

        retranslateUi(indow);

        QMetaObject::connectSlotsByName(indow);
    } // setupUi

    void retranslateUi(QMainWindow *indow)
    {
        indow->setWindowTitle(QApplication::translate("indow", "MainWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class indow: public Ui_indow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INDOW_H
