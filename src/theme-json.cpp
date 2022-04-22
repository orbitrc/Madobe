#include "theme-json.h"

#include <stdlib.h>
#include <stdio.h>

#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>

namespace madobe {

ThemeJson::ThemeJson(const char *path)
{
    FILE *f = fopen(path, "r");
    // Get data length.
    fseek(f, 0, SEEK_END);
    this->_data_len = ftell(f);
    fseek(f, 0, SEEK_SET);
    // Read data.
    this->_data = (char*)malloc(sizeof(char) * this->_data_len);
    fread(this->_data, this->_data_len, 1, f);

    fclose(f);
}

ThemeJson::~ThemeJson()
{
    free(this->_data);
}

int ThemeJson::int_value(const char *key, int alt) const
{
    auto doc = QJsonDocument::fromJson(QByteArray(this->_data, this->_data_len));
    // Check parse error.
    if (doc.isNull()) {
        return alt;
    }
    auto json = doc.object();
    auto keyPath = QString(key).split(".");
    auto& it = json;
    for (int i = 0; i < keyPath.length() - 1; ++i) {
        if (!it.keys().contains(keyPath[0])) {
            return alt;
        }
        it = it.value(keyPath[i]).toObject();
    }
    if (it.value(keyPath.last()).isDouble()) {
        return it.value(keyPath.last()).toInt();
    }

    return alt;
}

bool ThemeJson::bool_value(const char *key, bool alt) const
{
    return alt;
}

std::string ThemeJson::string_value(const char *key, const std::string &alt) const
{
    return alt;
}

} // namespace madobe
