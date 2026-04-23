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
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *generateButton;
    QPushButton *inputButton;
    QPushButton *sortButton;
    QPushButton *buildHeapButton;
    QPushButton *stepButton;
    QPushButton *resetButton;
    QPushButton *CloseButton;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *arrayLabel;
    QLabel *statusLabel;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(660, 30, 115, 194));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(4);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        generateButton = new QPushButton(verticalLayoutWidget);
        generateButton->setObjectName("generateButton");

        verticalLayout->addWidget(generateButton);

        inputButton = new QPushButton(verticalLayoutWidget);
        inputButton->setObjectName("inputButton");

        verticalLayout->addWidget(inputButton);

        sortButton = new QPushButton(verticalLayoutWidget);
        sortButton->setObjectName("sortButton");

        verticalLayout->addWidget(sortButton);

        buildHeapButton = new QPushButton(verticalLayoutWidget);
        buildHeapButton->setObjectName("buildHeapButton");

        verticalLayout->addWidget(buildHeapButton);

        stepButton = new QPushButton(verticalLayoutWidget);
        stepButton->setObjectName("stepButton");

        verticalLayout->addWidget(stepButton);

        resetButton = new QPushButton(verticalLayoutWidget);
        resetButton->setObjectName("resetButton");

        verticalLayout->addWidget(resetButton);

        CloseButton = new QPushButton(verticalLayoutWidget);
        CloseButton->setObjectName("CloseButton");

        verticalLayout->addWidget(CloseButton);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(170, 30, 471, 151));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        arrayLabel = new QLabel(verticalLayoutWidget_2);
        arrayLabel->setObjectName("arrayLabel");
        arrayLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_2->addWidget(arrayLabel);

        statusLabel = new QLabel(verticalLayoutWidget_2);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_2->addWidget(statusLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        generateButton->setText(QCoreApplication::translate("MainWindow", "generateButton", nullptr));
        inputButton->setText(QCoreApplication::translate("MainWindow", "inputButton", nullptr));
        sortButton->setText(QCoreApplication::translate("MainWindow", "sortButton", nullptr));
        buildHeapButton->setText(QCoreApplication::translate("MainWindow", "buildHeapButton", nullptr));
        stepButton->setText(QCoreApplication::translate("MainWindow", "stepButton", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "resetButton", nullptr));
        CloseButton->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        arrayLabel->setText(QCoreApplication::translate("MainWindow", "arrayLabel", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "statusLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
