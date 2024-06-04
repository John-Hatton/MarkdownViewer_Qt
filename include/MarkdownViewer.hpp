//
// Created by John on 6/4/2024.
//
#include <QWidget>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <MarkdownRenderer.hpp>
#include <FolderMenu.hpp>
#include <QMenuBar>
#include <QSplitter>

#ifndef MARKDOWNVIEWER_QT_MARKDOWNVIEWER_HPP
#define MARKDOWNVIEWER_QT_MARKDOWNVIEWER_HPP


class MarkdownViewer : public QWidget
{
Q_OBJECT
public:
    explicit MarkdownViewer(QWidget *parent = nullptr);

public slots:
    void loadMarkdownFile(const QString &filePath);
    void openFile();
    void openFolder();
    void handleFolderMenuToggle(); // Slot to handle folder menu toggle

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *contentLayout;
    QMenuBar *menuBar;
    QTextBrowser *textBrowser;
    MarkdownRenderer *renderer;
    FolderMenu *folderMenu;
    QSplitter *splitter;

    void setupMenu();
};

#endif //MARKDOWNVIEWER_QT_MARKDOWNVIEWER_HPP
