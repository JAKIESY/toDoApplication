#ifndef TODOWINDOW_H
#define TODOWINDOW_H

#include <QMainWindow>

namespace Ui {
class TodoWindow;
}

class QDockWidget;
class QTextEdit;

class TodoWindow final : public QMainWindow {
    Q_OBJECT
public:
    explicit TodoWindow(QWidget *parent = nullptr);
    ~TodoWindow() override;

    // Append text to console area
    void appendToConsole(const QString &text) const;

private:
    Ui::TodoWindow *ui;

    // Docks created in code
    QDockWidget *m_consoleDock{nullptr};
    QTextEdit *m_consoleText{nullptr};
    QDockWidget *m_rightDock{nullptr};
};

#endif // TODOWINDOW_H
