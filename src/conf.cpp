#include "conf.h"

#include <QFile>

namespace madobe {

Conf::Conf(const char *path)
{
    QFile f(path);
    if (!f.exists()) {
        return;
    }

    f.open(QFile::ReadOnly | QFile::Text);
    auto line = f.readLine();
    QString current_group = "";
    while (line != "") {
        if (line.startsWith("[")) {
            current_group = line.replace("[", "").replace("]", "").trimmed();
        } else if (line.contains("=")) {
            auto kv = line.trimmed().split('=');
            auto key = current_group + "/" + kv[0];
            auto value = kv[1].toStdString();
            this->_map[key.toStdString()] = value;
        }

        line = f.readLine();
    }

    f.close();
}

Conf::~Conf()
{
}

std::string Conf::value(const std::string &key, const std::string &alt) const
{
    if (this->_map.count(key) == 0) {
        return alt;
    }

    return this->_map.at(key);
}

//==================
// Private Methods
//==================
bool parse()
{
    return false;
}

} // namespace madobe
