#include "theme.h"

#include <stdlib.h>

#include <filesystem>

#include <librsvg/rsvg.h>

#include "theme-json.h"

#define STANDALONE_THEME_ID     "standalone"
#define STANDALONE_BORDER_WIDTH 2
#define STANDALONE_RESIZE_WIDTH 5
#define STANDALONE_SHADOW_WIDTH 40
#define STANDALONE_TITLE_BAR_HEIGHT 30
#define STANDALONE_BUTTON_WIDTH 6
#define STANDALONE_BUTTON_HEIGHT 6
#define MADOBE_THEMES_DIR        "/usr/share/madobe/themes"

namespace madobe {

Theme::Theme(const char *id)
{
    this->_id = id;

    // Init.
    this->_border_top_left_data = nullptr;
    this->_border_top_left_len = 0;
    this->_border_top_data = nullptr;
    this->_border_top_len = 0;
    this->_border_top_right_data = nullptr;
    this->_border_top_right_len = 0;
    this->_border_left_data = nullptr;
    this->_border_left_len = 0;
    this->_border_right_data = nullptr;
    this->_border_right_len = 0;
    this->_border_bottom_left_data = nullptr;
    this->_border_bottom_left_len = 0;
    this->_border_bottom_data = nullptr;
    this->_border_bottom_len = 0;
    this->_border_bottom_right_data = nullptr;
    this->_border_bottom_right_len = 0;
    this->_close_data = nullptr;
    this->_close_len = 0;

    if (this->_id == STANDALONE_THEME_ID) {
        return;
    }

    if (!load()) {
        this->_id = STANDALONE_THEME_ID;
    }
}

Theme::~Theme()
{
    if (this->_border_top_left_data != nullptr) {
        free(this->_border_top_left_data);
    }
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

uint32_t Theme::button_width() const
{
    if (this->_id == STANDALONE_THEME_ID) {
        return STANDALONE_BUTTON_WIDTH;
    }

    return this->_button_width;
}

uint32_t Theme::button_height() const
{
    if (this->_id == STANDALONE_THEME_ID) {
        return STANDALONE_BUTTON_HEIGHT;
    }

    return this->_button_height;
}

const uint8_t* Theme::border_top_left_image() const
{
    return this->_border_top_left_data;
}

const uint8_t* Theme::border_top_image() const
{
    return this->_border_top_data;
}

const uint8_t* Theme::border_top_right_image() const
{
    return this->_border_top_right_data;
}

const uint8_t* Theme::border_left_image() const
{
    return this->_border_left_data;
}

const uint8_t* Theme::border_right_image() const
{
    return this->_border_right_data;
}

const uint8_t* Theme::border_bottom_left_image() const
{
    return this->_border_bottom_left_data;
}

const uint8_t* Theme::border_bottom_image() const
{
    return this->_border_bottom_data;
}

const uint8_t* Theme::border_bottom_right_image() const
{
    return this->_border_bottom_right_data;
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

        ThemeJson theme_json(this->_json_path.c_str());
        this->_border_width = theme_json.int_value("border.width",
            STANDALONE_BORDER_WIDTH);
        this->_resize_width = theme_json.int_value("resize.width",
            STANDALONE_RESIZE_WIDTH);
        this->_shadow_width = theme_json.int_value("shadow.width",
            STANDALONE_SHADOW_WIDTH);
        this->_title_bar_height = theme_json.int_value("titleBar.height",
            STANDALONE_TITLE_BAR_HEIGHT);
        this->_button_width = theme_json.int_value(
            "titleBar.buttonGroup.button.width",
            STANDALONE_BUTTON_WIDTH
        );
        this->_button_height = theme_json.int_value(
            "titleBar.buttonGroup.button.height",
            STANDALONE_BUTTON_HEIGHT
        );

        this->_border_top_left_len = this->load_image(
            &(this->_border_top_left_data), "border-top-left.svg",
            this->_border_width,
            this->_border_width
        );
        this->_border_top_len = this->load_image(
            &(this->_border_top_data), "border-top.svg",
            1,
            this->_border_width
        );
        this->_border_top_right_len = this->load_image(
            &(this->_border_top_right_data), "border-top-right.svg",
            this->_border_width,
            this->_border_width
        );
        this->_border_left_len = this->load_image(
            &(this->_border_left_data), "border-left.svg",
            this->_border_width,
            1
        );
        this->_border_right_len = this->load_image(
            &(this->_border_right_data), "border-right.svg",
            this->_border_width,
            1
        );
        this->_border_bottom_left_len = this->load_image(
            &(this->_border_bottom_left_data), "border-bottom-left.svg",
            this->_border_width,
            this->_border_width
        );
        this->_border_bottom_len = this->load_image(
            &(this->_border_bottom_data), "border-bottom.svg",
            1,
            this->_border_width
        );
        this->_border_bottom_right_len = this->load_image(
            &(this->_border_bottom_right_data), "border-bottom-right.svg",
            this->_border_width,
            this->_border_width
        );

        return true;
    }

    return false;
}

uint32_t Theme::load_image(uint8_t **to, const char *filename,
        uint32_t width, uint32_t height)
{
    auto image_path = this->_images_dir + "/" + filename;
    if (!std::filesystem::exists(image_path)) {
        return 0;
    }

    GError *err = NULL;
    RsvgHandle *handle = rsvg_handle_new_from_file(
        image_path.c_str(), &err
    );

    RsvgDimensionData dimension;
    rsvg_handle_get_dimensions(handle, &dimension);

    RsvgRectangle viewport = {
        .x = 0.0,
        .y = 0.0,
        .width = static_cast<double>(dimension.width),
        .height = static_cast<double>(dimension.height),
    };

    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
        width, height);
    cairo_t *cr = cairo_create(surface);

    rsvg_handle_render_document(handle, cr, &viewport, &err);

//    uint32_t w = cairo_image_surface_get_width(surface);
    uint32_t h = cairo_image_surface_get_height(surface);
    uint32_t s = cairo_image_surface_get_stride(surface);
    uint32_t len = s * h;

    *to = (uint8_t*)malloc(len);
    memcpy(*to, cairo_image_surface_get_data(surface), len);

    // Free resources.
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    g_object_unref(handle);

    return len;
}

} // namespace madobe
