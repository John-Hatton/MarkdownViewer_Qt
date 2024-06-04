//
// Created by John on 6/4/2024.
//

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>

#ifndef MARKDOWNVIEWER_QT_FOLDERMENU_HPP
#define MARKDOWNVIEWER_QT_FOLDERMENU_HPP

class FolderMenu : public QWidget
{
Q_OBJECT
public:
    explicit FolderMenu(QWidget *parent = nullptr);

    void addMarkdownFile(const QString &filePath);
    QListWidget *getFileList() const; // Method to access the file list
    int getLastWidth() const { return lastWidth; }
    void setLastWidth(int width) { lastWidth = width; }

signals:
    void fileSelected(const QString &filePath);
    void toggled(); // Signal to notify when the folder menu is toggled

private slots:
    void onItemClicked(QListWidgetItem *item);

private:
    QVBoxLayout *layout;
    QPushButton *toggleButton;
    QListWidget *fileList;
    int lastWidth; // Store the last width before collapsing
};

#endif //MARKDOWNVIEWER_QT_FOLDERMENU_HPP
