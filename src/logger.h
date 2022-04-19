#ifndef _MADOBE_LOGGER_H
#define _MADOBE_LOGGER_H

#include <string>

namespace madobe {

class Logger
{
public:
    Logger();

    void info(const char *format);
    void warn(const char *format);
    void error(const char *format);

private:
    std::string _log_dir;
    std::string _log_filename;
};

} // namespace madobe

#endif // _MADOBE_LOGGER_H
