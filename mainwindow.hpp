#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    // Internal storage for logs to support filtering/search
    struct LogEntry {
        QString level; // "Info", "Warning", "Error"
        QString text;
    };

    QList<LogEntry> m_logs;

private slots:
    void onToggleLeftDock() const;

    void onToggleRightDock() const;

    void onToggleBottomDock() const;

    // Console controls
    void onClearOutput();

    void onCopyOutput() const;

    void onLevelFilterChanged(const QString &level);

    void onOutputSearchTextChanged(const QString &text);

public:
    // Append a log line to the Run tab (and stored for filtering)
    void appendRunLog(const QString &level, const QString &text);
};

#endif // MAINWINDOW_H
