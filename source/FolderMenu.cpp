//
// Created by John on 6/4/2024.
//

#include <FolderMenu.hpp>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QDir>

FolderMenu::FolderMenu(QWidget *parent)
        : QWidget(parent), layout(new QVBoxLayout(this)), toggleButton(new QPushButton(this)), fileTree(new QTreeWidget(this)), lastWidth(200)
{
    toggleButton->setIcon(QIcon(":/resources/Hamburger.png"));
    toggleButton->setFixedSize(30, 30);

    connect(toggleButton, &QPushButton::clicked, this, [this]() {
        if (this->fileTree->isVisible()) {
            lastWidth = this->width(); // Save the current width before collapsing
            this->setMaximumWidth(30);
            this->setMinimumWidth(30);
        } else {
            this->setMaximumWidth(QWIDGETSIZE_MAX); // Allow full expansion
            this->setMinimumWidth(200); // Set the minimum width when expanded
        }
        this->fileTree->setVisible(!this->fileTree->isVisible());
        emit toggled(); // Emit the toggled signal
    });

    fileTree->setHeaderHidden(true);
    connect(fileTree, &QTreeWidget::itemClicked, this, &FolderMenu::onItemClicked);

    layout->setContentsMargins(0, 0, 0, 0); // No margins to keep button in place
    layout->setSpacing(0); // No spacing between button and tree
    layout->addWidget(toggleButton, 0, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(fileTree);
    setLayout(layout);

    this->setMinimumWidth(200); // Ensure it starts with the correct minimum width
}

void FolderMenu::addMarkdownFilesFromDirectory(const QString &directoryPath, QTreeWidgetItem *parentItem)
{
    QDir directory(directoryPath);
    QFileInfoList entries = directory.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

    for (const QFileInfo &entry : entries) {
        if (entry.isDir()) {
            QTreeWidgetItem *dirItem;
            if (parentItem) {
                dirItem = new QTreeWidgetItem(parentItem);
            } else {
                dirItem = new QTreeWidgetItem(fileTree);
            }
            dirItem->setText(0, entry.fileName());
            addMarkdownFilesFromDirectory(entry.absoluteFilePath(), dirItem);
        } else if (entry.isFile() && entry.suffix() == "md") {
            QTreeWidgetItem *fileItem;
            if (parentItem) {
                fileItem = new QTreeWidgetItem(parentItem);
            } else {
                fileItem = new QTreeWidgetItem(fileTree);
            }
            fileItem->setText(0, entry.fileName());
            fileItem->setData(0, Qt::UserRole, entry.absoluteFilePath());
        }
    }
}

void FolderMenu::onItemClicked(QTreeWidgetItem *item, int column)
{
    QString filePath = item->data(0, Qt::UserRole).toString();
    if (!filePath.isEmpty()) {
        emit fileSelected(filePath);
    }
}

QTreeWidget *FolderMenu::getFileTree() const {
    return fileTree;
}
