/********************************************************************************
** Form generated from reading UI file 'searchdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHDIALOG_H
#define UI_SEARCHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_searchDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *Next;
    QPushButton *Delete;
    QLabel *Count;
    QTextEdit *textEdit;

    void setupUi(QDialog *searchDialog)
    {
        if (searchDialog->objectName().isEmpty())
            searchDialog->setObjectName("searchDialog");
        searchDialog->resize(296, 103);
        verticalLayoutWidget = new QWidget(searchDialog);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(180, 10, 111, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Next = new QPushButton(verticalLayoutWidget);
        Next->setObjectName("Next");

        verticalLayout->addWidget(Next);

        Delete = new QPushButton(verticalLayoutWidget);
        Delete->setObjectName("Delete");

        verticalLayout->addWidget(Delete);

        Count = new QLabel(verticalLayoutWidget);
        Count->setObjectName("Count");
        Count->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(Count);

        textEdit = new QTextEdit(searchDialog);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(10, 10, 161, 81));

        retranslateUi(searchDialog);

        QMetaObject::connectSlotsByName(searchDialog);
    } // setupUi

    void retranslateUi(QDialog *searchDialog)
    {
        searchDialog->setWindowTitle(QCoreApplication::translate("searchDialog", "Dialog", nullptr));
        Next->setText(QCoreApplication::translate("searchDialog", "Next", nullptr));
        Delete->setText(QCoreApplication::translate("searchDialog", "Delete", nullptr));
        Count->setText(QCoreApplication::translate("searchDialog", "Count", nullptr));
    } // retranslateUi

};

namespace Ui {
    class searchDialog: public Ui_searchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHDIALOG_H
