// texteditcommand.h
#ifndef TEXTEDITCOMMAND_H
#define TEXTEDITCOMMAND_H

#include <QUndoCommand>
#include <QTextEdit>
#include <QString>

class TextEditCommand : public QUndoCommand
{
public:
    TextEditCommand(QTextEdit *textEdit, const QString &oldText, const QString &newText,
                    int oldCursorPosition, int newCursorPosition, QUndoCommand *parent = nullptr);
    void undo() override;
    void redo() override;

private:
    QTextEdit *m_textEdit;
    QString m_oldText;
    QString m_newText;
    int m_oldCursorPosition;
    int m_newCursorPosition;
};

#endif // TEXTEDITCOMMAND_H
