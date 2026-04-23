#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_N,&QAction::triggered,this,&MainWindow::newActionSlot);
    connect(ui->action_O,&QAction::triggered,this,&MainWindow::openActionSlot);
    connect(ui->action_S,&QAction::triggered,this,&MainWindow::saveActionSlot);
    connect(ui->action_F,&QAction::triggered,this,&MainWindow::openSearchDialog);

    this->setWindowTitle("MyNotepad");

    qDebug() << "连接撤销信号槽";
    // 检查undoStack是否有效
    if (!undoStack) {
        qDebug() << "错误: undoStack 为空指针!";
        undoStack = new QUndoStack();
    }
    // 初始化撤销栈
    undoStack->setUndoLimit(50); // 设置最大撤销步数
    // 连接撤销栈的信号来更新UI状态
    connect(undoStack, &QUndoStack::indexChanged, this, &MainWindow::updateUndoRedoActions);
    connect(undoStack, &QUndoStack::cleanChanged, this, &MainWindow::updateUndoRedoActions);

    qDebug() << "连接撤销信号槽成功";
}

void MainWindow::openSearchDialog()
{
    qDebug() << "Opening search dialog...";

    if (searchDialog==nullptr) {
        qDebug() << "Creating new search dialog instance";
        searchDialog = new class searchDialog(ui->textEdit); // 去掉 class 关键字
        // 确保对话框关闭时删除
        searchDialog->setAttribute(Qt::WA_DeleteOnClose);
        // 连接 destroyed 信号避免悬空指针
        connect(searchDialog, &QObject::destroyed, this, [this]() {
            searchDialog = nullptr;
            qDebug() << "Search dialog destroyed";
        });
    }

    searchDialog->show();
    searchDialog->activateWindow();
    searchDialog->raise();

    qDebug() << "Search dialog shown";
}

void MainWindow::newActionSlot()
{
    ui->textEdit->clear();
    this->setWindowTitle("新建文本文档.txt");
}

void MainWindow::openActionSlot()
{
    QString filename=QFileDialog::getOpenFileName(this,"选择一个文件",
            QCoreApplication::applicationFilePath(),"*.txt");
    if(filename.isEmpty()){
        QMessageBox::warning(this,"警告","请选择一个文件");
    }else{
        // qDebug()<<filename;
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        QByteArray ba = file.readAll();
        ui->textEdit->setText(QString(ba));
        file.close();
    }
}

void MainWindow::saveActionSlot()
{
    QString filename=QFileDialog::getSaveFileName(this,"选择一个文件",
                                                    "Untitled.txt",
"文本文件(*.txt);;所有文件(*)");

    if(filename.isEmpty()){
        QMessageBox::warning(this,"警告","请选择一个文件");
    }else{
        // qDebug()<<filename;
        QFile file(filename);
        file.open(QIODevice::WriteOnly);
        QByteArray ba=ui->textEdit->toPlainText().toUtf8();
        file.write(ba);
        file.close();
    }
}

/*
void MainWindow::onSearchActionTriggered()
{
    bool ok;
    QString searchText = QInputDialog::getText(this, tr("搜索"), tr("请输入要查找的子串:"), QLineEdit::Normal, "", &ok);

    if (ok && !searchText.isEmpty()) {
        m_currentSearchText = searchText;
        // 这里先直接调用查找高亮，实际你可能想弹出一个更复杂的对话框，包含查找和删除按钮
        // 为了简化，我们先高亮所有匹配项
        highlightAllMatches(searchText);
    }
}
*/

// 高亮所有匹配项的函数
void MainWindow::highlightAllMatches(const QString &pattern)
{
    if (pattern.isEmpty()) {
        ui->textEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>());
        QMessageBox::information(this, "提示", "搜索内容不能为空");
        return;
    }

    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextCursor cursor(ui->textEdit->document());
    QColor color = QColor(Qt::yellow).lighter(50); // 浅黄色背景

    int matchCount = 0;
    int totalChars = 0;

    cursor.movePosition(QTextCursor::Start);
    while (!cursor.isNull() && !cursor.atEnd()) {
        cursor = ui->textEdit->document()->find(pattern, cursor, QTextDocument::FindCaseSensitively); // 根据需求调整查找选项，如大小写敏感
        if (!cursor.isNull()) {
            QTextEdit::ExtraSelection extra;
            extra.cursor = cursor;
            extra.format.setBackground(color);
            extraSelections.append(extra);
            matchCount++;
            totalChars += cursor.selectedText().length(); // 统计匹配字符总数
        }
    }
    ui->textEdit->setExtraSelections(extraSelections); // 应用高亮
    m_extraSelections = extraSelections; // 保存当前高亮信息，供删除使用

    QString message;
    if (matchCount > 0) {
        message = QString("搜索完成！\n\n"
                          "搜索内容: \"%1\"\n"
                          "匹配数量: %2 处\n"
                          "总字符数: %3 个字符\n\n"
                          "所有匹配项已高亮显示。")
                      .arg(pattern)
                      .arg(matchCount)
                      .arg(totalChars);
    } else {
        message = QString("搜索完成！\n\n"
                          "搜索内容: \"%1\"\n"
                          "匹配数量: 0 处\n\n"
                          "未找到匹配项。")
                      .arg(pattern);
    }

    QMessageBox::information(this, "搜索结果", message);
}

// 删除当前高亮（选中）的子串
void MainWindow::onDeleteButtonClicked() // 这个函数可以连接到一个删除按钮的clicked信号
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if (cursor.hasSelection()) {
        // 检查选中的文本是否是我们之前搜索的文本（可选）
        cursor.removeSelectedText();
        // 删除后重新高亮，因为位置可能变了
        highlightAllMatches(m_currentSearchText);
    } else {
        // 如果没有选中文本，可以尝试查找并选中下一个匹配项，然后让用户再次点击删除
        // 或者直接查找并删除第一个匹配项
        findNextMatch(); // 你需要实现findNextMatch函数来查找下一个
        // 假设此时光标已经移动到下一个匹配项并选中
        if (ui->textEdit->textCursor().hasSelection()) {
            ui->textEdit->textCursor().removeSelectedText();
            highlightAllMatches(m_currentSearchText);
        }
    }
}

void MainWindow::findNextMatch()
{
    if (m_currentSearchText.isEmpty()) return;

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor = ui->textEdit->document()->find(m_currentSearchText, cursor);
    if (!cursor.isNull()) {
        ui->textEdit->setTextCursor(cursor); // 移动光标并选中匹配的文本
    }
}

void MainWindow::on_textEdit_textChanged()
{
    QString text = ui->textEdit->toPlainText();

    int letterCount = 0;
    int digitCount = 0;
    int symbolCount = 0;
    int spaceCount = 0;
    int totalCount = text.length();

    // 遍历每个字符进行分类计数
    for (const QChar &ch : text) {
        if (ch.isLetter()) {
            letterCount++;
        } else if (ch.isDigit()) {
            digitCount++;
        } else if (!ch.isSpace()) { // 空格不算符号
            symbolCount++;
        } else{
            spaceCount++;
        }
    }

    // 更新标签显示
    ui->cntlabel->setText(QString("字符统计: 总字数 %1 | 字母 %2 | 数字 %3 | 符号 %4 | 空格 %5")
                                .arg(totalCount)
                                .arg(letterCount)
                                .arg(digitCount)
                                .arg(symbolCount)
                                .arg(spaceCount));

    static QString lastText;
    static int lastCursorPosition = 0;

    // 获取当前光标位置
    int currentCursorPosition = ui->textEdit->textCursor().position();

    // 避免重复记录相同的文本状态
    if (text != lastText) {
        // 创建撤销命令，包含光标位置信息
        TextEditCommand *command = new TextEditCommand(ui->textEdit, lastText, text,
                                                       lastCursorPosition, currentCursorPosition);
        undoStack->push(command);

        lastText = text;
        lastCursorPosition = currentCursorPosition;
    } else {
        // 文本相同但光标位置可能变化，更新光标位置
        lastCursorPosition = currentCursorPosition;
    }
}


void MainWindow::on_action_U_triggered()
{
    if (undoStack->canUndo()) {
        undoStack->undo();
    }
}

void MainWindow::on_action_R_triggered()
{
    if (undoStack->canRedo()) {
        undoStack->redo();
    }
}

void MainWindow::updateUndoRedoActions()
{
    // 更新撤销/恢复Action的启用状态和文本
    ui->action_U->setEnabled(undoStack->canUndo());
    ui->action_R->setEnabled(undoStack->canRedo());

    // 设置提示文本
    QString undoText = undoStack->canUndo() ?
                           QString("撤销 (%1)").arg(undoStack->undoText()) : "撤销";
    QString redoText = undoStack->canRedo() ?
                           QString("恢复 (%1)").arg(undoStack->redoText()) : "恢复";

    ui->action_U->setText(undoText);
    ui->action_R->setText(redoText);
}


MainWindow::~MainWindow()
{
    delete ui;
}
