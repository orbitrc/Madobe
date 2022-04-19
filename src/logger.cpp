#include "logger.h"

#include <stdlib.h>

#include <QString>
#include <QDir>
#include <QFile>

#define MADOBE_LOG_DIR ".local/share/madobe"
#define MADOBE_LOG_FILENAME "madobe.log"

namespace madobe {

Logger::Logger()
{
    auto home = getenv("HOME");
    QString log_dir = QString(home) + QString("/") + QString(MADOBE_LOG_DIR);
    // Create log directory if not exists.
    if (!QDir(log_dir).exists()) {
        QDir(log_dir).mkpath(log_dir);
    }
    this->_log_dir = log_dir.toStdString();
    this->_log_filename = MADOBE_LOG_FILENAME;

    QString log_path = log_dir + QString("/") + QString(this->_log_filename.c_str());

    QFile f(log_path);
    if (!f.exists()) {
        f.open(QFile::Append | QFile::Text);
        f.write("Madobe Log Begin");
        f.close();
    }
}

void Logger::info(const char *format)
{
    QString log_path = QString::fromStdString(this->_log_dir)
        + QString("/")
        + QString::fromStdString(this->_log_filename);
    QFile f(log_path);

    f.open(QFile::Append | QFile::Text);
    f.write("[INFO] ");
    f.write(format);
    f.close();
}

} // namespace madobe
