#include "LoginWindow.h"
#include "ui_loginwindow.h"
#include "../todo/TodoWindow.h"
#include "../../log/Logger.h"
#include "../../utils/env/EnvPath.h"
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QLineEdit>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent), ui(new Ui::LoginWindow) {
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);

    // Pressing Enter the password field should trigger the login button
    connect(ui->passwordLineEdit, &QLineEdit::returnPressed, ui->loginButton, &QPushButton::click);

    QString projectDir = QString::fromStdString(Env::projectPath());
    Logger::info(QString("Database dir: %1, sep: %2").arg(projectDir, QDir::separator()));
    m_dbPath = projectDir + QDir::separator() + "data/db/user.db";
    Logger::info(QString("Database path: %1").arg(m_dbPath));

    if (!initDatabase()) {
        // initDatabase already shows an error message box with details
        Logger::error(QString("Failed to initialize data at %1").arg(m_dbPath));
    }
}

LoginWindow::~LoginWindow() {
    delete ui;
}

bool LoginWindow::initDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(m_dbPath);
    if (!db.open()) {
        const QString err = db.lastError().text();
        Logger::error(QString("Cannot open data: %1").arg(err));
        QMessageBox::critical(this, "Database Error", "Cannot open data: " + err);
        return false;
    }

    QSqlQuery q;
    // Create users table if not exists: id INTEGER PRIMARY KEY, username TEXT UNIQUE, password_hash TEXT
    if (!q.exec(
        "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, password_hash TEXT)")) {
        const QString err = q.lastError().text();
        Logger::error(QString("Failed to create users table: %1").arg(err));
        QMessageBox::critical(this, "Database Error", "Failed to create users table: " + err);
        db.close();
        return false;
    }

    db.close();
    return true;
}

QString LoginWindow::hashPassword(const QString &password) {
    const QByteArray hashed = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return {hashed.toHex()};
}

void LoginWindow::onLoginClicked() {
    const QString userName = ui->usernameLineEdit->text().trimmed();
    const QString password = ui->passwordLineEdit->text();

    if (userName.isEmpty() || password.isEmpty()) {
        Logger::info("Username or password empty");
        QMessageBox::warning(this, "Input required", "Please enter both username and password.");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid()) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(m_dbPath);
    }
    if (!db.open()) {
        const QString err = db.lastError().text();
        Logger::error(QString("Cannot open data for login: %1").arg(err));
        QMessageBox::critical(this, "Database Error", "Cannot open data: " + err);
        return;
    }

    QSqlQuery q;
    q.prepare("SELECT password_hash FROM users WHERE username = :u");
    q.bindValue(":u", userName);
    if (!q.exec()) {
        const QString err = q.lastError().text();
        Logger::error(QString("Query failed: %1").arg(err));
        QMessageBox::critical(this, "Database Error", "Query failed: " + err);
        db.close();
        return;
    }

    if (q.next()) {
        const QString storedHash = q.value(0).toString();
        const QString providedHash = hashPassword(password);
        if (storedHash == providedHash) {
            Logger::info(QString("Login success for user %1").arg(userName));
            QMessageBox::information(this, "Login successful", QString("Welcome, %1!").arg(userName));

            // Open the TodoWindow and close the login window
            auto *todo = new TodoWindow();
            todo->show();

            this->close();
        } else {
            Logger::error(QString("Invalid credentials for user %1").arg(userName));
            QMessageBox::warning(this, "Login failed", "Invalid username or password.");
        }
    } else {
        // user not found -> register new user with hashed password
        const QString pHash = hashPassword(password);
        QSqlQuery ins;
        ins.prepare("INSERT INTO users (username, password_hash) VALUES (:u, :p)");
        ins.bindValue(":u", userName);
        ins.bindValue(":p", pHash);
        if (!ins.exec()) {
            const QString err = ins.lastError().text();
            Logger::error(QString("Failed to register user: %1").arg(err));
            QMessageBox::critical(this, "Registration failed", "Failed to register user: " + err);
        } else {
            Logger::info(QString("Registered new user %1").arg(userName));
            QMessageBox::information(this, "Registered", QString("User '%1' registered successfully.").arg(userName));
        }
    }

    db.close();
}
