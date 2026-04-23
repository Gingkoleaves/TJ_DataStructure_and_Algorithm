// texteditcommand.cpp
#include "texteditcommand.h"
#include <QDebug>

TextEditCommand::TextEditCommand(QTextEdit *textEdit, const QString &oldText, const QString &newText,
                                 int oldCursorPosition, int newCursorPosition, QUndoCommand *parent)
    : QUndoCommand(parent)
    , m_textEdit(textEdit)
    , m_oldText(oldText)
    , m_newText(newText)
    , m_oldCursorPosition(oldCursorPosition)
    , m_newCursorPosition(newCursorPosition)
{
    return;
}

void TextEditCommand::undo()
{
    if (m_textEdit) {
        m_textEdit->blockSignals(true);
        m_textEdit->setPlainText(m_oldText);

        // 恢复光标位置
        QTextCursor cursor = m_textEdit->textCursor();
        cursor.setPosition(qMin(m_oldCursorPosition, m_oldText.length()));
        m_textEdit->setTextCursor(cursor);

        m_textEdit->blockSignals(false);
    }
}

void TextEditCommand::redo()
{
    if (m_textEdit) {
        m_textEdit->blockSignals(true);
        m_textEdit->setPlainText(m_newText);

        // 恢复光标位置
        QTextCursor cursor = m_textEdit->textCursor();
        cursor.setPosition(qMin(m_newCursorPosition, m_newText.length()));
        m_textEdit->setTextCursor(cursor);

        m_textEdit->blockSignals(false);
    }
}
