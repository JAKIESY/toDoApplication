#include <QApplication>
#include "LoginWindow.h"
#include "log/Logger.h"
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Initialize logger to project dir app.log
    QString projectDir = QDir::currentPath();
    QString logPath = projectDir + QDir::separator() + "app.log";
    if (!Logger::init(logPath)) {
        qWarning() << "Failed to initialize logger at" << logPath;
    }

    LoginWindow w;
    w.show();
    int ret = QApplication::exec();

    Logger::shutdown();
    return ret;
}
