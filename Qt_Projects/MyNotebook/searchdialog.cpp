// searchdialog.cpp
#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QMessageBox>
#include <QLineEdit>

searchDialog::searchDialog(QTextEdit *mainTextEdit, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::searchDialog)
    , mainTextEdit(mainTextEdit) // 初始化主文本编辑框指针
{
    ui->setupUi(this);
    setWindowTitle("查找文本");
    setFixedSize(400, 200);

    // 连接信号和槽 - 搜索对话框中的输入变化触发搜索
    connect(ui->textEdit, &QTextEdit::textChanged, this, &searchDialog::Search);}

searchDialog::~searchDialog()
{
    // 清除主文本编辑框的高亮
    if (mainTextEdit) {
        mainTextEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>());
    }
    m_extraSelections.clear();
    delete ui;
}

void searchDialog::setTextEdit(QTextEdit *textEdit)
{
    mainTextEdit = textEdit;
}

void searchDialog::on_Next_clicked()
{
    // 实现查找下一个功能
    if (!mainTextEdit || ui->textEdit->toPlainText().isEmpty()) {
        return;
    }

    QString pattern = ui->textEdit->toPlainText();
    QTextCursor cursor = mainTextEdit->textCursor();
    cursor = mainTextEdit->document()->find(pattern, cursor);

    if (!cursor.isNull()) {
        mainTextEdit->setTextCursor(cursor);
    } else {
        // 从头开始搜索
        cursor = mainTextEdit->document()->find(pattern);
        if (!cursor.isNull()) {
            mainTextEdit->setTextCursor(cursor);
        } else {
            QMessageBox::information(this, "提示", "未找到匹配项");
        }
    }
}

void searchDialog::on_Delete_clicked()
{

    if (!mainTextEdit) {
        return;
    }

    // 获取当前文本光标
    QTextCursor cursor = mainTextEdit->textCursor();

    // 检查是否有选中的文本
    if (cursor.hasSelection()) {
        // 删除选中的文本
        cursor.removeSelectedText();
        ui->Count->setText("已删除选中文本");
    } else {
        // 如果没有选中文本，尝试删除当前搜索匹配的文本
        QString pattern = ui->textEdit->toPlainText();
        if (!pattern.isEmpty()) {
            // 查找第一个匹配项并删除
            QTextCursor searchCursor(mainTextEdit->document());
            searchCursor = mainTextEdit->document()->find(pattern, searchCursor);

            if (!searchCursor.isNull()) {
                searchCursor.removeSelectedText();
                ui->Count->setText("已删除第一个匹配项");

                // 重新搜索更新高亮和计数
                Search();
            } else {
                ui->Count->setText("没有找到匹配项可删除");
            }
        } else {
            ui->Count->setText("请输入要删除的文本");
        }
    }
}

void searchDialog::Search()
{
    if (!mainTextEdit) {
        ui->Count->setText("未设置文本编辑框");
        return;
    }

    QString pattern = ui->textEdit->toPlainText();
    if (pattern.isEmpty()) {
        // 清空搜索时清除高亮
        if (mainTextEdit) {
            mainTextEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>());
        }
        m_extraSelections.clear();
        ui->Count->setText("就绪");
        return;
    }

    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextCursor cursor(mainTextEdit->document());
    QColor color = QColor(Qt::yellow).lighter(130); // 更柔和的黄色

    int matchCount = 0;

    cursor.movePosition(QTextCursor::Start);
    while (!cursor.isNull() && !cursor.atEnd()) {
        cursor = mainTextEdit->document()->find(pattern, cursor);
        if (!cursor.isNull()) {
            QTextEdit::ExtraSelection extra;
            extra.cursor = cursor;
            extra.format.setBackground(color);
            extraSelections.append(extra);
            matchCount++;
        }
    }

    // 应用到主窗口的文本编辑框
    mainTextEdit->setExtraSelections(extraSelections);
    m_extraSelections = extraSelections;

    if (matchCount == 0) {
        ui->Count->setText("未找到匹配项");
    } else {
        ui->Count->setText(QString("找到 %1 个匹配项").arg(matchCount));
    }
}
