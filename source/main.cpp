//
// Created by John on 6/4/2024.
//
#include <QApplication>
#include <MarkdownViewer.hpp>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPalette customPalette;
    customPalette.setColor(QPalette::Window, QColor(30, 30, 30));
    customPalette.setColor(QPalette::WindowText, Qt::white);
    customPalette.setColor(QPalette::Base, QColor(45, 45, 45));
    customPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    customPalette.setColor(QPalette::ToolTipBase, Qt::white);
    customPalette.setColor(QPalette::ToolTipText, Qt::white);
    customPalette.setColor(QPalette::Text, Qt::white);
    customPalette.setColor(QPalette::Button, QColor(0, 120, 212));
    customPalette.setColor(QPalette::ButtonText, Qt::white);
    customPalette.setColor(QPalette::BrightText, Qt::red);
    customPalette.setColor(QPalette::Link, QColor(0, 120, 212));
    customPalette.setColor(QPalette::Highlight, QColor(0, 120, 212));
    customPalette.setColor(QPalette::HighlightedText, Qt::black);

    // Apply custom palette
    app.setPalette(customPalette);

    // Apply custom stylesheet
    app.setStyleSheet(
            "QMenuBar { background-color: #303030; color: white; }"
            "QMenuBar::item { background-color: #303030; color: white; }"
            "QMenuBar::item::selected { background-color: #505050; }"
            "QMenu { background-color: #303030; color: white; }"
            "QMenu::item::selected { background-color: #505050; }"
            "QPushButton { background-color: #0078d4; color: white; border: none; }"
            "QPushButton::hover { background-color: #005fa3; }"
            "QScrollBar:vertical { background: #303030; width: 12px; }"
            "QScrollBar::handle:vertical { background: #606060; }"
            "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { background: #303030; }"
            "QScrollBar:horizontal { background: #303030; height: 12px; }"
            "QScrollBar::handle:horizontal { background: #606060; }"
            "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal { background: #303030; }"
    );

    MarkdownViewer viewer;
    viewer.resize(1000, 600);
    viewer.show();

    return QApplication::exec();
}