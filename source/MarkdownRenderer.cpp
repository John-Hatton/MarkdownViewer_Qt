//
// Created by John on 6/4/2024.
//


#include <MarkdownRenderer.hpp>
#include <QTextBlockFormat>
#include <QTextCursor>
#include <QLabel>
#include <QTextEdit>
#include <QTableWidget>
#include <QHeaderView>

//MarkdownRenderer::MarkdownRenderer(QObject *parent)
//        : QObject(parent), inCodeBlock(false)
//{
//}
//
//QWidget* MarkdownRenderer::renderMarkdown(const QString &markdownText)
//{
//    QWidget *container = new QWidget;
//    QVBoxLayout *layout = new QVBoxLayout(container);
//    QStringList lines = markdownText.split('\n');
//
//    for (const QString &line : lines) {
//        parseLine(line, layout);
//    }
//
//    // Handle any remaining code block
//    if (inCodeBlock) {
//        parseCodeBlock("", layout);
//    }
//
//    container->setLayout(layout);
//    return container;
//}
//
//void MarkdownRenderer::parseLine(const QString &line, QVBoxLayout *layout)
//{
//    if (line.startsWith("```")) {
//        inCodeBlock = !inCodeBlock;
//        if (!inCodeBlock) {
//            parseCodeBlock("", layout);
//        }
//        return;
//    }
//
//    if (inCodeBlock) {
//        codeLines.append(line);
//        return;
//    }
//
//    if (line.startsWith("# ")) {
//        QLabel *label = new QLabel("<h1>" + line.mid(2) + "</h1>");
//        layout->addWidget(label);
//    } else if (line.startsWith("## ")) {
//        QLabel *label = new QLabel("<h2>" + line.mid(3) + "</h2>");
//        layout->addWidget(label);
//    } else if (line.startsWith("### ")) {
//        QLabel *label = new QLabel("<h3>" + line.mid(4) + "</h3>");
//        layout->addWidget(label);
//    } else if (line.startsWith("---")) {
//        QFrame *line = new QFrame();
//        line->setFrameShape(QFrame::HLine);
//        line->setFrameShadow(QFrame::Sunken);
//        layout->addWidget(line);
//    } else if (line.contains("|")) {
//        parseTable(line, layout);
//    } else {
//        QLabel *label = new QLabel(line);
//        layout->addWidget(label);
//    }
//}
//
//void MarkdownRenderer::parseTable(const QString &line, QVBoxLayout *layout)
//{
//    static QStringList tableHeader;
//    static QList<QStringList> tableData;
//
//    if (line.startsWith("|")) {
//        if (tableHeader.isEmpty()) {
//            tableHeader = line.split('|', Qt::SkipEmptyParts);
//        } else {
//            tableData.append(line.split('|', Qt::SkipEmptyParts));
//        }
//    } else {
//        QTableWidget *table = new QTableWidget;
//        table->setColumnCount(tableHeader.size());
//        table->setHorizontalHeaderLabels(tableHeader);
//        table->setRowCount(tableData.size());
//
//        for (int row = 0; row < tableData.size(); ++row) {
//            const QStringList &rowData = tableData.at(row);
//            for (int col = 0; col < rowData.size(); ++col) {
//                table->setItem(row, col, new QTableWidgetItem(rowData.at(col)));
//            }
//        }
//
//        table->horizontalHeader()->setStretchLastSection(true);
//        table->resizeColumnsToContents();
//        layout->addWidget(table);
//
//        tableHeader.clear();
//        tableData.clear();
//    }
//}
//
//void MarkdownRenderer::parseCodeBlock(const QString &line, QVBoxLayout *layout)
//{
//    QTextEdit *codeEdit = new QTextEdit;
//    codeEdit->setPlainText(codeLines.join("\n"));
//    codeEdit->setReadOnly(true);
//    codeEdit->setStyleSheet("background-color: #2e2e2e; color: white;");
//    layout->addWidget(codeEdit);
//    codeLines.clear();
//}

#include <QTextCursor>
#include <QTextBlockFormat>
#include <QTextCharFormat>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QTextTableCell>

MarkdownRenderer::MarkdownRenderer(QObject *parent)
        : QObject(parent), inCodeBlock(false)
{
}

QTextDocument* MarkdownRenderer::renderMarkdown(const QString &markdownText)
{
    QTextDocument *document = new QTextDocument();
    QTextCursor cursor(document);

    QStringList lines = markdownText.split('\n');
    for (const QString &line : lines) {
        parseLine(line, cursor);
    }

    return document;
}

void MarkdownRenderer::parseLine(const QString &line, QTextCursor &cursor)
{
    static QStringList tableHeader;
    static QList<QStringList> tableData;

    if (line.startsWith("```")) {
        cursor.insertBlock();
        inCodeBlock = !inCodeBlock;
        if (!inCodeBlock) {
            QTextBlockFormat format;
            format.setBackground(Qt::black);
            cursor.mergeBlockFormat(format);
            cursor.insertText(codeLines.join("\n"));
            codeLines.clear();
        }
        return;
    }

    if (inCodeBlock) {
        codeLines.append(line);
        return;
    }

    if (line.startsWith("# ")) {
        cursor.insertBlock();
        cursor.insertHtml("<h1>" + line.mid(2) + "</h1>");
    } else if (line.startsWith("## ")) {
        cursor.insertBlock();
        cursor.insertHtml("<h2>" + line.mid(3) + "</h2>");
    } else if (line.startsWith("### ")) {
        cursor.insertBlock();
        cursor.insertHtml("<h3>" + line.mid(4) + "</h3>");
    } else if (line.startsWith("---")) {
        cursor.insertBlock();
        cursor.insertHtml("<hr>");
    } else if (line.contains("|") && !line.trimmed().startsWith("|--")) {
        if (tableHeader.isEmpty()) {
            tableHeader = line.split('|', Qt::SkipEmptyParts);
        } else {
            tableData.append(line.split('|', Qt::SkipEmptyParts));
        }
    } else if (line.trimmed().startsWith("|--")) {
        // Ignore separator line in markdown table
    } else {
        if (!tableHeader.isEmpty()) {
            QTextTableFormat tableFormat;
            tableFormat.setBorder(1);
            tableFormat.setHeaderRowCount(1);

            QTextTable *table = cursor.insertTable(tableData.size() + 1, tableHeader.size(), tableFormat);

            for (int col = 0; col < tableHeader.size(); ++col) {
                QTextTableCell cell = table->cellAt(0, col);
                QTextCursor cellCursor = cell.firstCursorPosition();
                cellCursor.insertText(tableHeader.at(col));
            }

            for (int row = 0; row < tableData.size(); ++row) {
                const QStringList &rowData = tableData.at(row);
                for (int col = 0; col < rowData.size(); ++col) {
                    QTextTableCell cell = table->cellAt(row + 1, col);
                    QTextCursor cellCursor = cell.firstCursorPosition();
                    cellCursor.insertText(rowData.at(col));
                }
            }

            tableHeader.clear();
            tableData.clear();
        }
        cursor.insertBlock();
        cursor.insertText(line);
    }
}

