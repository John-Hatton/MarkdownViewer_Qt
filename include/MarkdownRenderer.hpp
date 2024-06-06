//
// Created by John on 6/4/2024.
//
//#include <QObject>
//#include <QWidget>
//#include <QVBoxLayout>
//#include <QTextEdit>
//#include <QTableWidget>
//#include <QTextDocument>

#ifndef MARKDOWNVIEWER_QT_MARKDOWNRENDERER_HPP
#define MARKDOWNVIEWER_QT_MARKDOWNRENDERER_HPP

#include <QObject>
#include <QTextDocument>

class MarkdownRenderer : public QObject
{
Q_OBJECT
public:
    explicit MarkdownRenderer(QObject *parent = nullptr);
    QTextDocument* renderMarkdown(const QString &markdownText);

private:
    void parseLine(const QString &line, QTextCursor &cursor);

    bool inCodeBlock;
    QStringList codeLines;
};

#endif //MARKDOWNVIEWER_QT_MARKDOWNRENDERER_HPP
