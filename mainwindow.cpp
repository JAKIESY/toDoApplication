#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QDockWidget>
#include <QMessageBox>
#include <QClipboard>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // 简单版 CLion 风 QSS
    const QString qss = R"(
        QMainWindow {
            background-color: #2b2b2b;
        }

        QMenuBar {
            background-color: #3c3f41;
            color: #bbbbbb;
        }
        QMenuBar::item {
            background: transparent;
            padding: 4px 12px;
        }
        QMenuBar::item:selected {
            background: #4b6eaf;
            color: white;
        }

        QMenu {
            background-color: #3c3f41;
            color: #bbbbbb;
            border: 1px solid #2b2b2b;
        }
        QMenu::item:selected {
            background-color: #4b6eaf;
            color: white;
        }

        QToolBar {
            background-color: #3c3f41;
            border-bottom: 1px solid #242424;
            spacing: 4px;
        }

        QStatusBar {
            background-color: #3c3f41;
        }

        QTabWidget::pane {
            border-top: 1px solid #444444;
        }

        QTabBar::tab {
            background: #3c3f41;
            color: #bbbbbb;
            padding: 4px 10px;
        }
        QTabBar::tab:selected {
            background: #4b6eaf;
            color: white;
        }
        QTabBar::tab:hover:not:selected {
            background: #45494a;
        }

        QTreeView {
            background-color: #2b2b2b;
            alternate-background-color: #313335;
            color: #bbbbbb;
            border: none;
        }
        QTreeView::item:selected {
            background-color: #4b6eaf;
            color: white;
        }

        QPlainTextEdit {
            background-color: #2b2b2b;
            color: #a9b7c6;
            border: 1px solid #3c3f41;
        }

        QListWidget {
            background-color: #2b2b2b;
            color: #bbbbbb;
            border: none;
        }
        QListWidget::item:selected {
            background-color: #4b6eaf;
            color: white;
        }
    )";

    qApp->setStyleSheet(qss);


    setWindowTitle("Qt5 + CLion IDE Layout");

    //
    // 绑定 Actions 到槽函数
    //
    connect(ui->actionToggleLeftDock, &QAction::triggered, this, &MainWindow::onToggleLeftDock);
    connect(ui->actionToggleRightDock, &QAction::triggered, this, &MainWindow::onToggleRightDock);
    connect(ui->actionToggleBottomDock, &QAction::triggered, this, &MainWindow::onToggleBottomDock);

    //
    // File → New
    //
    connect(ui->actionNew, &QAction::triggered, this, [this]() {
        ui->editorArea->setPlainText("// New file");
    });

    //
    // Help → About
    //
    connect(ui->actionAbout, &QAction::triggered, this, []() {
        QMessageBox::information(nullptr, "About", "A Qt5 + CLion custom IDE layout demo");
    });

    //
    // 初始状态：都显示
    //
    ui->leftDock->show();
    ui->rightDock->show();
    ui->bottomDock->show();

    // --- Connect bottom console controls
    connect(ui->clearOutputButton, &QPushButton::clicked, this, &MainWindow::onClearOutput);
    connect(ui->copyOutputButton, &QPushButton::clicked, this, &MainWindow::onCopyOutput);
    connect(ui->levelFilterCombo, &QComboBox::currentTextChanged, this, &MainWindow::onLevelFilterChanged);
    connect(ui->outputSearch, &QLineEdit::textChanged, this, &MainWindow::onOutputSearchTextChanged);

    // Add some demo logs
    appendRunLog("Info", "Application started");
    appendRunLog("Info", "Loading project...");
    appendRunLog("Warning", "Some deprecated API used in module X");
    appendRunLog("Error", "Failed to locate toolchain: please configure CMake");
}

MainWindow::~MainWindow() {
    delete ui;
}

//
// Slots 实现
//

void MainWindow::onToggleLeftDock() const {
    ui->leftDock->setVisible(!ui->leftDock->isVisible());
}

void MainWindow::onToggleRightDock() const {
    ui->rightDock->setVisible(!ui->rightDock->isVisible());
}

void MainWindow::onToggleBottomDock() const {
    ui->bottomDock->setVisible(!ui->bottomDock->isVisible());
}

// Console slots
void MainWindow::onClearOutput() {
    ui->runOutput->clear();
    ui->buildOutput->clear();
    m_logs.clear();
}

void MainWindow::onCopyOutput() const {
    const QTextCursor cur = ui->runOutput->textCursor();
    QString text;
    if (cur.hasSelection()) {
        text = cur.selectedText();
    } else {
        text = ui->runOutput->toPlainText();
    }
    QClipboard *cb = QApplication::clipboard();
    cb->setText(text);
}

void MainWindow::onLevelFilterChanged(const QString &level) {
    // Rebuild visible runOutput from stored logs
    ui->runOutput->clear();
    const QString search = ui->outputSearch->text();
    for (const auto &[level, text]: qAsConst(m_logs)) {
        if (level != "All" && level.compare(level, Qt::CaseInsensitive) != 0) continue;
        if (!search.isEmpty() && !text.contains(search, Qt::CaseInsensitive)) continue;
        ui->runOutput->appendPlainText(QString("[%1] %2").arg(level, text));
    }
}

void MainWindow::onOutputSearchTextChanged(const QString &text) {
    // Rebuild visible runOutput using current level filter
    const QString level = ui->levelFilterCombo->currentText();
    onLevelFilterChanged(level);
}

void MainWindow::appendRunLog(const QString &level, const QString &text) {
    LogEntry e{level, text};
    m_logs.append(e);

    // Only append if it passes current filter/search
    const QString curLevel = ui->levelFilterCombo->currentText();
    const QString search = ui->outputSearch->text();
    if (curLevel != "All" && e.level.compare(curLevel, Qt::CaseInsensitive) != 0) return;
    if (!search.isEmpty() && !e.text.contains(search, Qt::CaseInsensitive)) return;

    ui->runOutput->appendPlainText(QString("[%1] %2").arg(e.level, e.text));
}
