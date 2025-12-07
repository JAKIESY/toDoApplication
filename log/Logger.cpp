#include "Logger.h"
#include <QFile>
#include <QDateTime>
#include <QMutex>
#include <QDebug>
#include <QtGlobal>
#include <cstdio>

static QFile *g_logFile = nullptr;
static QMutex g_logMutex;

// Logger::Logger() {
//     init();
// }

Logger::~Logger() {
    shutdown();
}


static void qtMessageHandler(const QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    Q_UNUSED(context);
    QString level;
    switch (type) {
        case QtDebugMsg: level = "DEBUG";
            break;
        case QtInfoMsg: level = "INFO";
            break;
        case QtWarningMsg: level = "WARN";
            break;
        case QtCriticalMsg: level = "CRITICAL";
            break;
        case QtFatalMsg: level = "FATAL";
            break;
        default: level = "UNKNOWN";
            break;
    }

    QString timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);
    const QString line = QString("[%1] %2: %3\n").arg(timestamp, level, msg);

    QMutexLocker locker(&g_logMutex);
    if (g_logFile && g_logFile->isOpen()) {
        QTextStream ts(g_logFile);
        ts << line;
        ts.flush();
    }
    // Always also print to stdout/stderr for developer convenience
    if (type == QtWarningMsg || type == QtCriticalMsg || type == QtFatalMsg) {
        fprintf(stderr, "%s", line.toLocal8Bit().constData());
    } else {
        fprintf(stdout, "%s", line.toLocal8Bit().constData());
    }
    fflush(stderr);
}

bool Logger::init(const QString &logFilePath) {
    QMutexLocker locker(&g_logMutex);
    if (g_logFile) return true; // already initialized

    g_logFile = new QFile(logFilePath);
    if (!g_logFile->open(QIODevice::Append | QIODevice::Text)) {
        delete g_logFile;
        g_logFile = nullptr;
        return false;
    }
    qInstallMessageHandler(qtMessageHandler);
    return true;
}

void Logger::shutdown() {
    QMutexLocker locker(&g_logMutex);
    qInstallMessageHandler(nullptr);
    if (g_logFile) {
        g_logFile->close();
        delete g_logFile;
        g_logFile = nullptr;
    }
}

void Logger::debug(const QString &msg) {
    qDebug().noquote() << msg;
}

void Logger::info(const QString &msg) {
    qInfo().noquote() << msg;
}

void Logger::error(const QString &msg) {
    qCritical().noquote() << msg;
}
