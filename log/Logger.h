#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

class Logger {
public:
    // Logger();

    ~Logger();

    // Initialize logger and install global message handler. Returns true on success.
    static bool init(const QString &logFilePath);

    // Shutdown logger and release resources
    static void shutdown();

    // Convenience logging helpers (these forward to the Qt logging functions so they
    // are handled by the installed message handler and also appear in the log file).
    static void debug(const QString &msg);

    static void info(const QString &msg);

    static void warn(const QString &msg);

    static void error(const QString &msg);
};

#endif // LOGGER_H
