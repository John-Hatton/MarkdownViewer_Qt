//
// Created by John on 6/4/2024.
//

#include <FolderMenu.hpp>
#include <QListWidgetItem>
#include <QVBoxLayout>

FolderMenu::FolderMenu(QWidget *parent)
        : QWidget(parent), layout(new QVBoxLayout(this)), toggleButton(new QPushButton(this)), fileList(new QListWidget(this)), lastWidth(200)
{
    toggleButton->setIcon(QIcon(":/resources/Hamburger.png"));
    toggleButton->setFixedSize(30, 30);

    connect(toggleButton, &QPushButton::clicked, this, [this]() {
        if (this->fileList->isVisible()) {
            lastWidth = this->width(); // Save the current width before collapsing
            this->setMaximumWidth(30);
            this->setMinimumWidth(30);
        } else {
            this->setMaximumWidth(QWIDGETSIZE_MAX); // Allow full expansion
            this->setMinimumWidth(200); // Set the minimum width when expanded
        }
        this->fileList->setVisible(!this->fileList->isVisible());
        emit toggled(); // Emit the toggled signal
    });

    layout->setContentsMargins(0, 0, 0, 0); // No margins to keep button in place
    layout->setSpacing(0); // No spacing between button and list
    layout->addWidget(toggleButton, 0, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(fileList);
    setLayout(layout);

    this->setMinimumWidth(200); // Ensure it starts with the correct minimum width

    connect(fileList, &QListWidget::itemClicked, this, &FolderMenu::onItemClicked); // Ensure the signal is connected
}

void FolderMenu::addMarkdownFile(const QString &filePath)
{
    QListWidgetItem *item = new QListWidgetItem(filePath);
    fileList->addItem(item);
}

void FolderMenu::onItemClicked(QListWidgetItem *item)
{
    emit fileSelected(item->text());
}

QListWidget *FolderMenu::getFileList() const {
    return fileList;
}