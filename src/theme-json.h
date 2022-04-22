#ifndef _MADOBE_THEME_JSON_H
#define _MADOBE_THEME_JSON_H

#include <stdint.h>

#include <string>

namespace madobe {

class ThemeJson
{
public:
    ThemeJson(const char *path);
    ~ThemeJson();

    int int_value(const char *key, int alt) const;
    bool bool_value(const char *key, bool alt) const;
    std::string string_value(const char *key, const std::string& alt) const;

private:
    char *_data;
    uint32_t _data_len;
};

} // namespace madobe

#endif // _MADOBE_THEME_JSON_H
