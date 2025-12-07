#include "implement/login/LoginWindow.h"
#include "log/Logger.h"
#include "utils/env/EnvPath.h"
#include <QApplication>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Initialize logger to project dir app.log
    QString projectDir = QString::fromStdString(Env::projectPath());
    QString logPath = projectDir + QDir::separator() + "data/app.log";
    if (!Logger::init(logPath)) {
        qWarning() << "Failed to initialize logger at" << logPath;
    }

    LoginWindow w;
    w.show();
    int ret = QApplication::exec();

    Logger::shutdown();
    return ret;
}
