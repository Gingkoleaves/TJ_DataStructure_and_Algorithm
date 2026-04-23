// searchdialog.h
#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDialog>
#include <QInputDialog>
#include <QTextEdit>

namespace Ui {
class searchDialog;
}

class searchDialog : public QDialog
{
    Q_OBJECT

public:
    // 修改构造函数，接收主窗口的文本编辑框指针
    explicit searchDialog(QTextEdit *mainTextEdit, QWidget *parent = nullptr);
    ~searchDialog();

    // 设置要搜索的文本编辑框
    void setTextEdit(QTextEdit *textEdit);

private slots:
    void on_Next_clicked();
    void on_Delete_clicked();
    void Search();

private:
    Ui::searchDialog *ui;
    QTextEdit *mainTextEdit; // 指向主窗口的文本编辑框
    QList<QTextEdit::ExtraSelection> m_extraSelections;
};

#endif // SEARCHDIALOG_H
