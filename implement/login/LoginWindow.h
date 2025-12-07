#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QString>

namespace Ui {
    class LoginWindow;
}

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

    ~LoginWindow() override;

private slots:
    void onLoginClicked();

private:
    Ui::LoginWindow *ui;

    // Path to SQLite data file
    QString m_dbPath;

    // Initialize data file and create table if necessary
    bool initDatabase();

    // Return SHA-256 hex string of the password
    [[nodiscard]] static QString hashPassword(const QString &password);
};

#endif // LOGINWINDOW_H
