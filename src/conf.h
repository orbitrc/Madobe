#ifndef _MADOBE_CONF_H
#define _MADOBE_CONF_H

#include <string>
#include <map>

namespace madobe {

class Conf
{
public:
    Conf(const char *path);
    ~Conf();

    std::string value(const std::string& key, const std::string& alt) const;

private:
    bool parse();

private:
    std::map<std::string, std::string> _map;
};

} // namespace madobe

#endif // _MADOBE_CONF_H
