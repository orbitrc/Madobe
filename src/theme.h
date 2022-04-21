#ifndef _MADOBE_THEME_H
#define _MADOBE_THEME_H

#include <stdint.h>

#include <string>

namespace madobe {

class Theme
{
public:
    class Metadata
    {
    public:
        Metadata(const char *path);

    private:
        std::string _name;
        std::string _description;
        std::string _author;
        std::string _email;
        std::string _screenshot;
        std::string _version;
    };

public:
    Theme(const char *id);
    ~Theme();

    const std::string& id() const;

    uint32_t border_width() const;
    uint32_t resize_width() const;
    uint32_t shadow_width() const;
    uint32_t title_bar_height() const;

private:
    bool load();

private:
    std::string _id;
    Metadata *_metadata;
    std::string _json_path;
    std::string _images_dir;
    uint32_t _border_width;
    uint32_t _resize_width;
    uint32_t _shadow_width;
    uint32_t _title_bar_height;
};

} // namespace madobe

#endif // _MADOBE_THEME_H
