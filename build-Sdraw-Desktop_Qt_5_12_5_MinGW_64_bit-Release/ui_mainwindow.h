/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <graphlibrary.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_N;
    QAction *action_O;
    QAction *action_S;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCircle;
    QAction *actionLine;
    QAction *actionFree;
    QAction *actionEllipse;
    QAction *actionRectangle;
    QAction *actionTool_bar;
    QAction *actionChoose;
    QAction *actionChoose_by_area;
    QAction *actionDelete;
    QAction *actionRotate;
    QAction *actionScale;
    QAction *actionClip;
    QAction *actionMove;
    QAction *actionColor;
    QAction *actionReadText_R;
    QAction *actionSize;
    QWidget *centralwidget;
    GraphLibrary *openGLWidget;
    QMenuBar *menubar;
    QMenu *menu_F;
    QMenu *menu_E;
    QMenu *menuOptions;
    QMenu *menuView;
    QMenu *menuOptions_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        action_N = new QAction(MainWindow);
        action_N->setObjectName(QString::fromUtf8("action_N"));
        action_O = new QAction(MainWindow);
        action_O->setObjectName(QString::fromUtf8("action_O"));
        action_S = new QAction(MainWindow);
        action_S->setObjectName(QString::fromUtf8("action_S"));
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        actionCircle = new QAction(MainWindow);
        actionCircle->setObjectName(QString::fromUtf8("actionCircle"));
        actionLine = new QAction(MainWindow);
        actionLine->setObjectName(QString::fromUtf8("actionLine"));
        actionFree = new QAction(MainWindow);
        actionFree->setObjectName(QString::fromUtf8("actionFree"));
        actionEllipse = new QAction(MainWindow);
        actionEllipse->setObjectName(QString::fromUtf8("actionEllipse"));
        actionRectangle = new QAction(MainWindow);
        actionRectangle->setObjectName(QString::fromUtf8("actionRectangle"));
        actionTool_bar = new QAction(MainWindow);
        actionTool_bar->setObjectName(QString::fromUtf8("actionTool_bar"));
        actionChoose = new QAction(MainWindow);
        actionChoose->setObjectName(QString::fromUtf8("actionChoose"));
        actionChoose_by_area = new QAction(MainWindow);
        actionChoose_by_area->setObjectName(QString::fromUtf8("actionChoose_by_area"));
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        actionRotate = new QAction(MainWindow);
        actionRotate->setObjectName(QString::fromUtf8("actionRotate"));
        actionScale = new QAction(MainWindow);
        actionScale->setObjectName(QString::fromUtf8("actionScale"));
        actionClip = new QAction(MainWindow);
        actionClip->setObjectName(QString::fromUtf8("actionClip"));
        actionMove = new QAction(MainWindow);
        actionMove->setObjectName(QString::fromUtf8("actionMove"));
        actionColor = new QAction(MainWindow);
        actionColor->setObjectName(QString::fromUtf8("actionColor"));
        actionReadText_R = new QAction(MainWindow);
        actionReadText_R->setObjectName(QString::fromUtf8("actionReadText_R"));
        actionSize = new QAction(MainWindow);
        actionSize->setObjectName(QString::fromUtf8("actionSize"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        openGLWidget = new GraphLibrary(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(-20, 0, 821, 561));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        openGLWidget->setAutoFillBackground(false);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menu_F = new QMenu(menubar);
        menu_F->setObjectName(QString::fromUtf8("menu_F"));
        menu_E = new QMenu(menubar);
        menu_E->setObjectName(QString::fromUtf8("menu_E"));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuOptions_2 = new QMenu(menubar);
        menuOptions_2->setObjectName(QString::fromUtf8("menuOptions_2"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_F->menuAction());
        menubar->addAction(menu_E->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuOptions_2->menuAction());
        menu_F->addAction(action_N);
        menu_F->addAction(action_O);
        menu_F->addAction(action_S);
        menu_F->addAction(actionReadText_R);
        menu_E->addAction(actionUndo);
        menu_E->addAction(actionRedo);
        menu_E->addAction(actionScale);
        menu_E->addAction(actionDelete);
        menu_E->addAction(actionRotate);
        menu_E->addAction(actionClip);
        menu_E->addAction(actionMove);
        menuOptions->addAction(actionCircle);
        menuOptions->addAction(actionLine);
        menuOptions->addAction(actionFree);
        menuOptions->addAction(actionEllipse);
        menuOptions->addAction(actionRectangle);
        menuView->addAction(actionTool_bar);
        menuView->addAction(actionColor);
        menuView->addAction(actionSize);
        menuOptions_2->addAction(actionChoose);
        menuOptions_2->addAction(actionChoose_by_area);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        action_N->setText(QApplication::translate("MainWindow", "New(&N)", nullptr));
        action_O->setText(QApplication::translate("MainWindow", "Open(&O)", nullptr));
        action_S->setText(QApplication::translate("MainWindow", "Save(&S)", nullptr));
        actionUndo->setText(QApplication::translate("MainWindow", "Undo", nullptr));
        actionRedo->setText(QApplication::translate("MainWindow", "Redo", nullptr));
        actionCircle->setText(QApplication::translate("MainWindow", "Circle", nullptr));
        actionLine->setText(QApplication::translate("MainWindow", "Line", nullptr));
        actionFree->setText(QApplication::translate("MainWindow", "Free", nullptr));
        actionEllipse->setText(QApplication::translate("MainWindow", "Ellipse", nullptr));
        actionRectangle->setText(QApplication::translate("MainWindow", "Rectangle", nullptr));
        actionTool_bar->setText(QApplication::translate("MainWindow", "Tool bar", nullptr));
        actionChoose->setText(QApplication::translate("MainWindow", "Choose by point", nullptr));
        actionChoose_by_area->setText(QApplication::translate("MainWindow", "Choose by area", nullptr));
        actionDelete->setText(QApplication::translate("MainWindow", "Delete", nullptr));
#ifndef QT_NO_SHORTCUT
        actionDelete->setShortcut(QApplication::translate("MainWindow", "Del", nullptr));
#endif // QT_NO_SHORTCUT
        actionRotate->setText(QApplication::translate("MainWindow", "Rotate", nullptr));
        actionScale->setText(QApplication::translate("MainWindow", "Scale", nullptr));
        actionClip->setText(QApplication::translate("MainWindow", "Clip", nullptr));
        actionMove->setText(QApplication::translate("MainWindow", "Move", nullptr));
        actionColor->setText(QApplication::translate("MainWindow", "Color", nullptr));
        actionReadText_R->setText(QApplication::translate("MainWindow", "ReadText(&R)", nullptr));
        actionSize->setText(QApplication::translate("MainWindow", "Size", nullptr));
        menu_F->setTitle(QApplication::translate("MainWindow", "File(&F)", nullptr));
        menu_E->setTitle(QApplication::translate("MainWindow", "Edit(&E)", nullptr));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Insert", nullptr));
        menuView->setTitle(QApplication::translate("MainWindow", "View", nullptr));
        menuOptions_2->setTitle(QApplication::translate("MainWindow", "Options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
