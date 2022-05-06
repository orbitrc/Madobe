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
    uint32_t button_width() const;
    uint32_t button_height() const;

    const uint8_t* border_top_left_image() const;
    const uint8_t* border_top_image() const;
    const uint8_t* border_top_right_image() const;
    const uint8_t* border_left_image() const;
    const uint8_t* border_right_image() const;
    const uint8_t* border_bottom_left_image() const;
    const uint8_t* border_bottom_image() const;
    const uint8_t* border_bottom_right_image() const;

private:
    bool load();

    uint32_t load_image(uint8_t **to, const char *filename,
            uint32_t width, uint32_t height);

private:
    std::string _id;
    Metadata *_metadata;
    std::string _json_path;
    std::string _images_dir;
    uint32_t _border_width;
    uint32_t _resize_width;
    uint32_t _shadow_width;
    uint32_t _title_bar_height;
    uint32_t _button_width;
    uint32_t _button_height;

    uint8_t *_border_top_left_data;
    uint32_t _border_top_left_len;

    uint8_t *_border_top_data;
    uint32_t _border_top_len;

    uint8_t *_border_top_right_data;
    uint32_t _border_top_right_len;

    uint8_t *_border_left_data;
    uint32_t _border_left_len;

    uint8_t *_border_right_data;
    uint32_t _border_right_len;

    uint8_t *_border_bottom_left_data;
    uint32_t _border_bottom_left_len;

    uint8_t *_border_bottom_data;
    uint32_t _border_bottom_len;

    uint8_t *_border_bottom_right_data;
    uint32_t _border_bottom_right_len;

    uint8_t *_close_data;
    uint32_t _close_len;
};

} // namespace madobe

#endif // _MADOBE_THEME_H
