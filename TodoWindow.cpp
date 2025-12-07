#include "TodoWindow.h"
#include "ui_todo.h"
#include <QFile>
#include <QTextStream>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QTextEdit>
#include <QLabel>

TodoWindow::TodoWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::TodoWindow) {
    ui->setupUi(this);

    // Create console dock at bottom
    m_consoleDock = new QDockWidget(tr("Console"), this);
    m_consoleText = new QTextEdit(m_consoleDock);
    m_consoleText->setReadOnly(false);
    m_consoleDock->setWidget(m_consoleText);
    addDockWidget(Qt::BottomDockWidgetArea, m_consoleDock);

    // Create right tools dock
    m_rightDock = new QDockWidget(tr("Tools"), this);
    QWidget *rightWidget = new QWidget(m_rightDock);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
    QLabel *toolsLabel = new QLabel(tr("Tool windows"), rightWidget);
    rightLayout->addWidget(toolsLabel);
    rightWidget->setLayout(rightLayout);
    m_rightDock->setWidget(rightWidget);
    addDockWidget(Qt::RightDockWidgetArea, m_rightDock);

    // Wire up clear console action (if present in UI)
    if (ui->actionClearConsole) {
        connect(ui->actionClearConsole, &QAction::triggered, this, [this]() {
            if (m_consoleText) m_consoleText->clear();
        });
    }

    appendToConsole("TODO window started.");
}

TodoWindow::~TodoWindow() {
    delete ui;
}

void TodoWindow::appendToConsole(const QString &text) {
    if (m_consoleText) m_consoleText->append(text);
}
