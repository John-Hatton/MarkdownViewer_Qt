//
// Created by John on 6/4/2024.
//

#include <MarkdownViewer.hpp>

#include <QApplication>
#include <QWidget>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QSplitter>
#include <QMessageBox>
#include <QDirIterator>
#include <QDebug>

MarkdownViewer::MarkdownViewer(QWidget *parent)
        : QWidget(parent), mainLayout(new QVBoxLayout(this)), contentLayout(new QHBoxLayout()), menuBar(new QMenuBar(this)), textBrowser(new QTextBrowser(this)), renderer(new MarkdownRenderer(this)), folderMenu(new FolderMenu(this)), splitter(new QSplitter(this))
{
    setupMenu();

    splitter->addWidget(folderMenu);
    splitter->addWidget(textBrowser);
    splitter->setStretchFactor(0, 1); // Allow folderMenu to stretch
    splitter->setStretchFactor(1, 1); // Allow textBrowser to stretch

    contentLayout->addWidget(splitter);

    mainLayout->setContentsMargins(10, 10, 10, 10); // Add padding
    mainLayout->addWidget(menuBar);
    mainLayout->addLayout(contentLayout);
    setLayout(mainLayout);

    setWindowTitle("Markdown Viewer");

    connect(folderMenu, &FolderMenu::fileSelected, this, &MarkdownViewer::loadMarkdownFile);
    connect(folderMenu, &FolderMenu::toggled, this, &MarkdownViewer::handleFolderMenuToggle); // Connect the toggle signal
}

void MarkdownViewer::setupMenu()
{
    QMenu *fileMenu = new QMenu("File", this);

    QAction *openAction = fileMenu->addAction("Open");
    connect(openAction, &QAction::triggered, this, &MarkdownViewer::openFile);

    QAction *openFolderAction = fileMenu->addAction("Open Folder");
    connect(openFolderAction, &QAction::triggered, this, &MarkdownViewer::openFolder);

    QAction *exitAction = fileMenu->addAction("Exit");
    connect(exitAction, &QAction::triggered, this, &QApplication::quit);

    menuBar->addMenu(fileMenu);
    menuBar->setFixedHeight(25); // Adjust menu bar height
}

void MarkdownViewer::loadMarkdownFile(const QString &filePath)
{
    qDebug() << "Loading Markdown File:" << filePath;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open markdown file.");
        return;
    }

    QString markdownText = file.readAll();
    file.close();

    qDebug() << "Loaded Markdown Text.";

    QTextDocument *document = renderer->renderMarkdown(markdownText);
    textBrowser->setDocument(document);
}

void MarkdownViewer::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Markdown File", QString(), "Markdown Files (*.md)");
    if (!filePath.isEmpty()) {
        loadMarkdownFile(filePath);
    }
}

void MarkdownViewer::openFolder()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, "Open Folder", QString());
    if (!folderPath.isEmpty()) {
        folderMenu->getFileTree()->clear();
        folderMenu->addMarkdownFilesFromDirectory(folderPath);
    }
}

void MarkdownViewer::handleFolderMenuToggle()
{
    QList<int> sizes;
    if (folderMenu->getFileTree()->isVisible()) {
        sizes << folderMenu->getLastWidth() << (splitter->width() - folderMenu->getLastWidth());
    } else {
        sizes << 30 << (splitter->width() - 30);
    }
    splitter->setSizes(sizes);
}
