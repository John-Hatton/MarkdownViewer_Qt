//
// Created by John on 6/4/2024.
//
#include <QObject>
#include <QTextDocument>

#ifndef MARKDOWNVIEWER_QT_MARKDOWNRENDERER_HPP
#define MARKDOWNVIEWER_QT_MARKDOWNRENDERER_HPP


class MarkdownRenderer : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownRenderer(QObject *parent = nullptr);
    QTextDocument* renderMarkdown(const QString &markdownText);
};


#endif //MARKDOWNVIEWER_QT_MARKDOWNRENDERER_HPP
