//
// Created by John on 6/4/2024.
//

#include <QWidget>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QPushButton>

#ifndef MARKDOWNVIEWER_QT_FOLDERMENU_HPP
#define MARKDOWNVIEWER_QT_FOLDERMENU_HPP

class FolderMenu : public QWidget
{
Q_OBJECT
public:
    explicit FolderMenu(QWidget *parent = nullptr);

    void addMarkdownFilesFromDirectory(const QString &directoryPath, QTreeWidgetItem *parentItem = nullptr);
    QTreeWidget *getFileTree() const; // Method to access the file tree
    int getLastWidth() const { return lastWidth; }
    void setLastWidth(int width) { lastWidth = width; }

signals:
    void fileSelected(const QString &filePath);
    void toggled(); // Signal to notify when the folder menu is toggled

private slots:
    void onItemClicked(QTreeWidgetItem *item, int column);

private:
    QVBoxLayout *layout;
    QPushButton *toggleButton;
    QTreeWidget *fileTree;
    int lastWidth; // Store the last width before collapsing
};

#endif //MARKDOWNVIEWER_QT_FOLDERMENU_HPP
