#include "theme.h"

#include <filesystem>

#include <librsvg/rsvg.h>

#define STANDALONE_THEME_ID     "standalone"
#define STANDALONE_BORDER_WIDTH 2
#define STANDALONE_RESIZE_WIDTH 5
#define STANDALONE_SHADOW_WIDTH 40
#define STANDALONE_TITLE_BAR_HEIGHT 30
#define MADOBE_THEMES_DIR        "/usr/share/madobe/themes"

namespace madobe {

Theme::Theme(const char *id)
{
    this->_id = id;

    if (this->_id == STANDALONE_THEME_ID) {
        return;
    }

    if (!load()) {
        this->_id = STANDALONE_THEME_ID;
    }
}

Theme::~Theme()
{
}

const std::string& Theme::id() const
{
    return this->_id;
}

uint32_t Theme::border_width() const
{
    if (this->_id == STANDALONE_THEME_ID) {
        return STANDALONE_BORDER_WIDTH;
    }

    return this->_border_width;
}

uint32_t Theme::resize_width() const
{
    if (this->_id == STANDALONE_THEME_ID) {
        return STANDALONE_RESIZE_WIDTH;
    }

    return this->_resize_width;
}

uint32_t Theme::shadow_width() const
{
    if (this->_id == STANDALONE_THEME_ID) {
        return STANDALONE_SHADOW_WIDTH;
    }

    return this->_shadow_width;
}

uint32_t Theme::title_bar_height() const
{
    if (this->_id == STANDALONE_THEME_ID) {
        return STANDALONE_TITLE_BAR_HEIGHT;
    }

    return this->_title_bar_height;
}

//==================
// Private Methods
//==================

bool Theme::load()
{
    std::string theme_dir = std::string(MADOBE_THEMES_DIR) + "/" + this->_id;
    if (std::filesystem::is_directory(theme_dir)) {
        // Check theme.json file.
        this->_json_path = theme_dir + "/theme.json";
        if (!std::filesystem::exists(this->_json_path)) {
            this->_json_path = "";
            return false;
        }

        // Check images directory.
        this->_images_dir = theme_dir + "/images";
        if (!std::filesystem::is_directory(this->_images_dir)) {
            this->_images_dir = "";
            return false;
        }
    }

    return false;
}

} // namespace madobe
