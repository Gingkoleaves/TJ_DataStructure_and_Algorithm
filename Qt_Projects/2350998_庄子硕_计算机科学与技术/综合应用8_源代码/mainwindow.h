#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "searchdialog.h"
#include "texteditcommand.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDialog>
#include <QInputDialog>
#include <QTextEdit>
#include <QUndoStack>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void newActionSlot();
    void openActionSlot();
    void saveActionSlot();
    void openSearchDialog();

    void on_action_U_triggered(); // 撤销
    void on_action_R_triggered(); // 恢复
    void updateUndoRedoActions(); // 更新撤销/恢复按钮状态

    void on_textEdit_textChanged();

    //void onSearchActionTriggered();
    // void onFindButtonClicked();
    void onDeleteButtonClicked();

private:
    QString m_currentSearchText;
    QList<QTextEdit::ExtraSelection> m_extraSelections;
    searchDialog *searchDialog=nullptr;
    void highlightAllMatches(const QString&);
    void findNextMatch();
    QUndoStack *undoStack=nullptr; // 撤销栈
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
