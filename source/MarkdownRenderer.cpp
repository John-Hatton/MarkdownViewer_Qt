//
// Created by John on 6/4/2024.
//


#include <MarkdownRenderer.hpp>
#include <QTextBlockFormat>
#include <QTextCursor>

MarkdownRenderer::MarkdownRenderer(QObject *parent)
        : QObject(parent)
{
}

QTextDocument* MarkdownRenderer::renderMarkdown(const QString &markdownText)
{
    QTextDocument *document = new QTextDocument();

    // Split the markdown text into lines and process each line
    QStringList lines = markdownText.split('\n');
    QTextCursor cursor(document);
    QTextCharFormat normalFormat;
    QTextCharFormat codeFormat;
    codeFormat.setFontFamilies(QStringList() << "Courier");
    codeFormat.setFontPointSize(12);

            foreach (const QString &line, lines) {
            if (line.startsWith("    ") || line.startsWith("\t")) {
                cursor.insertBlock();
                cursor.setBlockCharFormat(codeFormat);
                cursor.insertText(line);
            } else {
                cursor.insertBlock();
                cursor.setBlockCharFormat(normalFormat);
                cursor.insertText(line);
            }
        }

    return document;
}