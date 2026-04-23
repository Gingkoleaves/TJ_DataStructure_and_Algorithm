/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_N;
    QAction *action_O;
    QAction *action_S;
    QAction *action_F;
    QAction *action_U;
    QAction *action_R;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QLabel *cntlabel;
    QMenuBar *menubar;
    QMenu *menu_F;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        action_N = new QAction(MainWindow);
        action_N->setObjectName("action_N");
        action_O = new QAction(MainWindow);
        action_O->setObjectName("action_O");
        action_S = new QAction(MainWindow);
        action_S->setObjectName("action_S");
        action_F = new QAction(MainWindow);
        action_F->setObjectName("action_F");
        action_U = new QAction(MainWindow);
        action_U->setObjectName("action_U");
        action_R = new QAction(MainWindow);
        action_R->setObjectName("action_R");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);

        cntlabel = new QLabel(centralwidget);
        cntlabel->setObjectName("cntlabel");
        cntlabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout->addWidget(cntlabel);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menu_F = new QMenu(menubar);
        menu_F->setObjectName("menu_F");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_F->menuAction());
        menu_F->addAction(action_N);
        menu_F->addAction(action_O);
        menu_F->addAction(action_S);
        menu_F->addSeparator();
        menu_F->addAction(action_F);
        menu_F->addAction(action_U);
        menu_F->addAction(action_R);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_N->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272(&N)", nullptr));
        action_O->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200(&O)", nullptr));
        action_S->setText(QCoreApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272(&S)", nullptr));
        action_F->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242(&S)", nullptr));
        action_U->setText(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200(&U)", nullptr));
        action_R->setText(QCoreApplication::translate("MainWindow", "\346\201\242\345\244\215(&R)", nullptr));
        cntlabel->setText(QCoreApplication::translate("MainWindow", "\345\255\227\347\254\246\347\273\237\350\256\241: \346\200\273\345\255\227\346\225\260 0 | \345\255\227\346\257\215 0 | \346\225\260\345\255\227 0 | \347\254\246\345\217\267 0", nullptr));
        menu_F->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
