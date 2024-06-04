//
// Created by John on 6/4/2024.
//

#include "MarkdownRenderer.hpp"

MarkdownRenderer::MarkdownRenderer(QObject *parent)
        : QObject(parent)
{
}

QTextDocument* MarkdownRenderer::renderMarkdown(const QString &markdownText)
{
    QTextDocument *document = new QTextDocument();
    document->setMarkdown(markdownText);
    return document;
}